#define BOOST_TEST_MODULE rasterizedglyphset
#include <boost/test/unit_test.hpp>

#include <gpc/fonts/CharacterSet.hpp>

using namespace gpc;

BOOST_AUTO_TEST_CASE(test_can_create_empty_CharacterSet)
{
    fonts::CharacterSet cs;

    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(test_can_add_character_to_CharacterSet)
{
    fonts::CharacterSet cs;

    cs.add(65);

    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(test_CharacterSet_negative_check_for_character)
{
    fonts::CharacterSet cs;

    BOOST_CHECK(cs.contains(65) == false);
}

BOOST_AUTO_TEST_CASE(test_CharacterSet_positive_check_for_character)
{
    fonts::CharacterSet cs;

    cs.add(65);

    BOOST_CHECK(cs.contains(65) == true);
}

BOOST_AUTO_TEST_CASE(test_adjacent_ranges_fuse)
{
    fonts::CharacterSet cs;

    cs.add(65);
    cs.add(66);

    BOOST_CHECK(cs.ranges().size() == 1);
}
