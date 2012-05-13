/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#include "Stdafx.h"
#include "ObjectID.h"

using namespace QuinceSystem;

unsigned int ObjectID::sNextValue = 1;

ObjectID::ObjectID()
 : mValue(sNextValue++)
{
}

ObjectID::ObjectID(unsigned int v) 
 : mValue(v)
{
}
