#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <map>
#include <string>

class Object {
    public:
        Object();
        ~Object();
        
    private:
        Object *parent;
        std::map<Object *, int> dependents;
        std::vector<std::string *> values;
};

#endif