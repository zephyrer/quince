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

#include <boost/log/common.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/filters.hpp>
#include <boost/log/formatters.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/filters.hpp>
#include <boost/log/sinks/sink.hpp>
#include <boost/log/utility/init/to_file.hpp>
#include <boost/log/formatters.hpp>
#include <boost/log/common.hpp>
#include <boost/filesystem.hpp> 
#include <boost/log/utility/init/to_console.hpp>
#include <boost/log/utility/init/common_attributes.hpp>
#include <boost/log/attributes/timer.hpp>

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
  
namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace sources = boost::log::sources;
//namespace formatters = boost::log::formatters;
namespace filters = boost::log::filters;
namespace attributes = boost::log::attributes;
namespace keywords = boost::log::keywords;

#define foreach BOOST_FOREACH

#ifdef _MSC_VER
	#pragma warning(pop)
#endif // _MSC_VER

#endif
