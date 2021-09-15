#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>

#include "interpreter/script/script.hpp"

using namespace std;
using namespace nlohmann;

int main(int argc, char* argv[]) {
    // json test = json::parse("{\"val\" : 15}");
    // cout << "Json file: " << test.dump() << endl;
    // cout << "Val: " << to_string(test["val"]) << endl;

    linker lnk;
    shared_ptr<invokable> invk(new script(invoke_def({}, {}, {}), &lnk, "test_program.heli"));

    memory_map* init_mem = invk->get_initial_mem();
    memory_map* out_mem = invk->get_output_mem();

    init_mem->create_mem("inp", 1)->set_bytes({0x01});
    invk->invoke();

    assert(out_mem->contains_mem("out_1"));
    assert(out_mem->contains_mem("out_2"));

    uint8_t val_out_1 = *(uint8_t*)out_mem->find_mem("out_1")->get_sub_block_addr(0, 1);
    uint8_t val_out_2 = *(uint8_t*)out_mem->find_mem("out_2")->get_sub_block_addr(0, 1);

    cout << "Value of out_1: " << to_string(val_out_1) << "\n";
    cout << "Value of out_2: " << to_string(val_out_2) << endl;
}