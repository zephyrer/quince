/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/
#include "Stdafx.h"
#include "Object.h"

using namespace QuinceSystem;

unsigned int Object::ObjectGlobalID::sNextGlobalValue = 1;

Object::ObjectGlobalID::ObjectGlobalID()
 : ObjectID(sNextGlobalValue++)
{
}

Object::ObjectGlobalID::ObjectGlobalID(const ObjectGlobalID &)
: ObjectID(sNextGlobalValue++)
{
}

Object::~Object()
{
}

Object::Object()
{
}

Object::Object(const ObjectID &id)
 : mId(id)
{
}

Object::Object(const Object &other)
 : mId(other.mId)
{
}

Object &
Object::operator = (const Object &other)
{
    mId = other.mId;
    return *this;
}

void
Object::save(std::ostream &out, const Object &context)
{
    hibernate(context);
    boost::archive::binary_oarchive oa(out);
    oa << this;
}

shared_ptr<Object>
Object::load(std::istream &in, const Object &context)
{
    Object *p = NULL;
    boost::archive::binary_iarchive ia(in);
    ia >> p;
    shared_ptr<Object> result(p);
    result->wakeup(context);
    return result;
}

void
Object::hibernate(const Object &)
{
}

void 
Object::wakeup(const Object &)
{
}
