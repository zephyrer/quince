/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUICE_PLATFORMCOMMON_H
#define QUICE_PLATFORMCOMMON_H

#include "Platform.h"
#if defined QUINCE_PLATFORM_WINDOWS
#include <windows.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

#endif
