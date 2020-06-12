/*
Object.h
Developed by Adam Payzant 07/06/2020

Stores class information to generate a UML
*/
#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <map>
#include <string>
#include <utility>

class Object {
    public:
        Object(std::string &, std::string &);
        ~Object();
        void addDependent(std::string &);
        void addDependent(std::string &, int);
        void setParent(std::string &);
        void addValue(std::string &);
        void addFunction(std::string &);

        std::string& getFileName();
        std::string& getClassName();
        std::string& getParent();
        std::vector<std::string>& getValues();
        std::vector<std::string>& getFunctions();
        std::map<std::string, int>& getDependents();
    private:
        std::string filename;
        std::string name;
        std::string parent;
        std::map<std::string, int> dependents;
        std::vector<std::string> values;
        std::vector<std::string> functions;
};

#endif