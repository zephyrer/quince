/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUINCEDOC_ENTITY_H
#define QUINCEDOC_ENTITY_H

#include "Object/Object.h"

namespace QuinceSystem
{

class ObjectPath;

class QUINCEDOC_DLLAPI Entity: public Object 
{
public:
    Entity(const Entity &);
    Entity & operator = (const Entity &other);

    // emit when object changed
    boost::signal<void ()> changed;

    virtual ObjectPath pathOfChild(const Object &child) const;
    virtual shared_ptr<Object> childFromPath(const ObjectPath &path) const;   

    virtual shared_ptr<Entity> copy() const = 0;
    virtual void print(std::ostream &output, unsigned int indent = 0) const; 

    virtual void save(std::ostream &out, const Object &context);
    static shared_ptr<Entity> load(std::istream &in, const Object &context);
   
    virtual void getChildren(vector<shared_ptr<Entity> > &result) const; 
    virtual void removeChild(shared_ptr<Entity> entity, bool allDescendant = false);
    virtual void replaceChild(shared_ptr<Entity> oldChild, shared_ptr<Entity> newChild, bool allDescendant = false);
protected:
    Entity();

    typedef map<ObjectPath, shared_ptr<Entity> > ChildrenMap;
    friend class boost::serialization::access;
    template <typename Archive> void serialize(Archive &ar, const unsigned int)
    {
        ar & boost::serialization::base_object<Object>(*this);
    }
};

inline std::ostream & operator << (std::ostream &output, const Entity &entity)
{
    entity.print(output);
    return output;
}

}

#endif // QUINCEDOC_OBJECT_H
