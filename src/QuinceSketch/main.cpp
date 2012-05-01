/*===========================================================================

   Copyright (c) neuron Inc. 2012-
   All rights reserved.
   Author: Chen Zeshi, Scott  

=============================================================================*/

#include "Stdafx.h"


void init()
{
    // logging::init_log_to_console(std::clog, keywords::format = "%TimeStamp%: %_%");
    logging::init_log_to_file("sample.log");
    logging::init_log_to_file
    (
        keywords::file_name = "sample_%N.log",
        keywords::rotation_size = 10 * 1024 * 1024,
        keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0)
        //keywords::format = "[%TimeStamp%]:%_%"
    );
    logging::core::get()->set_filter
    (
	filters::attr< logging::trivial::severity_level > ("Severity") >= logging::trivial::info
    );
}

int main(int argc, char* argv[])
{
    init();
    BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(info) << "An informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
    BOOST_LOG_TRIVIAL(error) << "An error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

    return 0;
}
