FILE (GLOB_RECURSE test_SRCS *.cpp *.cxx *.cc *.C *.c *.h *.hpp)

SET (PROJECT_NAME QuinceCore-unittests)
SET (Quince_LIBS "QuinceCore")
SET (test_LIBS ${Boost_LIBRARIES} ${Quince_LIBS})
SET (test_BIN ${PROJECT_NAME})

INCLUDE_DIRECTORIES("${MAINFOLDER}/src/QuinceCommon/QuinceCore")
ADD_EXECUTABLE(${test_BIN} ${test_SRCS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${test_LIBS})

#ADD_CUSTOM_TARGET(check ALL "${MAINFOLDER}/bin/${test_BIN}" DEPENDS ${test_BIN} COMMENT "Executing unit tests..." VERBATIM SOURCES ${test_SRCS})
#ADD_CUSTOM_TARGET(test "${MAINFOLDER}/bin/${test_BIN}" DEPENDS ${test_BIN} COMMENT "Executing unit tests..." VERBATIM SOURCES ${test_SRCS})
