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

    BOOST_CHECK(cs.contains(65));
}

BOOST_AUTO_TEST_CASE(test_CharacterSet_negative_check_for_character)
{
    fonts::CharacterSet cs;

    BOOST_CHECK(cs.contains(65) == false);
}

BOOST_AUTO_TEST_CASE(test_adjacent_character_extends_existing_range_at_end)
{
    fonts::CharacterSet cs;

    cs.add(65);
    cs.add(66);

    BOOST_CHECK(cs.ranges().size() == 1);
    BOOST_CHECK(cs.contains(65));
    BOOST_CHECK(cs.contains(66));
}

BOOST_AUTO_TEST_CASE(test_adjacent_character_extends_existing_range_at_beginning)
{
    fonts::CharacterSet cs;

    cs.add(65);
    cs.add(96);

    cs.add(95);

    BOOST_CHECK(cs.ranges().size() == 2);
    BOOST_CHECK(cs.contains(65));
    BOOST_CHECK(cs.contains(96));
    BOOST_CHECK(cs.contains(95));
}

BOOST_AUTO_TEST_CASE(test_can_add_character_range)
{
    fonts::CharacterSet cs;

    cs.add(65, 26);

    BOOST_CHECK(cs.ranges().size() == 1);
    BOOST_CHECK(cs.contains(90));
    BOOST_CHECK(!cs.contains(91));
}

BOOST_AUTO_TEST_CASE(test_filling_gap_between_ranges_fuses_ranges_into_one)
{
    fonts::CharacterSet cs;

    cs.add(65, 10);
    cs.add(85, 10);
    BOOST_CHECK(cs.ranges().size() == 2);

    cs.add(75, 10);
    BOOST_CHECK(cs.ranges().size() == 1);
}
