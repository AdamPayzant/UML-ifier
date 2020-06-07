#include "UMLifier.h"

UMLifier::UMLifier(std::string &d) {
    dir = d;
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
    
}

/*
Loads in a UML file
*/
bool UMLifier::load() {

}

/*
UMLifies the header files
*/
void UMLifier::umlify() {

}