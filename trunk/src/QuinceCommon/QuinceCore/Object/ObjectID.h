/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUINCECORE_OBJECTID_H
#define QUINCECORE_OBJECTID_H

namespace QuinceSystem
{

class QUINCECORE_DLLAPI ObjectID
{
public:
    ObjectID();
    explicit ObjectID(unsigned int v);
    void setValue(unsigned int v) {
        mValue = v;
    }
 
    unsigned int value() const {
        return mValue;
    }

    bool operator == (const ObjectID &other) const {
        return mValue == other.mValue;
    }
    
    operator int() const  {
        return mValue;   
    }
    bool operator != (const ObjectID &other) const {
        return !(*this == other);
    }

    bool operator < (const ObjectID &other) const {
        return mValue < other.mValue;
    }
private:
    unsigned int mValue;
    static unsigned int sNextValue;

    friend class boost::serialization::access;
    template <typename Archive> void serialize(Archive &ar, const unsigned int) 
    {
        ar & mValue;
        sNextValue = std::max(sNextValue, mValue + 1);
        ar & sNextValue;
    }
};

}


#endif // QUINCECORE_OBJECTID_H
