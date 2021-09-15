#include <catch2/catch_all.hpp>

#include "memory/mem_except.hpp"
#include "memory/mem_types.hpp"

using namespace std;

TEST_CASE("testing of primary memory methods", "[memory][mem_types]") {
    unique_ptr<mem_projectile> test_mem;

    SECTION("testing of projectile memory") {
        REQUIRE_THROWS_AS(mem_projectile(0), invalid_mem_size_exception);
        test_mem = unique_ptr<mem_projectile>(new mem_projectile(4));
    }
    SECTION("testing of satellite memory") {
        REQUIRE_THROWS_AS(mem_satellite(0), invalid_mem_size_exception);
        test_mem = unique_ptr<mem_projectile>(new mem_satellite(4));
    }
    SECTION("testing of interstellar memory") {
        REQUIRE_THROWS_AS(mem_interstellar(0), invalid_mem_size_exception);
        test_mem = unique_ptr<mem_projectile>(new mem_interstellar(4));
    }

    REQUIRE(test_mem->get_block_length() == 4);

    REQUIRE_THROWS_AS(test_mem->get_sub_block_addr(0, 0), invalid_mem_size_exception);

    REQUIRE_NOTHROW(test_mem->get_sub_block_addr(0, 1));
    REQUIRE_NOTHROW(test_mem->get_sub_block_addr(0, 4));
    REQUIRE_NOTHROW(test_mem->get_sub_block_addr(2, 2));

    REQUIRE_THROWS_AS(test_mem->get_sub_block_addr(4, 1), invalid_mem_size_for_indexing_exception);
    REQUIRE_THROWS_AS(test_mem->get_sub_block_addr(4, 4), invalid_mem_size_for_indexing_exception);

    REQUIRE_THROWS_AS(test_mem->set_bytes({0x67, 0x89, 0xAB, 0xCD, 0xEF}), invalid_mem_size_for_indexing_exception);
    REQUIRE_NOTHROW(test_mem->set_bytes({0x89, 0xAB, 0xCD, 0xEF}));

    //NOTE: the compiler will handle any code big-endian to system little-endian conversions
    //for bits in a byte but it will not handle the byte order conversion for big-endian to
    //little-endian, hence the test cases use an inverted byte order

    REQUIRE(*(uint16_t*)test_mem->get_sub_block_addr(0, 2) == 0xAB89);
    REQUIRE(*(uint32_t*)test_mem->get_sub_block_addr(0, 4) == 0xEFCDAB89);

    REQUIRE_THROWS_AS(test_mem->set_bytes(0, {0x67, 0x89, 0xAB, 0xCD, 0xEF}), invalid_mem_size_for_indexing_exception);
    REQUIRE_THROWS_AS(test_mem->set_bytes(2, {0x01, 0x23, 0x45}), invalid_mem_size_for_indexing_exception);
    REQUIRE_NOTHROW(test_mem->set_bytes(2, {0x01, 0x23}));

    REQUIRE(*(uint32_t*)test_mem->get_sub_block_addr(0, 4) == 0x2301AB89);
}

TEST_CASE("testing of projectile memory control/update methods", "[memory][mem_types]"){
    unique_ptr<mem_projectile> test_mem(new mem_projectile(1));
    
    //these are just meant to show the debug log output, there is no way to test
    //whether the memory has been acquired as the mutex will be nonblocking when
    //running test cases
    test_mem->acquire_control();

    // projectile memory does not have update functionality
    REQUIRE_FALSE(test_mem->get_has_update());
    test_mem->set_has_update(true);
    REQUIRE_FALSE(test_mem->get_has_update());
    test_mem->set_has_update(false);
    REQUIRE_FALSE(test_mem->get_has_update());

    test_mem->release_control();
}

TEST_CASE("testing of satellite memory control/update methods", "[memory][mem_types]"){
    unique_ptr<mem_projectile> test_mem(new mem_satellite(1));
    
    //these are just meant to show the debug log output, there is no way to test
    //whether the memory has been acquired as the mutex will be nonblocking when
    //running test cases
    test_mem->acquire_control();

    // satellite memory does not have update functionality
    REQUIRE_FALSE(test_mem->get_has_update());
    test_mem->set_has_update(true);
    REQUIRE_FALSE(test_mem->get_has_update());
    test_mem->set_has_update(false);
    REQUIRE_FALSE(test_mem->get_has_update());

    test_mem->release_control();
}

TEST_CASE("testing of interstellar memory control/update methods", "[memory][mem_types]"){
    unique_ptr<mem_projectile> test_mem(new mem_interstellar(1));
    
    //these are just meant to show the debug log output, there is no way to test
    //whether the memory has been acquired as the mutex will be nonblocking when
    //running test cases
    test_mem->acquire_control();

    // interstellar memory does have update functionality
    REQUIRE_FALSE(test_mem->get_has_update());
    test_mem->set_has_update(true);
    REQUIRE(test_mem->get_has_update());
    test_mem->set_has_update(false);
    REQUIRE_FALSE(test_mem->get_has_update());

    test_mem->release_control();
}

TEST_CASE("testing copy of memory pointers sharing object", "[memory][mem_types]"){
    shared_ptr<mem_projectile> test_mem(new mem_projectile(4));
    shared_ptr<mem_projectile> test_mem_copy(test_mem);

    REQUIRE(test_mem.use_count() == 2);

    REQUIRE(test_mem->get_block_length() == 4);
    REQUIRE(test_mem_copy->get_block_length() == 4);

    REQUIRE(test_mem->get_sub_block_addr(2, 2) == test_mem_copy->get_sub_block_addr(2, 2));
}