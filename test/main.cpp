#include "Stdafx.h"
#define BOOST_TEST_MODULE QuinceCore-unittests
#include <boost/test/unit_test.hpp>
#include "QuinceCore.h"
#include "Object/ObjectID.h"

using namespace QuinceSystem;

BOOST_AUTO_TEST_SUITE(minimal_test)

BOOST_AUTO_TEST_CASE(ObjectID_test)
{
    ObjectID id;
	id.setValue(255);
	BOOST_CHECK_EQUAL(id.value(), 255);
}

BOOST_AUTO_TEST_SUITE_END()
int main(int argc, char* argv[])
{
    return 0;
}
