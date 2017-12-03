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

/* ViewFrustum
 *	Encapsulates a camera.
 */

#ifndef	BZF_VIEW_FRUSTUM_H
#define	BZF_VIEW_FRUSTUM_H

#include "common.h"
#include "bzfgl.h"
#include "Frustum.h"

// FIXME -- will need a means for off center projections for
//	looking through teleporters

class ViewFrustum : public Frustum {
  public:
    ViewFrustum();
    ~ViewFrustum();
    void		executeProjection() const;
    void		executeDeepProjection() const;
    void		executeView() const;
    void		executeOrientation() const;
    void		executePosition() const;
    void		executeBillboard() const;
};

#endif // BZF_VIEW_FRUSTUM_H

// Local Variables: ***
// mode:C++ ***
// tab-width: 8 ***
// c-basic-offset: 2 ***
// indent-tabs-mode: t ***
// End: ***
// ex: shiftwidth=2 tabstop=8
