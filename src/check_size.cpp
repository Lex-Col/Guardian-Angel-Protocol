#include <iostream>
#include "gap_struct.hpp"

int main() {
    CHA_Struct_t test_struct;
    std::cout << "Actual Size: " << sizeof(test_struct) << " bytes" << std::endl;
    if (sizeof(test_struct) == 322) {
        std::cout << "STATUS: MEMORY IS SEALED." << std::endl;
        return 0;
    } else {
        std::cerr << "STATUS: CRITICAL FAILURE." << std::endl;
        return 1;
    }
}
