#include <cstring>
#include <filesystem>
#include <iostream>

#include "interpreter/instr_parser.hpp"
#include "interpreter/instr_runner.hpp"
#include "memory/mem_except.hpp"
#include "memory/mem_mapping.hpp"
#include "util/mem_util.hpp"
#include "util/string_util.hpp"
#include "util/term_colors.hpp"
#include "util/value_util.hpp"

using namespace std;

void run_instrs(vector<text_instr> instrs, memory_map* m_map);

void parse_arg(string arg, memory_map* m_map);
inline void disp_inval_arg(string arg);

bool show_mem_after_instr() {
    const char* env = getenv("DEBUG_HELION_INSTR_PROG");
    return env != NULL && strcmp(env, "1") == 0;
}

int main(int argc, char* argv[]) {
    cout << "Helion Instruction Interpreter" << endl;
    cout << "Author: Samuel Street" << '\n'
         << endl;

    if (argc < 2) {
        cerr << foreground_green << "Instruction file not specified" << foreground_reset << endl;
        exit(EXIT_FAILURE);
    } else if (!filesystem::exists(argv[1])) {
        cerr << foreground_green << "Instruction file does not exist" << foreground_reset << endl;
        exit(EXIT_FAILURE);
    }

    cout << foreground_green << "Loading instruction file: " << foreground_reset << argv[1] << endl;
    vector<text_instr> instrs = parse_instr_file(argv[1]);

    cout << foreground_green << "Loading memory specified in arguments..." << foreground_reset << endl;
    memory_map m_map;

    //skips over application and file arguments
    for (int i = 2; i < argc; i++)
        parse_arg(argv[i], &m_map);

    cout << endl;

    cout << "Memory map prior to execution:" << endl;
    cout << m_map.as_string() << endl;  //result includes a newline

    //separate setup from execution
    //cout << endl;

    //runs loaded instructions
    run_instrs(instrs, &m_map);

    cout << "\nMemory map following execution:" << endl;
    cout << m_map.as_string() << endl;  //includes an additional newline

    cout << "Interpreter has finished!" << endl;

    return EXIT_SUCCESS;
}

string get_text_instr_as_text(text_instr instr) {
    string instr_str = instr.get_id() + " ";
    vector<string> args = instr.get_args();

    for (int i = 0; i < args.size(); i++) {
        instr_str = instr_str + args.at(i);
        if (i != args.size() - 1)
            instr_str = instr_str + ',';
    }

    return instr_str;
}

void run_instrs(vector<text_instr> instrs, memory_map* m_map) {
    cout << foreground_red << "Running instructions..." << foreground_reset << endl;

    size_t p_instr = 0;
    while (p_instr < instrs.size()) {
        cout << foreground_red << "Instruction: " << foreground_reset << p_instr << foreground_yellow << " --> " << get_text_instr_as_text(instrs.at(p_instr)) << foreground_reset << endl;
        try {
            instrs.at(p_instr).run_instr(m_map, &p_instr, instrs.size());
        } catch (invalid_mem_size_exception& e) {
            cout << e.what() << endl;
            exit(EXIT_FAILURE);
        }

        if (show_mem_after_instr())
            cout << '\n'
                 << m_map->as_string() << endl;  //extra newline is included in returned string
    }

    cout << foreground_red << "Finished running instructions!" << foreground_reset << endl;
}

void parse_arg(string arg, memory_map* m_map) {
    cout << foreground_green << "Parsing argument: " << foreground_reset << arg << endl;

    size_t mem_id_fin = arg.find('=');
    if (mem_id_fin == string::npos)
        disp_inval_arg(arg);

    string mem_id, mem_vals;
    mem_id = arg.substr(0, mem_id_fin);

    //prevents an indexing exception if there is nothing provided after '='
    if (mem_id_fin == arg.length() - 1)
        disp_inval_arg(arg);
    mem_vals = arg.substr(mem_id_fin + 1, arg.length() - (mem_id_fin + 1));

    if (mem_id.length() == 0 || mem_vals.length() == 0 || !is_valid_mem_identifier(mem_id))
        disp_inval_arg(arg);

    vector<string> vals = {};
    try {
        vals = parse_delim_vals(mem_vals, ',');
    } catch (invalid_argument& e) {
        cout << foreground_green << "Invalid delimited value list: " << foreground_reset << mem_vals << endl;
        exit(EXIT_FAILURE);
    }

    vector<uint8_t> uc_vals = {};

    for (string val : vals) {
        size_t uc_val = get_val(val);
        if (uc_val > 255) {
            cout << foreground_green << "Byte-value provided is higher than allowed (255)" << foreground_reset << endl;
            exit(EXIT_FAILURE);
        }

        uc_vals.push_back(uc_val);
    }

    m_map->create_mem(mem_id, uc_vals.size(), uc_vals);
}

inline void disp_inval_arg(string arg) {
    cerr << foreground_green << "Invalid argument string: " << foreground_reset << arg << endl;
    exit(EXIT_FAILURE);
}