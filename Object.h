#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <map>
#include <string>
#include <utility>

class Object {
    public:
        Object(std::string &);
        ~Object();
        void addDependent(Object *, int);
        void setParent(Object *);
        void addValue(std::string &);
    private:
        std::string name;
        Object *parent;
        std::map<Object *, int> dependents;
        std::vector<std::string> values;
};

#endif