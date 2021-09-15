#include "interpreter/script/script_parser.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <utility>
#include <vector>

#include "interpreter/script/linker.hpp"
#include "interpreter/script/script.hpp"

using namespace std;
using namespace nlohmann;

map<string, pair<string, string>> parse_script_directory(string dir_path) {
    map<string, pair<string, string>> m_script;

    //NOTE: the first value in the pair is the definition file (.helidef) while
    //the second value is the instruction file (.heli)

    for (const auto& dir_entry : filesystem::directory_iterator(dir_path)) {
        string dir_entry_path = dir_entry.path();

        size_t dir_end = dir_entry_path.rfind('/') + 1;
        string local_file = dir_entry_path.substr(dir_end, dir_entry_path.length() - dir_end);

        size_t name_end = local_file.rfind('.');
        string script_name = local_file.substr(0, name_end);
        string extension = local_file.substr(name_end + 1, script_name.length() - (name_end + 1));

        //cout << "Finished parsing values for script: " << script_name << endl;

        map<string, pair<string, string>>::iterator scrpt = m_script.find(script_name);
        if (m_script.find(script_name) == m_script.end()) {
            //if the file is not already in the map
            if (extension == "helidef")
                m_script.insert(pair<string, pair<string, string>>(script_name, {local_file, ""}));
            else if (extension == "heli")
                m_script.insert(pair<string, pair<string, string>>(script_name, {"", local_file}));
        } else {
            //if the script is already in the map (partially completed)
            if (extension == "helidef")
                scrpt->second.first = local_file;
            else if (extension == "heli")
                scrpt->second.second = local_file;
        }
    }

    // cout << "Finished generating map" << endl;

    // for (pair<string, pair<string, string>> entry : m_script) {
    //     cout << "Script name: " << entry.first << endl;
    //     cout << "\tScript definition: " << entry.second.first << endl;
    //     cout << "\tScript instruction: " << entry.second.second << endl;
    // }

    return m_script;
}

shared_ptr<script_block> parse_script_block(string file_path, map<string, pair<string, string>> script_files) {
    ifstream file_strm(file_path);
    json script_block;
    file_strm >> script_block;

    vector<shared_ptr<script>> scripts;

    //parses the inputs to get the various scripts and execution order
    vector<pair<size_t, string>> vec_script_order;
    for (auto& script : script_block["scripts"]) {
        size_t script_order = script["script-order"];
        string script_id = script["script-id"];

        vec_script_order.push_back({script_order, script_id});
    }

    //takes the input scripts and orders them sequentially
    sort(vec_script_order.begin(), vec_script_order.end(), [](const pair<size_t, string>& s1, const pair<size_t, string>& s2) -> bool {
        if (s1.first == s2.first) {
            cerr << "Scripts cannot be assigned the same execution order" << endl;
            exit(EXIT_FAILURE);
        }
        return s1.first < s2.first;
    });

    for (const pair<size_t, string>& s : vec_script_order) {
        cout << "Script -> order: " << s.first << "\tname: " << s.second << endl;
    }



    return NULL;
}

shared_ptr<script> parse_script(string file_path) {
    // parses the script instruction file adn generates a script ifle
}