#include <catch2/catch_all.hpp>
#include <memory>
#include <string>

#include "memory/mem_except.hpp"
#include "memory/mem_mapping.hpp"

// TODO - test cases for memory mapping

using namespace std;

TEST_CASE("testing of memory map internal memory", "[memory][mem_mapping]") {
    memory_map m_map;

    REQUIRE_THROWS_AS(m_map.create_mem("0_", 0), invalid_mem_identifier_exception);
    REQUIRE_THROWS_AS(m_map.create_mem("_0", 0), invalid_mem_size_exception);

    REQUIRE_THROWS_AS(m_map.create_mem("_AB", 1, {0xCD, 0xEF}), invalid_mem_size_for_indexing_exception);

    REQUIRE_THROWS_AS(m_map.find_mem("TEST_MEM"), unallocated_mem_identifier_exception);
    REQUIRE_FALSE(m_map.contains_mem("TEST_MEM"));

    shared_ptr<mem_projectile> test_mem = m_map.create_mem("TEST_MEM", 2, {0xCD, 0xEF});

    REQUIRE_THROWS_AS(m_map.create_mem("TEST_MEM", 1), duplicate_mem_identifier_exception);

    REQUIRE_NOTHROW(m_map.find_mem("TEST_MEM"));
    REQUIRE(m_map.contains_mem("TEST_MEM"));

    REQUIRE(test_mem.use_count() == 2);  //stored in local variable and map

    m_map.remove_mem("TEST_MEM");

    REQUIRE_THROWS_AS(m_map.find_mem("TEST_MEM"), unallocated_mem_identifier_exception);
    REQUIRE_FALSE(m_map.contains_mem("TEST_MEM"));

    REQUIRE(test_mem.use_count() == 1);  //should be removed from the map
}

TEST_CASE("testing of memory map external memory", "[memory][mem_mapping]") {
    shared_ptr<mem_projectile> test_proj = shared_ptr<mem_projectile>(new mem_projectile(2));
    shared_ptr<mem_interstellar> test_interst = shared_ptr<mem_interstellar>(new mem_interstellar(2));

    memory_map m_map;

    m_map.import_external_mem("TEST_PROJ", test_proj);
    REQUIRE_THROWS_AS(m_map.import_external_mem("TEST_PROJ", test_interst), duplicate_mem_identifier_exception);

    m_map.import_external_mem("TEST_INTERST", test_interst);

    REQUIRE(test_proj.use_count() == 2);
    REQUIRE(test_interst.use_count() == 2);

    shared_ptr<mem_projectile> test_proj_clone = m_map.find_mem("TEST_PROJ");
    shared_ptr<mem_projectile> test_interst_clone = m_map.find_mem("TEST_INTERST");

    REQUIRE(test_proj_clone.use_count() == 3);
    REQUIRE(test_interst_clone.use_count() == 3);

    REQUIRE_FALSE(test_proj_clone->get_has_update());
    REQUIRE_FALSE(test_interst_clone->get_has_update());

    test_proj->set_has_update(true);
    test_interst->set_has_update(true);

    REQUIRE_FALSE(test_proj_clone->get_has_update());
    REQUIRE(test_interst_clone->get_has_update());
}