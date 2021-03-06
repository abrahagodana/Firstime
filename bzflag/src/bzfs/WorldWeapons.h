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

#ifndef __WORLDWEAPON_H__
#define __WORLDWEAPON_H__

#ifdef _MSC_VER
#pragma warning(4:4786)
#endif

/* common header */
#include "common.h"

/* system headers */
#include <vector>

/* common interface headers */
#include "Flag.h"
#include "TimeKeeper.h"

/** WorldWeapons is a container class that holds weapons
 */
class WorldWeapons
{
public:
  WorldWeapons();
  ~WorldWeapons();
  void fire();
  void add( const FlagType *type, const float *origin, float direction, float initdelay, const std::vector<float> &delay, TimeKeeper &sync);
  float nextTime();
  void clear();
  unsigned int count(); // returns the number of world weapons
  int packSize() const;
  void *pack(void *buf) const;

private:
  struct Weapon
  {
    const FlagType	*type;
    float		origin[3];
    float		direction;
    float       initDelay;
    std::vector<float>  delay;
    TimeKeeper		nextTime;
    int			nextDelay;
  };

  std::vector<Weapon*> weapons;
  int worldShotId;

  WorldWeapons( const WorldWeapons &w);
  WorldWeapons& operator=(const WorldWeapons &w) const;
};

#endif

// Local Variables: ***
// mode:C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
