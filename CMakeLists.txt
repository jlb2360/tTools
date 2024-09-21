# 0.) Create Source and CMakeFile
# 1.) Create a build directory
# 2.) cd build
# 3.) cmake ..
# 4.) cmake --build .
# 5.) ./Executable


cmake_minimum_required(VERSION 3.22)

project(
    CppProjectTemplate
    VERSION 1.0.0
    LANGUAGES C CXX)


# Global CMake settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Options
option(ENABLE_TESTING "Enable a Unit Testing Build" ON)

option(ENABLE_WARNINGS "Enable Compiler Warnings" ON)
option(ENABLE_WARNINGS_AS_ERRORS "Enable warnings as errors" OFF)

option(ENABLE_SANITIZE_ADDR "Enable Address Sanitizer" OFF)
option(ENABLE_SANITIZE_UNDEF "Enable Undefined Behavior Sanitizer" OFF)
option(ENABLE_SANITIZE_LEAK "Enable Leak Sanitizer" OFF)
option(ENABLE_SANITIZE_THREAD "Enable Thread Sanitizer" OFF)

option(ENABLE_LTO "Enable Link Time Optimization" ON)

# Project/library name
set(LIBRARY_NAME Library)
set(EXECUTABLE_NAME Executable)

# CMAKE MODULES
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")
include(AddGitSubmodule)
include(Docs)
include(ConfigSafeGuards)



if (ENABLE_WARNINGS)
    include(Warnings)
endif()

if (ENABLE_SANITIZE_ADDR
        OR ENABLE_SANITIZE_UNDEF
        OR ENABLE_SANITIZE_LEAK
        OR ENABLE_SANITIZE_THREAD
    )

    include(Sanitizers)
    add_sanitizer_flags()
endif()

if (ENABLE_LTO)
    include(LTO)
endif()

include(CPM)
cpmaddpackage("gh:nlohmann/json#v3.11.3")
cpmaddpackage("gh:jarro2783/cxxopts#v3.2.0")
if(ENABLE_TESTING)
    cpmaddpackage("gh:catchorg/Catch2#v3.5.3")
    list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
endif()

add_subdirectory(configured)
add_subdirectory(external)
add_subdirectory(src)
add_subdirectory(app)
if(ENABLE_TESTING)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()
