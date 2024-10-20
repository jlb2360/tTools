#pragma once

#include <fstream>
#include <string>
#include <cstdint>
#include <cstring>

#include "result.h"


// creating struct of a todo

struct todo {
    char task_name[50];
    bool done;
    char description[200];

    todo(const char* n, bool d, const char* de): done(d){
        std::strncpy(task_name, n, sizeof(task_name)-1);
        task_name[sizeof(task_name) - 1] = '\0';

        std::strncpy(description, de, sizeof(description)-1);
        description[sizeof(description)-1] = '\0';
    } 
    todo(): done(false) {
        std::memset(task_name, 0, sizeof(task_name));
        std::memset(description, 0, sizeof(description));
    }
};

// creating struct for a header

struct header {
    int8_t version;
    int16_t todo_num;

    header(int8_t v, int16_t tn) : version(v), todo_num(tn) {}
    header(): version(0), todo_num(0) {};
};

// function for manipulating the todo file

std::fstream open_file(std::string);

void append_todo(std::string, todo);

Result<todo, std::string> get_todo(std::string, const char*);

void finish_todo(std::string, const char*);

void delete_todo(std::string, const char*);

void print_all(std::string);

void print_todo(todo);
