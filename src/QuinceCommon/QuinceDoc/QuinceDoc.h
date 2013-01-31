/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUINCESYSTEM_QUINCEDOC_H
#define QUINCESYSTEM_QUINCEDOC_H

#include "QuinceCore.h"


#if defined QUINCEDOC_STATIC || defined QUINCE_PLATFORM_LINUX || defined QUINCE_PLATFORM_MACOSX || defined QUINCE_PLATFORM_CYGWIN
    #define QUINCEDOC_DLLAPI
#else
    #ifdef QUINCEDOC_EXPORTS
        #define QUINCEDOC_DLLAPI __declspec(dllexport)
    #else
        #define QUINCEDOC_DLLAPI __declspec(dllimport)
    #endif
#endif

#endif 
