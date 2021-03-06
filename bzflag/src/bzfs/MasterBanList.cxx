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

#ifdef _MSC_VER
#pragma warning( 4: 4786)
#endif

#include "MasterBanList.h"
#include "URLManager.h"

MasterBanList::MasterBanList()
{
}

MasterBanList::~MasterBanList()
{

}

const std::string& MasterBanList::get ( const std::string URL )
{
  data = "";
  // get all up on the internet and go get the thing
	URLManager::instance().getURL(URL,data);
  return data;
}
