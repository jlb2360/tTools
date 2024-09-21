
#include <iostream>
#include <cstdint>

#include <nlohmann/json.hpp>


#include "my_lib.h"

/**
 * @brief Prints out hello world and test Libraries.
 *
 */

void print_hello(){
    std::cout << "Hello World\n";
}


std::uint32_t factorial(std::uint32_t number){
    return number <=1 ? 1 : factorial(number-1) * number;
}
