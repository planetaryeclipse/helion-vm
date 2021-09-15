#include "interpreter/instr_parser.hpp"

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "interpreter/instr_except.hpp"
#include "interpreter/instr_runner.hpp"
#include "util/string_util.hpp"

using namespace std;

text_instr parse_instr_line(string line) {
    if (line.length() == 0)
        throw invalid_instruction_file_line_exception(line);

    //NOTE: a line with only whitespace is not considered a blank line

    size_t instr_id_end = line.find(' ', 0);
    if (instr_id_end == 0 || instr_id_end == line.length() - 1)
        //if there is no ID or there is a space with no args
        throw invalid_instruction_file_line_exception(line);
    else if (instr_id_end == string::npos)  //whole line is instr ID
        return text_instr(line, {});

    if (instr_id_end != string::npos && line.find(' ', instr_id_end + 1) != string::npos)
        //cannot have space as part of argument
        throw invalid_instruction_file_line_exception(line);

    string id = line.substr(0, instr_id_end);
    vector<string> args;
    try {
        args = parse_delim_vals(line.substr(instr_id_end + 1, line.length() - (instr_id_end + 1)), ',');
    } catch (invalid_argument& e) {
        //catches and redirects the exception
        throw invalid_instruction_file_line_exception(line);
    }

    return text_instr(id, args);
}

vector<text_instr> parse_instr_file(string file_path) {
    ifstream file(file_path);
    if (!file)
        throw invalid_argument("Instruction file does not exist");

    //splits the file into a collection of lines
    vector<string> lines;
    for (string line; getline(file, line);) {
        line.erase(remove(line.begin(), line.end(), '\n'), line.end());
        lines.push_back(line);  //adds the line without the newline character
    }
    return parse_instr_file(lines);
}

vector<text_instr> parse_instr_file(vector<string> lines) {
    vector<text_instr> instrs;
    for (string line : lines) {
        if (line.length() == 0 || line.starts_with('%'))
            continue;  //ignores blank or commented lines (whitespace is not blank)
        instrs.push_back(parse_instr_line(line));
    }
    return instrs;
}