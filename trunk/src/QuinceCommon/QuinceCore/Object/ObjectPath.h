/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUINCECORE_OBJECTPATH_H
#define QUINCECORE_OBJECTPATH_H

#include "ObjectID.h"

namespace QuinceSystem
{

class QUINCECORE_DLLAPI ObjectPath : public vector<ObjectID>
{
public:
    ObjectPath();
    ObjectPath(const string &s);
    ObjectPath(const_iterator it1, const_iterator it2);
    explicit ObjectPath(const ObjectID &id);

    ObjectPath operator + (const ObjectID &id) const;
    ObjectPath operator + (const ObjectPath &other) const;
    ObjectPath & operator += (const ObjectID &id);
    ObjectPath & operator += (const ObjectPath &other);
    operator string() const { return toString(); }
  
    string toString() const;
    bool startsWith(const ObjectPath &prefix) const;
    bool endsWith(const ObjectPath &postfix) const;
    ObjectPath slice(int start) const { return slice(start, size()); }
    ObjectPath slice(int start, int end) const;

private:
    friend class boost::serialization::access;
    template <typename Archive> void serialize(Archive &ar, const unsigned int)
    {
        ar & boost::serialization::base_object<vector<ObjectID> >(*this);
    }
};

QUINCECORE_DLLAPI bool operator < (const ObjectPath &, const ObjectPath &);

}


#endif // QUINCECORE_OBJECTPATH_H
