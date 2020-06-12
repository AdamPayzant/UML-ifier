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
#include <fstream>
#include <unordered_set>

#include "Object.h"

// Change if not using 4 space length tabs
#define TABSIZE 4

class UMLifier {
    public:
        UMLifier(std::string &);
        ~UMLifier();
        void generate();
        void save();
        bool load();
        void umlify();
    private:
        bool loaded;
        void generateOne(std::string &);
        std::string path;
        std::vector<Object *> objects;
};

#endif