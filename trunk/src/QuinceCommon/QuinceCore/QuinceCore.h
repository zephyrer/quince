/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUINCESYSTEM_QUINCECORE_H
#define QUINCESYSTEM_QUINCECORE_H

#if defined QUINCECORE_STATIC || defined QUINCE_PLATFORM_LINUX || defined QUINCE_PLATFORM_MACOS || defined QUINCE_PLATFORM_CYGWIN
    #define QUINCECORE_DLLAPI
#else
    #ifdef QUINCECORE_EXPORTS
        #define QUINCECORE_DLLAPI __declspec(dllexport)
    #else
        #define QUINCECORE_DLLAPI __declspec(dllimport)
    #endif
#endif

#endif 
