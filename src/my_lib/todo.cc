
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdio>

#include "todo.h"

void print_todo(todo Tprint){
    std::cout << Tprint.task_name << ": ";
    if (Tprint.done == true){
        std::cout << "[x]\n";
    } else {
        std::cout << "[ ]\n";
    }

    std::cout << "Description: " << Tprint.description << std::endl;
}

void print_all(std::string fname){
    auto file = open_file(fname);

    todo Tprint;

    header h;
    file.read(reinterpret_cast<char*>(&h), sizeof(h));

    std::cout << "Version: " << h.version << std::endl;
    std::cout << "Number of todos: " << h.todo_num << std::endl;

    while (file.read(reinterpret_cast<char*>(&Tprint), sizeof(Tprint))){
        std::cout << Tprint.task_name << ": ";
        if (Tprint.done == true){
            std::cout << "[x]\n";
        } else {
            std::cout << "[ ]\n";
        }

        std::cout << "Description: " << Tprint.description << std::endl;
    }

}

void delete_todo(std::string fname, const char* task_name){
    std::fstream file;
    
    file = open_file(fname);

    // open a temp file to write to
    std::string tF = "temp";
    
    auto tFile = open_file(tF);

    header h;
    file.read(reinterpret_cast<char*>(&h), sizeof(h));
    
    h.todo_num = h.todo_num - 1;

    tFile.write(reinterpret_cast<char*>(&h), sizeof(h));

    todo temp_todo;

    while (file.read(reinterpret_cast<char*>(&temp_todo), sizeof(temp_todo))){
        if (std::strcmp(temp_todo.task_name, task_name) != 0){
            tFile.write(reinterpret_cast<char*>(&temp_todo), sizeof(temp_todo));
        }
    }


    std::stringstream ss;
    std::stringstream tSS;
    const char* homeDir = std::getenv("HOME");

    ss << std::string(homeDir) << "/.tTools/" << fname << ".bin";
    tSS << std::string(homeDir) << "/.tTools/" << tF << ".bin";

    std::remove(ss.str().c_str()); 

    std::rename(tSS.str().c_str(), ss.str().c_str());

}

void append_todo(std::string fname, todo T){
    std::fstream file;

    file = open_file(fname);

    // Read the header
    header h;
    file.read(reinterpret_cast<char*>(&h), sizeof(h));

    if (!file) {
        std::cerr << "Error reading header!" << std::endl;
        file.close();
        return;
    }

     // Move to the end of the file to append the new task
    file.seekp(0, std::ios::end);

    // Write the new task to the end of the file
    file.write(reinterpret_cast<char*>(&T), sizeof(T));

    if (!file) {
        std::cerr << "Error writing the new task!" << std::endl;
        file.close();
        return;
    }

    h.todo_num += 1;

    // Move back to the beginning of the file to update the header
    file.seekp(0, std::ios::beg);
    file.write(reinterpret_cast<char*>(&h), sizeof(h));

    if (!file) {
        std::cerr << "Error updating the header!" << std::endl;
    } else {
        std::cout << "Successfully appended task: " << T.task_name << " with description: " << T.description << std::endl;
    }

    file.close();
}

Result<todo, std::string> get_todo(std::string fname, const char* task_name){

    todo returnT;
    
    std::fstream file;

    file = open_file(fname);

    // Read the header
    header h;
    file.read(reinterpret_cast<char*>(&h), sizeof(h));

    if (!file) {
        file.close();
        return Result<todo, std::string>("Error reading header!\n");
    }

    bool found = false;

    while (file.read(reinterpret_cast<char*>(&returnT), sizeof(returnT))){
        if (std::strcmp(returnT.task_name, task_name) == 0){
            found = true;
            break;
        }
    }

    if (found != true){
       std::cout << "Todo with name '" << task_name << "' not found." << std::endl;  
        return Result<todo, std::string>("Todo not found");
    }

    return Result<todo, std::string>(returnT);
}

void finish_todo(std::string fname, const char* task_name){

    todo updateT;
    
    std::fstream file;

    file = open_file(fname);

    // Read the header
    header h;
    file.read(reinterpret_cast<char*>(&h), sizeof(h));

    if (!file) {
        std::cerr << "Error reading header!" << std::endl;
        file.close();
    }

    bool found = false;

    while (file.read(reinterpret_cast<char*>(&updateT), sizeof(updateT))){
        if (std::strcmp(updateT.task_name, task_name) == 0){
            found = true;
            break;
        }
    }

    if (found == true){
        updateT.done = true;
        file.seekp(-static_cast<int>(sizeof(todo)), std::ios::cur);
        file.write(reinterpret_cast<char*>(&updateT), sizeof(updateT));
    } else {
       std::cout << "Todo with name '" << task_name << "' not found." << std::endl;  
    }


}


std::fstream open_file(std::string fname){
    std::stringstream ss;
    const char* homeDir = std::getenv("HOME");

    ss << std::string(homeDir) << "/.tTools/" << fname << ".bin";

    std::fstream f;

    f.open(ss.str(), std::ios::in | std::ios::out | std::ios::binary);


    if (!f.good()){
        std::ofstream newf(ss.str());

        if (!newf){
            std::cout << "the file did not open correctly.\n";
            exit(0);
        }
        header h = header(1, 0);
        
        newf.write(reinterpret_cast<const char*>(&h), sizeof(h));
        

        f.open(ss.str(), std::ios::in | std::ios::out | std::ios::binary);
    }

    return f;
}
