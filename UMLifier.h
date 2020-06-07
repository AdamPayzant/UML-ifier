/*
UMLifier.h
Developed by Adam Payzant 07/06/2020

Can Generate or Load UML files and turn header files into UMLs for the project
*/
#ifndef UMLIFIER_H
#define UMLIFIER_H

#include <vector>

#include "Object.h"

class UMLifier {
    public:
        UMLifier(std::string &);
        ~UMLifier();
        void generate();
        bool load();
        void umlify();
    private:
        std::string dir;
        std::vector<Object *> objects;
};

#endif