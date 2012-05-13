/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUINCEDOC_VERSION_H
#define QUINCEDOC_VERSION_H

namespace QuinceSystem
{

#ifdef __cplusplus
	#define EXTERN extern "C"
#else
	#define EXTERN 
#endif 

EXTERN int QuinceDoc_version_major();
EXTERN int QuinceDoc_version_minor();
EXTERN int QuinceDoc_version_patch();

}

#endif // QUINCEDOC_VERSION_H
