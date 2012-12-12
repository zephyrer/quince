/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUINCESYSTEM_QUINCEDOC_H
#define QUINCESYSTEM_QUINCEDOC_H

#include "QuinceCore.h"

#if defined (__linux__) || defined (__linux)
#define LINUX 1
#endif 

#if defined (__MACH__) || defined (__APPLE__)
#define MACOS 1
#endif

#if defined QUINCEDOC_STATIC || defined LINUX || defined MACOS
    #define QUINCEDOC_DLLAPI
#else
    #ifdef QUINCEDOC_EXPORTS
        #define QUINCEDOC_DLLAPI __declspec(dllexport)
    #else
        #define QUINCEDOC_DLLAPI __declspec(dllimport)
    #endif
#endif

#endif 
