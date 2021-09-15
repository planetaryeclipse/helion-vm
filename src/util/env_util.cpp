#include "util/env_util.hpp"

#include <cstring>
#include <string>

using namespace std;

bool is_env_enabled(string env_var) {
    const char* env_val = getenv(env_var.c_str());
    return env_val != NULL && strcmp(env_val, "1") == 0;
}