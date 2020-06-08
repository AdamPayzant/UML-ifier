/*
UMLifier.h
Developed by Adam Payzant 07/06/2020

Can Generate or Load UML files and turn header files into UMLs for the project
*/
#ifndef UMLIFIER_H
#define UMLIFIER_H

#include <vector>
#include <thread>
#include <dirent.h>

#include "Object.h"

class UMLifier {
    public:
        UMLifier(std::string &);
        ~UMLifier();
        void generate();
        bool load();
        void umlify();
    private:
        void generateOne(std::string &);
        std::string path;
        std::vector<Object *> objects;
};

#endif