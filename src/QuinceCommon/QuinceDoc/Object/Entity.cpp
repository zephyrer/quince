/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/
#include "Stdafx.h"
#include "Entity.h"
#include "Object/ObjectPath.h"

using namespace QuinceSystem;
using namespace std;


Entity::Entity()
{
}

Entity::Entity(const Entity &other)
 : Object(other)
{
}

Entity &
Entity::operator = (const Entity &other)
{
    if(this != &other)
    {
        Object::operator = (other);
    }   
    return *this;
}

void
Entity::getChildren(vector<shared_ptr<Entity> > &) const
{
}

ObjectPath
Entity::pathOfChild(const Object &child) const
{
    vector<shared_ptr<Entity> > children;
    getChildren(children);
    foreach(shared_ptr<Entity> &ch, children)
    {
        if(ch.get() == &child)
        {
            return ObjectPath(ch->id());
        }
    }

    foreach(shared_ptr<Entity> &ch, children)
    {
        ObjectPath subPath = ch->pathOfChild(child);
        if(! subPath.empty())
        {
            return ObjectPath(ch->id()) + subPath;
        }
    }
    return ObjectPath();
}

shared_ptr<Object>
Entity::childFromPath(const ObjectPath &path) const
{
    if(! path.empty())
    {
        vector<shared_ptr<Entity> > children;
        getChildren(children);
        foreach(shared_ptr<Entity> &ch, children)
        {
            if(ch->id() == path.front())
            {
                if(path.size() == 1)
                {
                    return ch;
                }
                else
                {
                    return ch->childFromPath(path.slice(1)); 
                }
            }
        }
    }
    else
    {
    }
    return shared_ptr<Object>();
}

void
Entity::print(std::ostream &output, unsigned int indent) const
{
    output << string(indent, '\t') << typeid(*this).name() << " gId=" << globalId() << " id=" << id();
}

void
Entity::removeChild(shared_ptr<Entity>, bool)
{
}

void
Entity::replaceChild(shared_ptr<Entity>, shared_ptr<Entity>, bool)
{
}

void
Entity::save(std::ostream &out, const Object &context)
{
    hibernate(context);
    boost::archive::binary_oarchive oa(out);
    oa << this;
}

shared_ptr<Entity>
Entity::load(std::istream &in, const Object &context)
{
    Entity *p = NULL;
    boost::archive::binary_iarchive ia(in);
    ia >> p;
    shared_ptr<Entity> result(p);
    result->wakeup(context);
    return result;
}
