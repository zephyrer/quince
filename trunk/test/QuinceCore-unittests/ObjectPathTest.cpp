#include "Stdafx.h"
#include <boost/test/unit_test.hpp>
#include "QuinceCore.h"
#include "Object/ObjectPath.h"
using namespace QuinceSystem;

BOOST_AUTO_TEST_SUITE(QuinceCoreSuite);

BOOST_AUTO_TEST_CASE(ObjectPath_test)
{
    ObjectPath obj_path1;
    BOOST_CHECK_EQUAL(obj_path1.toString(), "");
    ObjectID id1(25), id2(30), id3(55), id4(255);
    ObjectPath obj_path2;
    obj_path2 += id1;
    obj_path2 += id2;
    obj_path2 += id3;
    obj_path2 += id4;
    BOOST_CHECK_EQUAL(obj_path2[0], id1);
    BOOST_CHECK_EQUAL(obj_path2.startsWith(ObjectPath(id1)), true);
    BOOST_CHECK_EQUAL(obj_path2.endsWith(ObjectPath("255")), true);
    ObjectPath obj_path3(obj_path2.begin(), obj_path2.end());
    BOOST_CHECK_EQUAL(obj_path3.toString(), "25.30.55.255");
}

BOOST_AUTO_TEST_SUITE_END()
