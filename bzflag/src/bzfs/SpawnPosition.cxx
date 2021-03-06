/* bzflag
 * Copyright (c) 1993 - 2005 Tim Riker
 *
 * This package is free software;  you can redistribute it and/or
 * modify it under the terms of the license found in the file
 * named COPYING that should have accompanied this file.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

// object that creates and contains a spawn position

#include "common.h"

#include <string>

#include "SpawnPosition.h"
#include "DropGeometry.h"
#include "Obstacle.h"
#include "FlagInfo.h"
#include "TeamBases.h"
#include "WorldInfo.h"
#include "PlayerInfo.h"
#include "PlayerState.h"
#include "GameKeeper.h"
#include "BZDBCache.h"

// FIXME: from bzfs.cxx
extern int getCurMaxPlayers();
extern bool areFoes(TeamColor team1, TeamColor team2);
extern BasesList bases;
extern WorldInfo *world;
extern PlayerState lastState[];

SpawnPosition::SpawnPosition(int playerId, bool onGroundOnly, bool notNearEdges) :
		curMaxPlayers(getCurMaxPlayers())
{
  GameKeeper::Player *playerData
    = GameKeeper::Player::getPlayerByIndex(playerId);
  if (!playerData)
    return;

  team = playerData->player.getTeam();
  azimuth = (float)(bzfrand() * 2.0 * M_PI);

  if (playerData->player.shouldRestartAtBase() &&
      (team >= RedTeam) && (team <= PurpleTeam) &&
      (bases.find(team) != bases.end())) {
    TeamBases &teamBases = bases[team];
    const TeamBase &base = teamBases.getRandomBase((int)(bzfrand() * 100));
    base.getRandomPosition(pos[0], pos[1], pos[2]);
    playerData->player.setRestartOnBase(false);
  } else {
    const float tankRadius = BZDBCache::tankRadius;
    safeSWRadius = (float)((BZDB.eval(StateDatabase::BZDB_SHOCKOUTRADIUS) + BZDBCache::tankRadius) * 1.5);
    safeDistance = tankRadius * 20; // FIXME: is this a good value?
    const float size = BZDBCache::worldSize;
    const float maxWorldHeight = world->getMaxWorldHeight();

    // keep track of how much time we spend searching for a location
    TimeKeeper start = TimeKeeper::getCurrent();

    int tries = 0;
    float minProximity = size / 3.0f;
    float bestDist = -1.0f;
    bool foundspot = false;
    while (!foundspot) {
      if (!world->getZonePoint(std::string(Team::getName(team)), testPos)) {
	if (notNearEdges) {
	  // don't spawn close to map edges in CTF mode
	  testPos[0] = ((float)bzfrand() - 0.5f) * size * 0.6f;
	  testPos[1] = ((float)bzfrand() - 0.5f) * size * 0.6f;
	} else {
	  testPos[0] = ((float)bzfrand() - 0.5f) * (size - 2.0f * tankRadius);
	  testPos[1] = ((float)bzfrand() - 0.5f) * (size - 2.0f * tankRadius);
	}
	testPos[2] = onGroundOnly ? 0.0f : ((float)bzfrand() * maxWorldHeight);
      }
      tries++;

      const float waterLevel = world->getWaterLevel();
      float minZ = 0.0f;
      if (waterLevel > minZ) {
	minZ = waterLevel;
      }
      float maxZ = maxWorldHeight;
      if (onGroundOnly) {
	maxZ = 0.0f;
      }

      if (DropGeometry::dropPlayer(testPos, minZ, maxZ)) {
	foundspot = true;
      }

      // check every now and then if we have already used up 10ms of time
      if (tries >= 50) {
	tries = 0;
	if (TimeKeeper::getCurrent() - start > 0.01f) {
	  if (bestDist < 0.0f) { // haven't found a single spot
	    //Just drop the sucka in, and pray
	    pos[0] = testPos[0];
	    pos[1] = testPos[1];
	    pos[2] = maxWorldHeight;
	    DEBUG1("Warning: getSpawnLocation ran out of time, just dropping the sucker in\n");
	  }
	  break;
	}
      }

      // check if spot is safe enough
      bool dangerous = isImminentlyDangerous();
      if (foundspot && !dangerous) {
	float enemyAngle;
	float dist = enemyProximityCheck(enemyAngle);
	if (dist > bestDist) { // best so far
	  bestDist = dist;
	  pos[0] = testPos[0];
	  pos[1] = testPos[1];
	  pos[2] = testPos[2];
	  azimuth = fmod((float)(enemyAngle + M_PI), (float)(2.0 * M_PI));
	}
	if (bestDist < minProximity) { // not good enough, keep looking
	  foundspot = false;
	  minProximity *= 0.99f; // relax requirements a little
	}
      } else if (dangerous) {
	foundspot = false;
      }
    }
  }
}

SpawnPosition::~SpawnPosition()
{
}

const bool SpawnPosition::isFacing(const float *enemyPos, const float enemyAzimuth,
				   const float deviation) const
{
  // vector points from test to enemy
  float dx = enemyPos[0] - testPos[0];
  float dy = enemyPos[0] - testPos[1];
  float angActual = atan2f (dy, dx);
  float diff = fmodf(enemyAzimuth - angActual, (float)M_PI * 2.0f);

  // now diff is between {-PI*2 and +PI*2}, and we're looking for values around
  // -PI or +PI, because that's when the enemy is facing the source.
  diff = fabsf (diff); // between {0 and +PI*2}
  diff = fabsf ((float)(diff - M_PI));

  if (diff < (deviation / 2.0f)) {
    return true;
  } else {
    return false;
  }
}

const bool SpawnPosition::isImminentlyDangerous() const
{
  GameKeeper::Player *playerData;
  for (int i = 0; i < curMaxPlayers; i++) {
    playerData = GameKeeper::Player::getPlayerByIndex(i);
    if (!playerData)
      continue;
    if (playerData->player.isAlive()) {
      float *enemyPos = lastState[i].pos;
      float enemyAngle = lastState[i].azimuth;
      if (playerData->player.getFlag() >= 0) {
	// check for dangerous flags
	const FlagInfo *finfo = FlagInfo::get(playerData->player.getFlag());
	const FlagType *ftype = finfo->flag.type;
	// FIXME: any more?
	if (ftype == Flags::Laser) {  // don't spawn in the line of sight of an L
	  if (isFacing(enemyPos, enemyAngle, (float)(M_PI / 9.0))) { // he's looking within 20 degrees of spawn point
	    return true;	// eek, don't spawn here
	  }
	} else if (ftype == Flags::ShockWave) {  // don't spawn next to a SW
	  if (distanceFrom(enemyPos) < safeSWRadius) { // too close to SW
	    return true;	// eek, don't spawn here
	  }
	}
      }
      // don't spawn in the line of sight of a normal-shot tank within a certain distance
      if (distanceFrom(enemyPos) < safeDistance) { // within danger zone?
	if (isFacing(enemyPos, enemyAngle, (float)(M_PI / 9.0))) { //and he's looking at me
	  return true;
	}
      }
    }
  }

  // TODO: should check world weapons also

  return false;
}

const float SpawnPosition::enemyProximityCheck(float &enemyAngle) const
{
  GameKeeper::Player *playerData;
  float worstDist = 1e12f; // huge number
  bool noEnemy    = true;

  for (int i = 0; i < curMaxPlayers; i++) {
    playerData = GameKeeper::Player::getPlayerByIndex(i);
    if (!playerData)
      continue;
    if (playerData->player.isAlive()
	&& areFoes(playerData->player.getTeam(), team)) {
      float *enemyPos = lastState[i].pos;
      if (fabs(enemyPos[2] - testPos[2]) < 1.0f) {
	float x = enemyPos[0] - testPos[0];
	float y = enemyPos[1] - testPos[1];
	float distSq = x * x + y * y;
	if (distSq < worstDist) {
	  worstDist  = distSq;
	  enemyAngle = lastState[i].azimuth;
	  noEnemy    = false;
	}
      }
    }
  }
  if (noEnemy)
    enemyAngle = (float)(bzfrand() * 2.0 * M_PI);
  return sqrtf(worstDist);
}

const float SpawnPosition::distanceFrom(const float* farPos) const
{
  float dx = farPos[0] - testPos[0];
  float dy = farPos[1] - testPos[1];
  float dz = farPos[2] - testPos[2];
  return (float)sqrt(dx*dx + dy*dy + dz*dz);
}

// Local Variables: ***
// mode:C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
