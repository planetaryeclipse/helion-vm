#include <catch2/catch_all.hpp>
#include <cstdlib>
#include <list>

#include "util/string_util.hpp"

using namespace std;

TEST_CASE("testing of char in list", "[string_util][util]") {
    const list<char> test_chars = {
        'A', 'B', 'C', '_'};

    REQUIRE(is_char_in_list('A', test_chars));
    REQUIRE(is_char_in_list('B', test_chars));
    REQUIRE(is_char_in_list('C', test_chars));
    REQUIRE(is_char_in_list('_', test_chars));

    REQUIRE_FALSE(is_char_in_list('?', test_chars));
    REQUIRE_FALSE(is_char_in_list('?', {}));
}

TEST_CASE("testing of parsing of delimited values", "[string_util][util]") {
    REQUIRE_THROWS_AS(parse_delim_vals("", ','), invalid_argument);
    REQUIRE_THROWS_AS(parse_delim_vals(",", ','), invalid_argument);
    REQUIRE_THROWS_AS(parse_delim_vals(",,", ','), invalid_argument);

    REQUIRE_THROWS_AS(parse_delim_vals("a", 'a'), invalid_argument);

    REQUIRE(parse_delim_vals("A", ',').size() == 1);
    REQUIRE(parse_delim_vals("A,B", ',').size() == 2);
    REQUIRE(parse_delim_vals("A,B,C", ',').size() == 3);

    REQUIRE_THROWS_AS(parse_delim_vals("A,", ','), invalid_argument);
    REQUIRE_THROWS_AS(parse_delim_vals("A,B,", ','), invalid_argument);

    REQUIRE_THROWS_AS(parse_delim_vals(",A", ','), invalid_argument);
    REQUIRE_THROWS_AS(parse_delim_vals(",A,B", ','), invalid_argument);

    REQUIRE_THROWS_AS(parse_delim_vals(",A,", ','), invalid_argument);
    REQUIRE_THROWS_AS(parse_delim_vals(",A,B,", ','), invalid_argument);

    REQUIRE(parse_delim_vals("AaB", 'a').size() == 2);
    REQUIRE(parse_delim_vals("AaBaC", 'a').size() == 3);

    REQUIRE(parse_delim_vals("val1", ',').at(0) == "val1");

    vector<string> test_vals = parse_delim_vals("val1,val2,val3", ',');
    REQUIRE(test_vals.at(0) == "val1");
    REQUIRE(test_vals.at(1) == "val2");
    REQUIRE(test_vals.at(2) == "val3");
}