/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/
#include "Version.h"
#include "LibraryInfo.h"

using namespace QuinceSystem;

EXTERN int QuinceDoc_version_major()
{
	return APPLICATION_VERSION_MAJOR;
}

EXTERN int QuinceDoc_version_minor()
{
    return APPLICATION_VERSION_MINOR;
}

EXTERN int QuinceDoc_version_patch()
{
    return APPLICATION_VERSION_PATCH;
}
