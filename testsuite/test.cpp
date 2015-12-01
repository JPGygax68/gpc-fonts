/*
The MIT License(MIT)

Copyright(c) 2014 Jean-Pierre Gygax, Biel/Bienne, Switzerland

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#define BOOST_TEST_MODULE rasterizedglyphset
#include <boost/test/unit_test.hpp>

#include <gpc/fonts/character_set.hpp>

using namespace gpc;

BOOST_AUTO_TEST_CASE(test_can_create_empty_character_set)
{
    fonts::character_set cs;

    BOOST_CHECK(1);
}

BOOST_AUTO_TEST_CASE(test_can_add_character_to_character_set)
{
    fonts::character_set cs;

    cs.add(65);

    BOOST_CHECK(cs.contains(65));
}

BOOST_AUTO_TEST_CASE(test_caracter_set_negative_check_for_character)
{
    fonts::character_set cs;

    BOOST_CHECK(cs.contains(65) == false);
}

BOOST_AUTO_TEST_CASE(test_adjacent_character_extends_existing_range_at_end)
{
    fonts::character_set cs;

    cs.add(65);
    cs.add(66);

    BOOST_CHECK(cs.ranges().size() == 1);
    BOOST_CHECK(cs.contains(65));
    BOOST_CHECK(cs.contains(66));
}

BOOST_AUTO_TEST_CASE(test_adjacent_character_extends_existing_range_at_beginning)
{
    fonts::character_set cs;

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
    fonts::character_set cs;

    cs.add(65, 26);

    BOOST_CHECK(cs.ranges().size() == 1);
    BOOST_CHECK(cs.contains(90));
    BOOST_CHECK(!cs.contains(91));
}

BOOST_AUTO_TEST_CASE(test_filling_gap_between_ranges_fuses_ranges_into_one)
{
    fonts::character_set cs;

    cs.add(65, 10);
    cs.add(76, 10);
    BOOST_CHECK(cs.ranges().size() == 2);

    cs.add(75);
    BOOST_CHECK(cs.ranges().size() == 1);
}

BOOST_AUTO_TEST_CASE(test_two_gaps_fill_one)
{
    fonts::character_set cs;

    cs.add(65, 10);
    cs.add(76, 10);
    cs.add(96, 10);
    BOOST_CHECK(cs.ranges().size() == 3);

    cs.add(75);
    BOOST_CHECK(cs.ranges().size() == 2);
}

BOOST_AUTO_TEST_CASE(test_two_gaps_fill_two)
{
    fonts::character_set cs;

    cs.add(65, 10);
    cs.add(76, 10);
    cs.add(96, 10);
    BOOST_CHECK(cs.ranges().size() == 3);

    cs.add(75);
    cs.add(86, 10);
    BOOST_CHECK(cs.ranges().size() == 1);
}

BOOST_AUTO_TEST_CASE(test_two_gaps_fill_first_partially_fill_second)
{
    fonts::character_set cs;

    cs.add(65, 10);
    cs.add(76, 10);
    cs.add(96, 10);
    BOOST_CHECK(cs.ranges().size() == 3);

    cs.add(75);
    cs.add(86, 9);
    BOOST_CHECK(cs.ranges().size() == 2);
}

BOOST_AUTO_TEST_CASE(test_remove_from_middle_of_range_splits_in_two)
{
    fonts::character_set cs;

    cs.add(65, 10);
    BOOST_CHECK(cs.ranges().size() == 1);
    BOOST_CHECK(cs.contains(70));

    cs.remove(70);
    BOOST_CHECK(cs.ranges().size() == 2);
    BOOST_CHECK(!cs.contains(70));
}

BOOST_AUTO_TEST_CASE(test_remove_from_start)
{
    fonts::character_set cs;

    cs.add(65, 10);
    cs.remove(65);

    BOOST_CHECK(cs.ranges().size() == 1);
    BOOST_CHECK(!cs.contains(65));
    BOOST_CHECK(cs.contains(66));
}

BOOST_AUTO_TEST_CASE(test_remove_from_end)
{
    fonts::character_set cs;

    cs.add(65, 10);
    cs.remove(74);

    BOOST_CHECK(cs.ranges().size() == 1);
    BOOST_CHECK(!cs.contains(74));
    BOOST_CHECK(cs.contains(73));
}


BOOST_AUTO_TEST_CASE(test_add_existing_range)
{
    fonts::character_set cs;
    fonts::character_range rn = { 65, 26 };

    cs.add(65, 10);
    BOOST_CHECK(!cs.contains(75));

    cs.add(rn);
    BOOST_CHECK(cs.contains(75));
}
