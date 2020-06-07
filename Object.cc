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
void Object::addDependent(Object *depend, int c) {
    dependents.insert(std::pair<Object *, int>(depend, c));
}

/*
Sets a parent class for it
*/
void Object::setParent(Object *p) {
    parent = p;
}

/*
Adds a primative data type to the object's UML
*/
void Object::addValue(std::string &val) {
    values.push_back(val);
}