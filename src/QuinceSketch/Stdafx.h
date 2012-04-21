/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUINCESKETCH_STDAFX_H
#define QUINCESKETCH_STDAFX_H

#include "QuinceSketch.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
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


namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace sources = boost::log::sources;
namespace filters = boost::log::filters;
namespace formatters = boost::log::formatters;
namespace attributes = boost::log::attributes;
namespace keywords = boost::log::keywords;

#endif 
