/*
Object.cc
Developed by Adam Payzant 07/06/2020
*/
#include "Object.h"

/*
Takes a filename and class name
*/
Object::Object(std::string &f, std::string &n) {
    filename = f;
    name = n;
}

/*
As it stands, Objects shouldn't have to worry about explicit deletions.
*/
Object::~Object() {
    
}

void Object::print() {
    std::cout << "Name: " << name << std::endl;
    std::cout << "File: " << filename << std::endl;
    if(!parent.empty()) {
        std::cout << "Parent: " << parent << std::endl;
    }
    std::cout << "Printing values: " << std::endl;
    for(auto v = values.begin(); v != values.end(); ++v) {
        std::cout << "  " << *v << std::endl;
    }
    std::cout << "Print dependents: " << std::endl;
    for(auto d = dependents.begin(); d != dependents.end(); ++d) {
        std::cout << "  " << d->first << ", " << d->second << std::endl;
    }
}

/*
Adds a single object dependency. 
-1 indicates infinite
*/
void Object::addDependent(std::string &depend) {
    if(dependents[depend] == -1) return;
    dependents[depend] += 1;
}

/*
Adds an object dependency and the number of objects present
-1 indicates infine occurances
*/
void Object::addDependent(std::string &depend, int c) {
    if(dependents[depend] == -1) return;
    if(c > 0) {
        dependents[depend] += c;
    }
    else {
        dependents[depend] = -1;
    }
}

/*
Sets a parent class for it
*/
void Object::setParent(std::string &p) {
    parent = p;
}

/*
Adds a primative data type to the object's UML
*/
void Object::addValue(std::string &val) {
    values.push_back(val);
}

void Object::addFunction(std::string &func) {
    functions.push_back(func);
}

void Object::addDependentLine(std::string &line) {
    dependentLines.push_back(line);
}

// Getters
std::string& Object::getFileName() {
    return(filename);
}

std::string& Object::getClassName() {
    return(name);
}

std::string& Object::getParent() {
    return(parent);
}

std::vector<std::string>& Object::getValues() {
    return(values);
}

std::vector<std::string>& Object::getFunctions() {
    return(functions);
}

std::map<std::string, int>& Object::getDependents() {
    return(dependents);
}

std::vector<std::string>&  Object::getDependentLines() {
    return(dependentLines);
}