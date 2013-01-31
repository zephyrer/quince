/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#include "Stdafx.h"
#include "ObjectPath.h"
#include <boost/tokenizer.hpp>

namespace QuinceSystem
{
    bool operator < (const ObjectPath &left, const ObjectPath &right)
    {
	size_t count = std::min(left.size(), right.size());
        for (size_t i = 0; i < count; ++i)
        {
            if (left[i] < right[i]) 
            {
                return true;
            }
            else if (left[i] > right[i])
            {
                return false;
            }
        }
        return left.size() < right.size();
    }
}

using namespace QuinceSystem;
using namespace std;
using namespace boost;

ObjectPath::ObjectPath()
{
}

ObjectPath::ObjectPath(const string &s)
{
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<string::value_type> sep(".");
    tokenizer tokens(s, sep);
    for(tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter)
    {
         push_back(ObjectID(lexical_cast<int>(*tok_iter)));
    }
}

ObjectPath::ObjectPath(const ObjectID &id)
 : vector<ObjectID>(1, id)
{
}

ObjectPath::ObjectPath(const_iterator it1, const_iterator it2)
: vector<ObjectID>(it1, it2)
{
}

bool
ObjectPath::startsWith(const ObjectPath &prefix) const
{
    if(prefix.size() <= size())
    {
        return equal(prefix.begin(), prefix.end(), begin());
    }
    return false;
}

bool
ObjectPath::endsWith(const ObjectPath &postfix) const
{
    if(postfix.size() <= size())
    {
        return equal(postfix.begin(), postfix.end(), begin() + size() - postfix.size());
    }
    return false;
}

ObjectPath
ObjectPath::operator + (const ObjectID &id) const
{
    ObjectPath result(*this);
    result.push_back(id);
    return result;
}

ObjectPath
ObjectPath::operator +(const ObjectPath &other) const
{
    ObjectPath result(*this);
    result.insert(result.end(), other.begin(), other.end());
    return result;
}
ObjectPath &
ObjectPath::operator +=(const ObjectID &id)
{
    push_back(id);
    return *this;
}

ObjectPath &
ObjectPath::operator +=(const ObjectPath &other)
{
    insert(end(), other.begin(), other.end());
    return *this;
}

string
ObjectPath::toString() const
{
    string result;
    for (size_t i = 0; i < size(); ++i) {
        result += lexical_cast<string>(operator[](i)) + '.';
    }
    if (not result.empty()) {
        result.resize(result.size() - 1);
    }
    return result;
}

ObjectPath
ObjectPath::slice(int start, int end) const
{
	int len = size();
	if (start < 0) start = len + start;
	start = max(0, min(len, start));
	if (end < 0) end = len + end;
	end = min(len, end);
	if (start < end) {
           return ObjectPath(begin() + start, begin() + end);
	}
	return ObjectPath();
}
