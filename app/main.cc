#include <iostream>

#include "todo.h"
#include <cxxopts.hpp>

void add_todo(std::string fname){
    std::string todo_name;
    std::string description;

    std::cout << "What is the name\n"; 
    std::getline(std::cin, todo_name);
    std::cout << "What is the description\n";
    std::getline(std::cin, description);

    todo todo_t = todo(todo_name.c_str(), false, description.c_str());

    append_todo(fname, todo_t);
}


int main(int argc, char *argv[]){

    cxxopts::Options options("Todo App", "This is a terminal based todo app");

    options.add_options()
        ("i,input", "File name holding todo list", cxxopts::value<std::string>())
        ("h,help", "print usage")
        ("a,add", "We want to add to todo")
        ("d,delete", "We want to delete a todo")
        ("c,complete", "We have completed this task")
        ("g,get", "print out the specific todo")
        ("p,print", "print the entire todo list")
    ;

    auto result = options.parse(argc, argv);

    if (result.count("help")){
        std::cout << options.help() << std::endl;
        return 0;
    }

    if (result.count("input")){
        std::string fname = result["input"].as<std::string>();

        if (result.count("add")){
            add_todo(fname);
        } else if (result.count("delete")){
            std::string todo_name;

            std::cout << "What is the name\n"; 
            std::getline(std::cin, todo_name);
            delete_todo(fname, todo_name.c_str());
        } else if (result.count("complete")){
            std::string todo_name;

            std::cout << "What is the name\n"; 
            std::getline(std::cin, todo_name);
            finish_todo(fname, todo_name.c_str());
        } else if (result.count("get")){
            std::string todo_name;

            std::cout << "What is the name\n"; 
            std::getline(std::cin, todo_name);
            auto todo_result = get_todo(fname, todo_name.c_str());
            if (todo_result.is_ok()){
                print_todo(todo_result.value());
            } else {
                std::cout << "I could not retrieve the todo\n";
            }
        } else if (result.count("print")){
            print_all(fname);
        }
    } else {
        std::cerr << "There is no file name given" << std::endl;
        return 1;
    }




    return 0;
}
