/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#ifndef QUICECORE_STDAFX_H
#define QUICECORE_STDAFX_H

#define QUINCECORE_EXPORTS

#include "QuinceCore.h"

#include <limits>
#include <iostream>
#include <string>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/filters.hpp>


namespace QuinceSystem
{
    using std::string;
}

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace sources = boost::log::sources;
//namespace formatters = boost::log::formatters;
namespace filters = boost::log::filters;
namespace attributes = boost::log::attributes;
namespace keywords = boost::log::keywords;

#endif
