# neuron. Copyright (C) 2012. <License>.

#
# Solution Properties
#
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(OS "Mac OS X")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    SET(OS "Linux")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    SET(OS "Windows")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

if(APPLE)
    SET( CMAKE_CXX_COMPILER /opt/local/bin/g++-mp-4.8 )
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
   execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
   if (GCC_VERSION VERSION_GREATER 4.7 OR GCC_VERSION VERSION_EQUAL 4.7)
        message(STATUS "C++11 activated.")
        add_definitions("-std=gnu++11")
   elseif(GCC_VERSION VERSION_GREATER 4.3 OR GCC_VERSION VERSION_EQUAL 4.3)
        message(WARNING "C++0x activated. If you get any errors update to a compiler which fully supports C++11")
        add_definitions("-std=gnu++0x")
   else ()
        message(FATAL_ERROR "C++11 needed. Therefore a gcc compiler with a version higher than 4.3 is needed.")   
   endif()
endif(CMAKE_COMPILER_IS_GNUCXX)

PROJECT(QuinceSystem)
# have a test
#
# Debugging Options
#
SET (CMAKE_VERBOSE_MAKEFILE 0) # Use 1 for debugging, 0 for release

#
# Project Output Paths
#
SET (MAINFOLDER ${PROJECT_SOURCE_DIR})
SET (EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/bin")
SET (LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")
SET (THIRDPARTY_PATH "${MAINFOLDER}/thirdparty")
SET (TEST_PATH "${MAINFOLDER}/test")

#
# Project Search Paths
#
LIST (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}")
LIST (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}/tools")
LIST (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}/thirdparty")
LIST (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}/test")
INCLUDE_DIRECTORIES("${MAINFOLDER}/include")
INCLUDE_DIRECTORIES("${MAINFOLDER}/src/QuinceCommon")

#
# Locate Project Prerequisites 
#
SET (Boost_ADDITIONAL_VERSIONS "1.39" "1.39.0" "1.40" "1.40.0" "1.41" "1.41.0" "1.42" "1.42.0" "1.43" "1.43.0" "1.44" "1.44.0" "1.45" "1.45.0" "1.46" "1.46.0" "1.47.0" "1.48" "1.48.0" "1.49" "1.49.0" "1.50" "1.50.0")
FIND_PACKAGE (Boost 1.37 COMPONENTS "unit_test_framework"  "date_time" "filesystem" "graph" "iostreams" "program_options" "regex" "serialization" "signals" "system" "thread" "wserialization" REQUIRED)
FIND_PACKAGE (Boost 1.37 COMPONENTS  "unit_test_framework" "date_time" "filesystem" "graph" "iostreams" "program_options" "regex" "serialization" "signals" "system" "thread" "wserialization" REQUIRED)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

SET (GLM_VERSION "glm-0.9.3.2")
INCLUDE_DIRECTORIES(${THIRDPARTY_PATH}/${GLM_VERSION})

#
# Add Precompile File
#
MACRO(ADD_PCH_RULE header_filename project_srcs)
IF(MSVC)
    IF(USE_MSVC_PCH)
        SET_SOURCE_FILES_PROPERTIES("Stdafx.cpp"
                                    PROPERTIES
                                    COMPILE_FLAGS "/YcStdafx.h")
        FOREACH(SRC_FILE ${project_srcs})
            SET_SOURCE_FILES_PROPERTIES(${SRC_FILE}
                                        PROPERTIES
                                        COMPILE_FLAGS "/YuStdafx.h")
        ENDFOREACH(SRC_FILE ${project_srcs})
   ENDIF(USE_MSVC_PCH)
ELSE(MSVC)
    SET(_gch_filename "${header_filename}.gch")
    LIST(APPEND ${project_srcs}  ${_gch_filename})
    SET(_args ${CMAKE_CXX_FLAGS})
    LIST(APPEND _args -c ${header_filename} -o ${_gch_filename})
    GET_DIRECTORY_PROPERTY(DIRINC INCLUDE_DIRECTORIES)
    FOREACH(_inc ${DIRINC})
        LIST(APPEND _args "-I" ${_inc})
    ENDFOREACH(_inc ${DIRINC})
        SEPARATE_ARGUMENTS(_args)
        ADD_CUSTOM_COMMAND(OUTPUT ${_gch_filename}
                           COMMAND rm -f ${_gch_filename}
                           COMMAND ${CMAKE_CXX_COMPILER}
                           ${CMAKE_CXX_COMPILER_ARG1} ${_args}
                           DEPENDS ${header_filename})
ENDIF(MSVC)
ENDMACRO(ADD_PCH_RULE header_filename project_srcs)


#
# Add Build Targets
#
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)
#
# Add Install Targets
#
IF (EXISTS "${MAINFOLDER}/include/${PROJECT_NAME}" AND IS_DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}")
    INSTALL(DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}" DESTINATION "include")
ENDIF (EXISTS "${MAINFOLDER}/include/${PROJECT_NAME}" AND IS_DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}")

