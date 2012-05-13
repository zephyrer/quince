/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUINCEDOC_OBJECT_H
#define QUINCEDOC_OBJECT_H

#include "Object/ObjectID.h"
#include "Object/ObjectPath.h"

namespace QuinceSystem
{

class QUINCEDOC_DLLAPI Object 
{
public:
    virtual ~Object();

    Object & operator = (const Object &other);

    ObjectID id() const { return mId; }
    void setId(const ObjectID &value) { mId = value; }

    const ObjectID & globalId() const { return mGlobalId; }

    virtual ObjectPath pathOfChild(const Object &child) const = 0;
    virtual shared_ptr<Object> childFromPath(const ObjectPath &path) const = 0;   
 
    virtual void hibernate(const Object &);
    virtual void wakeup(const Object &);

    virtual void save(std::ostream &out, const Object &context);
    static shared_ptr<Object> load(std::istream &in, const Object &context);
protected:
    Object();
    Object(const ObjectID &id);
    Object(const Object &other);
private:
    class ObjectGlobalID : public ObjectID
    {
    public:
        ObjectGlobalID();
        ObjectGlobalID(const ObjectGlobalID &);
    private:
        static unsigned int sNextGlobalValue;
    };


    ObjectID mId;
    ObjectGlobalID mGlobalId;

    friend class boost::serialization::access;
    template <typename Archive> void serialize(Archive &ar, const unsigned int)
    {
        ar & mId;
    }
};

}

#endif // QUINCEDOC_OBJECT_H
