#include <iostream>

#include <nlohmann/json.hpp>

#include "my_lib.h"
#include "config.hpp"
#include <cxxopts.hpp>

int main(){

    std::cout << project_name << '\n';
    std::cout << project_version << '\n';

    std::cout << "JSON_Lib_Version:"
              << NLOHMANN_JSON_VERSION_MAJOR << "."
              << NLOHMANN_JSON_VERSION_MINOR << "."
              << NLOHMANN_JSON_VERSION_PATCH << "\n";

    std::cout << "CXXOPTS:"
              << CXXOPTS__VERSION_MAJOR << "."
              << CXXOPTS__VERSION_MINOR << "."
              << CXXOPTS__VERSION_PATCH << "\n";


    print_hello();

    return 0;
}
