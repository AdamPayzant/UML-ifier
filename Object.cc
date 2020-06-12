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