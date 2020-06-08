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
    // The elements of an object
    std::string name;
    std::string parent;
    std::vector<std::string> attributes;

    std::ifstream file(path + fileName);

    /*
    This char is to denote an attributes visibility
    0 - Not in class
    '+' - In public
    '#' - In protected
    '-' - In private
    */
    char vis = 0;

    std::string line;
    while(getline(file, line)) {
        if(vis > 0) {
            if(line.find(':') != std::string::npos) {
                if(line.at(TABSIZE+2) == 'b') vis = '+';
                else if(line.at(TABSIZE+2) == 'o') vis = '#';
                else if(line.at(TABSIZE+2) == 'i') vis = '-';
            }
            else {
                line = line.substr(2 * TABSIZE, line.length() - 2 * TABSIZE);
                attributes.push_back(vis + " " + line);
            }
        }
        else {
            // Check if a class definition begins
            if(line.substr(0, 5) == "class") {
                vis = '+';
                if(line.find(':') == std::string::npos) { // No Inheritance
                    name = line.substr(6, line.length() - 8);
                }
                else { // TODO: Inheritance
                    int col = line.find(':');
                    name = line.substr(6, col - 7);
                    parent = line.substr(col + 1, line.length() - col); // This line will not work
                }
            }
        }
    }
    if(name != "") { // This is here in case someone uses something like a defs.h
        // TODO
        Object *obj = new Object(name);
    }
}

/*
Saves the UML file
*/
void UMLifier::save() {

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