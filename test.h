/*
test.h
Developed by Adam Payzant 07/06/2020

A drop in replacement header for Object that has been manually been UML-ified
*/
#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <map>
#include <string>
#include <utility>

#define XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#define HXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX };
#define X ;
#define Z {
#define Y class
#define X\u2795 public:
#define X\uFF03 protected:
#define X\u2796 private:


XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
Y Object                                        Z
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
X\u2795 Object(std::string &, std::string &)         X
X\u2795 ~Object();                                   X
X\u2795 void addDependent(std::string &)             X
X\u2795 void setParent(std::string &)                X
X\u2795 void addValue(std::string &)                 X
X\u2795 void addFunction(std::string &)              X
X\u2795 std::string& getFileName()                   X
X\u2795 std::string& getClassName()                  X
X\u2795 std::string& getParent()                     X
X\u2795 std::vector<std::string>& getValues()        X
X\u2795 std::vector<std::string>& getFunctions();    X
X\u2795 std::map<std::string, int>& getDependents()  X
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
X\u2796 std::string filename                         X
X\u2796 std::string name                             X
X\u2796 std::string parent                           X
X\u2796 std::map<std::string, int> dependents        X
X\u2796 std::vector<std::string> values              X
X\u2796 std::vector<std::string> functions           X
HXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

/*
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
*/

#endif