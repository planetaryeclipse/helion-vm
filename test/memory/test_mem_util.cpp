#include <catch2/catch_all.hpp>

#include "util/mem_util.hpp"

TEST_CASE("testing of uint8 bit order inversion", "[memory]") {
    REQUIRE(get_inverted_bit_order(0b00000000) == 0b00000000);
    REQUIRE(get_inverted_bit_order(0b11111111) == 0b11111111);

    REQUIRE(get_inverted_bit_order(0b00000001) == 0b10000000);
    REQUIRE(get_inverted_bit_order(0b00001111) == 0b11110000);
}

TEST_CASE("testing of uint16 byte order inversion", "[memory]") {
    REQUIRE(get_inverted_byte_order((uint16_t)0x0000) == 0x0000);
    REQUIRE(get_inverted_byte_order((uint16_t)0xFFFF) == 0xFFFF);

    REQUIRE(get_inverted_byte_order((uint16_t)0x0001) == 0x0100);
    REQUIRE(get_inverted_byte_order((uint16_t)0x00FF) == 0xFF00);
}

TEST_CASE("testing of uint32 byte order inversion", "[memory]") {
    REQUIRE(get_inverted_byte_order((uint32_t)0x00000000) == 0x00000000);
    REQUIRE(get_inverted_byte_order((uint32_t)0xFFFFFFFF) == 0xFFFFFFFF);

    REQUIRE(get_inverted_byte_order((uint32_t)0x00000001) == 0x01000000);
    REQUIRE(get_inverted_byte_order((uint32_t)0x0000ABCD) == 0xCDAB0000);
}

TEST_CASE("testing of uint64 byte order inversion", "[memory]") {
    REQUIRE(get_inverted_byte_order((uint64_t)0x0000000000000000) == 0x0000000000000000);
    REQUIRE(get_inverted_byte_order((uint64_t)0xFFFFFFFFFFFFFFFF) == 0xFFFFFFFFFFFFFFFF);

    REQUIRE(get_inverted_byte_order((uint64_t)0x0000000000000001) == 0x0100000000000000);
    REQUIRE(get_inverted_byte_order((uint64_t)0x0000000089ABCDEF) == 0xEFCDAB8900000000);
}

TEST_CASE("testing of valid memory identifiers", "[memory]") {
    REQUIRE_FALSE(is_valid_mem_identifier(""));

    REQUIRE_FALSE(is_valid_mem_identifier("0"));
    REQUIRE_FALSE(is_valid_mem_identifier("9A"));

    REQUIRE(is_valid_mem_identifier("A"));
    REQUIRE(is_valid_mem_identifier("_"));

    REQUIRE(is_valid_mem_identifier("_0"));
    REQUIRE(is_valid_mem_identifier("_A"));
}