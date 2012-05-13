#include "Stdafx.h"
#include <boost/test/unit_test.hpp>
#include "QuinceCore.h"
#include "Object/ObjectID.h"

using namespace QuinceSystem;

BOOST_AUTO_TEST_SUITE(QuinceCoreSuite);

BOOST_AUTO_TEST_CASE(ObjectID_test)
{
    ObjectID id1;
    BOOST_CHECK_EQUAL(id1.value(), 1);
    ObjectID id2(32);
    BOOST_CHECK_EQUAL(id2.value(), 32);
    ObjectID id3;
    id3.setValue(255);
    BOOST_CHECK_EQUAL(id3.value(), 255);
    ObjectID nextID;
    BOOST_CHECK_EQUAL(nextID.value(), 3);
    BOOST_CHECK_EQUAL(id2 ==  ObjectID(32), true);
    BOOST_CHECK_EQUAL(id1 != id2, true);
    BOOST_CHECK_EQUAL(id1 < id2, true);
}
BOOST_AUTO_TEST_SUITE_END()
