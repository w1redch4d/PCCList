#include "../include/pcclist/pcclist.h"
#include <cstdint>
#include <cstring>
#include <string>

// This is the entry point libFuzzer expects:
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    PCCList::List L;

    //todo
}