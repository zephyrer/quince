/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/
#include "Version.h"
#include "ApplicationInfo.h"

using namespace QuinceSystem;

EXTERN int QuinceSketch_version_major()
{
	return APPLICATION_VERSION_MAJOR;
}

EXTERN int QuinceSketch_version_minor()
{
    return APPLICATION_VERSION_MINOR;
}

EXTERN int QuinceSketch_version_patch()
{
    return APPLICATION_VERSION_PATCH;
}