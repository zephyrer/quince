/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUINCECORE_VERSION_H
#define QUINCECORE_VERSION_H

namespace QuinceSystem
{

#ifdef __cplusplus
	#define EXTERN extern "C"
#else
	#define EXTERN 
#endif 

EXTERN int QuinceCore_version_major();
EXTERN int QuinceCore_version_minor();
EXTERN int QuinceCore_version_patch();

}

#endif // QUINCECORE_VERSION_H
