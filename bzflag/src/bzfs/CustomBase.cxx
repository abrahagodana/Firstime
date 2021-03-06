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

/* interface header */
#include "CustomBase.h"

/* common implementation headers */
#include "global.h" // for CtfTeams
#include "BaseBuilding.h"
#include "ObstacleMgr.h"


CustomBase::CustomBase()
{
  pos[0] = pos[1] = pos[2] = 0.0f;
  rotation = 0.0f;
  size[0] = size[1] = BZDB.eval(StateDatabase::BZDB_BASESIZE);
  color = 0;
}


bool CustomBase::read(const char *cmd, std::istream& input) {
  if (strcmp(cmd, "color") == 0) {
    input >> color;
    if ((color < 0) || (color >= CtfTeams))
      return false;
  } else {
    if (!WorldFileObstacle::read(cmd, input))
      return false;
  }
  return true;
}


void CustomBase::writeToGroupDef(GroupDefinition *groupdef) const
{
  float absSize[3] = { fabsf(size[0]), fabsf(size[1]), fabsf(size[2]) };
  BaseBuilding* base = new BaseBuilding(pos, rotation, absSize, color);
  groupdef->addObstacle(base);
}

// Local variables: ***
// mode:C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
