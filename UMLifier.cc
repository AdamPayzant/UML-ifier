/*
UMLifier.cc
Developed by Adam Payzant 07/06/2020
*/
#include "UMLifier.h"

UMLifier::UMLifier(std::string &p) {
    path = p;
}

/*
Deletes all Object objects from the vector. As it stands nothing else should need to be explicitly deleted
*/
UMLifier::~UMLifier() {
    for(auto it = objects.begin(); it != objects.end(); ++it) {
        delete(*it);
    }
}

/*
Generates a UML file for the project from the header files
*/
void UMLifier::generate() {
    std::vector<std::string> headers;
    std::vector<std::thread> threads;
    // Gets all header names
    struct dirent *entry;
    DIR *dir = opendir(path.c_str());
    if(dir == NULL) {
        return;
    }
    while((entry = readdir(dir)) != NULL) {
        if(entry->d_type == DT_REG) {
            std::string name = entry->d_name;
            if(name.substr(name.size() - 2, name.size() - 1) == ".h") {
                headers.push_back(name);
            }
        }
    }
    // Sends generation tasks off to other threads
    for(auto f = headers.begin(); f != headers.end(); ++f) {
        threads.emplace_back(std::thread (generateOne, *f));
    }
    // Waits for all threads to finish
    for(auto& th : threads) {
        th.join();
    }
}

/*
Generates class data from a header file then pushes it to the object vector
*/
// TODO
void UMLifier::generateOne(std::string &fileName) {

}

/*
Loads in a UML file
*/
// TODO
bool UMLifier::load() {

}

/*
UMLifies the header files
*/
// TODO
void UMLifier::umlify() {

}