/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUICE_BOOSTCOMMON_H
#define QUICE_BOOSTCOMMON_H

#ifdef _MSC_VER
	#pragma warning(push)
	#pragma warning(disable: 4251)
	#pragma warning(disable: 4819)
	#pragma warning(disable: 4996)
#endif

#include <boost/any.hpp>
#include <boost/assign.hpp>
#include <boost/foreach.hpp>
#include <boost/signal.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/scoped_ptr.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/weak_ptr.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/version.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/export.hpp> 
  
#define foreach BOOST_FOREACH

using boost::lexical_cast;

#ifdef _MSC_VER
	#pragma warning(pop)
#endif // _MSC_VER

#endif
