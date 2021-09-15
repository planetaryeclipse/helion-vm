#include <catch2/catch_all.hpp>
#include <cstdlib>
#include <string>

#include "util/value_util.hpp"

using namespace std;

TEST_CASE("testing of hexadecimal string validation", "[value_util][util]") {
    REQUIRE_FALSE(is_hex_val("0x"));
    REQUIRE_FALSE(is_hex_val("EF"));

    REQUIRE(is_hex_val("0xEF"));
    REQUIRE_FALSE(is_hex_val("0oEF"));

    REQUIRE_FALSE(is_hex_val("0x??"));
}

TEST_CASE("testing of octal string validation", "[value_util][util]") {
    REQUIRE_FALSE(is_oct_val("0o"));
    REQUIRE_FALSE(is_oct_val("67"));

    REQUIRE(is_oct_val("0o67"));
    REQUIRE_FALSE(is_oct_val("0x67"));

    REQUIRE_FALSE(is_oct_val("0o??"));
}

TEST_CASE("testing of decimal string validation", "[value_util][util]") {
    REQUIRE_FALSE(is_dec_val("0d"));
    REQUIRE_FALSE(is_dec_val("89"));

    REQUIRE(is_dec_val("0d89"));
    REQUIRE_FALSE(is_dec_val("0x89"));

    REQUIRE_FALSE(is_dec_val("0d??"));
}

TEST_CASE("testing of simple value string validation", "[value_util][util]") {
    REQUIRE_FALSE(is_valid_val("0x??"));
    REQUIRE_FALSE(is_valid_val("0o??"));
    REQUIRE_FALSE(is_valid_val("0d??"));

    REQUIRE(is_valid_val("0xEF"));
    REQUIRE(is_valid_val("0o67"));
    REQUIRE(is_valid_val("0d89"));
}

TEST_CASE("testing of complex value string validation", "[value_util][util]") {
    e_val_type type;

    REQUIRE_FALSE(is_valid_val("0x??", &type));
    REQUIRE_FALSE(is_valid_val("0o??", &type));
    REQUIRE_FALSE(is_valid_val("0d??", &type));

    REQUIRE(is_valid_val("0xEF", &type));
    REQUIRE(type == VAL_HEXADECIMAL);

    REQUIRE(is_valid_val("0o67", &type));
    REQUIRE(type == VAL_OCTAL);

    REQUIRE(is_valid_val("0d89", &type));
    REQUIRE(type == VAL_DECIMAL);
}

TEST_CASE("testing of conversion of value string to value", "[value_util][util]") {
    REQUIRE_THROWS_AS(get_val("0x??"), invalid_argument);
    REQUIRE_THROWS_AS(get_val("0o??"), invalid_argument);
    REQUIRE_THROWS_AS(get_val("0d??"), invalid_argument);

    REQUIRE(get_val("0xEF") == 0xEF);
    REQUIRE(get_val("0o67") == 067);
    REQUIRE(get_val("0d89") == 89);
}