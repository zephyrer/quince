/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUINCESYSTEM_QUINCECORE_H
#define QUINCESYSTEM_QUINCECORE_H

#if defined (__linux__) || defined (__linux)
#define LINUX 1
#endif 

#if defined (__MACH__) || defined (__APPLE__)
#define MACOS 1
#endif

#if defined QUINCECORE_STATIC || defined LINUX || defined MACOS
    #define QUINCECORE_DLLAPI
#else
    #ifdef QUINCECORE_EXPORTS
        #define QUINCECORE_DLLAPI __declspec(dllexport)
    #else
        #define QUINCECORE_DLLAPI __declspec(dllimport)
    #endif
#endif

#endif 
