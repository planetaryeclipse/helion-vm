#include <filesystem>
#include <iostream>
#include <memory>

#include "interpreter/script/invokable.hpp"
#include "interpreter/script/linker.hpp"
#include "interpreter/script/script.hpp"
#include "interpreter/script/script_parser.hpp"
#include "util/term_colors.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    cout << "Helion Program Interpreter" << endl;
    cout << "Author: Samuel Street" << '\n'
         << endl;

    if (argc < 3) {
        cerr << foreground_red << "Script file directory not specified" << foreground_reset << endl;
        exit(EXIT_FAILURE);
    } else if (!filesystem::is_directory(argv[2])) {
        cerr << foreground_red << "Script file directory is not a directory" << foreground_reset << endl;
        exit(EXIT_FAILURE);
    } else if (argc < 2) {
        cerr << foreground_red << "Program file not specified" << foreground_reset << endl;
        exit(EXIT_FAILURE);
    } else if (!filesystem::exists(argv[1])) {
        cerr << foreground_red << "Program file does not exist" << foreground_reset << endl;
        exit(EXIT_FAILURE);
    }

    map<string, pair<string, string>> m_script_dir = parse_script_directory(argv[2]);
    parse_script_block(argv[1], m_script_dir);
    //shared_ptr<script_block> p_script_block = parse_script_block(argv[1]);
}