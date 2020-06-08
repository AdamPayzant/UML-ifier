/*
Object.cc
Developed by Adam Payzant 07/06/2020
*/
#include "Object.h"

Object::Object(std::string &n) {
    name = n;
}

/*
As it stands, Objects shouldn't have to worry about explicit deletions.
*/
Object::~Object() {

}

/*
Adds an object dependency and the number of objects present
*/
void Object::addDependent(std::string &depend, int c) {
    dependents.insert(std::pair<std::string, int>(depend, c));
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