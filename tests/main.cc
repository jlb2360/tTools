#include <cstdio>
#define CATCH_CONFIG_MAIN
#include <iostream>

#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <sstream>


#include "todo.h"


todo create_todo(){
    todo T = todo("test", false, "testing the todo");
    return T;
}

std::fstream get_file(){
    std::string name = "test";

    auto f = open_file(name);

    return f;
}


TEST_CASE("File creation", "[todo_files]"){
    
    std::string name = "test";
    std::stringstream ss;
    const char* homeDir = std::getenv("HOME");

    ss << std::string(homeDir) << "/.tTools/" << name << ".bin";

    std::remove(ss.str().c_str()); 
    
    auto f = open_file(name);
    
    REQUIRE(f.good() == true);

    header h;

    f.read(reinterpret_cast<char*>(&h), sizeof(h));

    f.close();

    REQUIRE(h.version == 1);
    REQUIRE(h.todo_num == 0);
}


TEST_CASE("add ToDo", "[todo_files]"){

    std::string name = "test";
    todo T = create_todo();

    append_todo(name, T); 

    std::fstream f;
    f = get_file();

    f.seekg(0, std::ios::beg);
    header h;

    f.read(reinterpret_cast<char*>(&h), sizeof(h));

    REQUIRE(h.version == 1);
    REQUIRE(h.todo_num == 1);

    todo TRe;

    f.read(reinterpret_cast<char*>(&TRe), sizeof(TRe));

    REQUIRE(std::strcmp(TRe.task_name, T.task_name) == 0);
    REQUIRE(TRe.done == false);
    REQUIRE(std::strcmp(TRe.description, T.description) == 0);
}

TEST_CASE("Get ToDo", "[todo_files]"){
    
    std::string name = "test";
    todo T = create_todo();

    char todo_name[50] = "test";

    auto rt = get_todo(name, todo_name);

    REQUIRE(rt.is_ok());

    todo gt = rt.value();

    REQUIRE(std::strcmp(T.task_name, gt.task_name) == 0);
    REQUIRE(gt.done == false);
    REQUIRE(std::strcmp(T.description, gt.description) == 0);
}

TEST_CASE("Update ToDo", "[todo_files]"){
    std::string name = "test";

    char todo_name[50] = "test";
    
    finish_todo(name, todo_name);

    todo T = create_todo();

    auto rt = get_todo(name, todo_name);

    REQUIRE(rt.is_ok());

    todo gt = rt.value();

    REQUIRE(std::strcmp(T.task_name, gt.task_name) == 0);
    REQUIRE(gt.done == true);
    REQUIRE(std::strcmp(T.description, gt.description) == 0);
}

TEST_CASE("Delete ToDo", "[todo_files]"){
    std::string name = "test";
    char todo_name[50] = "test";
    
    delete_todo(name, todo_name);

    auto rt = get_todo(name, todo_name);

    REQUIRE(rt.is_ok() == false); 
}
