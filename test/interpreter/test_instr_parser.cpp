#include <catch2/catch_all.hpp>
#include <string>

#include "interpreter/instr_except.hpp"
#include "interpreter/instr_parser.hpp"
#include "interpreter/instr_runner.hpp"

using namespace std;

TEST_CASE("testing of parsing instruction lines", "[instr_parser][interpreter]") {
    REQUIRE_THROWS_AS(parse_instr_line(""), invalid_instruction_file_line_exception);
    REQUIRE_THROWS_AS(parse_instr_line(" "), invalid_instruction_file_line_exception);

    REQUIRE_NOTHROW(parse_instr_line("ALLOC"));
    REQUIRE_THROWS_AS(parse_instr_line(" ALLOC"), invalid_instruction_file_line_exception);
    REQUIRE_THROWS_AS(parse_instr_line("ALLOC "), invalid_instruction_file_line_exception);
    REQUIRE_THROWS_AS(parse_instr_line("ALLOC  "), invalid_instruction_file_line_exception);

    REQUIRE_NOTHROW(parse_instr_line("ALLOC A"));
    REQUIRE_NOTHROW(parse_instr_line("ALLOC A,A"));
    REQUIRE_THROWS_AS(parse_instr_line("ALLOC ,"), invalid_instruction_file_line_exception);
    REQUIRE_THROWS_AS(parse_instr_line("ALLOC A,"), invalid_instruction_file_line_exception);
    REQUIRE_THROWS_AS(parse_instr_line("ALLOC ,A"), invalid_instruction_file_line_exception);

    text_instr test_instr = parse_instr_line("ALLOC arg1,arg2,arg3");
    REQUIRE(test_instr.get_id() == "ALLOC");
    REQUIRE(test_instr.get_args().size() == 3);
    REQUIRE(test_instr.get_args().at(0) == "arg1");
    REQUIRE(test_instr.get_args().at(1) == "arg2");
    REQUIRE(test_instr.get_args().at(2) == "arg3");
}

TEST_CASE("testing of parsing instruction file lines", "[instr_parser][interpreter]") {
    const vector<string> test_lines_valid = {
        "INSTR_1 VAL1,VAL2,VAL3",
        "INSTR_2 VAL1,VAL2",

        "% test comment before valid empty line",
        "",
        "% test comment after valid empty line",

        "INSTR_3 VAL1",
        "INSTR_4"};

    vector<text_instr> parsed_test_lines_valid;
    REQUIRE_NOTHROW(parsed_test_lines_valid = parse_instr_file(test_lines_valid));
    REQUIRE(parsed_test_lines_valid.size() == 4);

    REQUIRE(parsed_test_lines_valid.at(0).get_args().size() == 3);
    REQUIRE(parsed_test_lines_valid.at(1).get_args().size() == 2);
    REQUIRE(parsed_test_lines_valid.at(2).get_args().size() == 1);
    REQUIRE(parsed_test_lines_valid.at(3).get_args().size() == 0);

    const vector<string> test_lines_invalid_1 = {
        "% invalid empty line",
        "INSTR_1 VAL1",
        " ",
        "INSTR_2 VAL1"};

    const vector<string> test_lines_invalid_2 = {
        "% invalid leading space in front of instruction",
        "INSTR_1 VAL1",
        " INSTR_2 VAL1",
        "INSTR_3 VAL1"};

    const vector<string> test_lines_invalid_3 = {
        "% invalid leading space in front of comment",
        "INSTR_1 VAL1",
        " %INSTR_2",
        "INSTR_3 VAL1"};

    const vector<string> test_lines_invalid_4 = {
        "% invalid leading space in front of comment (also with following space)",
        "INSTR_1 VAL1",
        " % INSTR_2",
        "INSTR_3 VAL1"};

    REQUIRE_THROWS_AS(parse_instr_file(test_lines_invalid_1), invalid_instruction_file_line_exception);
    REQUIRE_THROWS_AS(parse_instr_file(test_lines_invalid_2), invalid_instruction_file_line_exception);
    REQUIRE_THROWS_AS(parse_instr_file(test_lines_invalid_3), invalid_instruction_file_line_exception);
    REQUIRE_THROWS_AS(parse_instr_file(test_lines_invalid_4), invalid_instruction_file_line_exception);
}

TEST_CASE("testing of parsing instruction file", "[instr_parser][interpreter]") {
    REQUIRE_THROWS_AS(parse_instr_file("interpreter/validation_scripts/test_no_exist.heli"), invalid_argument);

    vector<text_instr> parsed_test_valid;
    REQUIRE_NOTHROW(parsed_test_valid = parse_instr_file("interpreter/validation_scripts/test_valid.heli"));
    REQUIRE(parsed_test_valid.size() == 4);

    REQUIRE(parsed_test_valid.at(0).get_args().size() == 3);
    REQUIRE(parsed_test_valid.at(1).get_args().size() == 2);
    REQUIRE(parsed_test_valid.at(2).get_args().size() == 1);
    REQUIRE(parsed_test_valid.at(3).get_args().size() == 0);

    REQUIRE_THROWS_AS(parse_instr_file("interpreter/validation_scripts/test_invalid_1.heli"), invalid_instruction_file_line_exception);
    REQUIRE_THROWS_AS(parse_instr_file("interpreter/validation_scripts/test_invalid_2.heli"), invalid_instruction_file_line_exception);
    REQUIRE_THROWS_AS(parse_instr_file("interpreter/validation_scripts/test_invalid_3.heli"), invalid_instruction_file_line_exception);
    REQUIRE_THROWS_AS(parse_instr_file("interpreter/validation_scripts/test_invalid_4.heli"), invalid_instruction_file_line_exception);
}