/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUINCESKETCH_VERSION_H
#define QUINCESKETCH_VERSION_H

namespace QuinceSystem
{

#ifdef __cplusplus
	#define EXTERN extern "C"
#else
	#define EXTERN 
#endif 

EXTERN int QuinceSketch_version_major();
EXTERN int QuinceSketch_version_minor();
EXTERN int QuinceSketch_version_patch();

}

#endif // QUINCESKETCH_VERSION_H
