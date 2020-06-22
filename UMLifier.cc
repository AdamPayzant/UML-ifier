/*
UMLifier.cc
Developed by Adam Payzant 07/06/2020
*/
#include "UMLifier.h"

UMLifier::UMLifier(std::string &p) {
    path = p;
    loaded = false;
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
    std::vector<std::string> headers;
    std::vector<std::thread> threads;
    // Gets all header names
    struct dirent *entry;
    DIR *dir = opendir(path.c_str());
    if(dir == NULL) {
        return;
    }
    while((entry = readdir(dir)) != NULL) {
        if(entry->d_type == DT_REG) {
            std::string name = entry->d_name;
            if(name.substr(name.size() - 2, name.size() - 1) == ".h") {
                headers.push_back(name);
            }
        }
    }
    delete(entry);
    free(dir);
    // Sends generation tasks off to other threads
    for(auto f = headers.begin(); f != headers.end(); ++f) {
        //generateOne(*f);
        threads.emplace_back(std::thread (&UMLifier::generateOne, this, *f));
    }
    // Waits for all threads to finish
    for(auto& th : threads) {
        th.join();
    }

/*     std::cout << "Printing" << std::endl;
    for(auto it = objects.begin(); it != objects.end(); ++it) {
        (*it)->print();
    } */
}

/*
Generates class data from a header file then pushes it to the object vector
*/
void UMLifier::generateOne(std::string fileName) {
    // The elements of an object
    std::string name;
    std::string parent;
    std::vector<std::string> attributes;

    std::ifstream file(path + fileName);

    /*
    This char is to denote an attributes visibility
    'n' - Not in class
    '+' - In public
    '#' - In protected
    '-' - In private
    */
    char vis = 'n';
    // This step should skip all the include/macro/etc statements
    std::string line;
    while(getline(file, line)) {
        if(line.length() > 0) {
            if(vis != 'n') {
                if(line == "};") {
                    vis = 'n';
                    break;
                }
                else if(line.find(":") != std::string::npos) {
                    if(line.at(TABSIZE+2) == 'b') vis = '+';
                    else if(line.at(TABSIZE+2) == 'o') vis = '#';
                    else if(line.at(TABSIZE+2) == 'i') vis = '-';
                    else {
                        line = line.substr(2 * TABSIZE, line.length() - 2 * TABSIZE);
                        attributes.push_back(vis + line.substr(0, line.length() -1));
                    }
                }
                else {
                    line = line.substr(2 * TABSIZE, line.length() - 2 * TABSIZE);
                    attributes.push_back(vis + line.substr(0, line.length() - 1));
                }
            }
            else {
                // Check if a class definition begins
                if(line.substr(0, 5) == (std::string) "class") {
                    vis = '+';
                    if(line.find(':') == std::string::npos) { // No Inheritance
                        name = line.substr(6, line.length() - 8);
                    }
                    else {
                        int col = line.find(':');
                        name = line.substr(6, col - 7);
                        parent = line.substr(col + 2, line.length() - col - 4);
                    }
                }
            }
        }
    }

    // Second pass through, creating the actualy class object
    if(!name.empty()) { // This is here in case of header files without class definitions
        Object *obj = new Object(fileName, name);
        if(!parent.empty()) {
            obj->setParent(parent);
        }

        // A list of primatives (mostly) to reference against. Add to this if you want to consider other objects as attributes
        std::unordered_set<std::string> prims = {"int", "char", "bool", "float", "double", "string", "std::string"};
        for(auto l = attributes.begin(); l != attributes.end(); ++l) {
            std::string line = *l;
            std::cout << line.substr(1, line.find_first_of(" ")) << std::endl;

            // Checks if the attribute is a function or not an onbject
            if(prims.find(line.substr(1, line.find_first_of(" "))) != prims.end()) {
                std::cout << "Found primative" << std::endl;
                // Check if it's a function
                if(line.find("(") != std::string::npos) {
                    obj->addFunction(line);
                }
                else {
                    obj->addValue(line);
                }
            }
            // Not a primative
            else {
                // Add to this for it to consider additional container
                std::unordered_set<std::string> containers = {"std::vector", "std::map", "std::set", "std::unordered_set"};
                // Container object
                if((line.find("[") != std::string::npos) || (containers.find(line.substr(1, line.find_first_of("<"))) != containers.end())) {
                    int open = line.find("<"); int close = line.find(">");
                    // Check if it's a function
                    if(line.substr(close + 1, line.size() - close).find("(") != std::string::npos) {
                        std::string temp = line.substr(open+1, close - open - 1);
                        // Check if container is for primatives
                        if(prims.find(temp) != prims.end()) {
                            obj->addValue(line);
                        }
                        else {
                            obj->addDependent(temp , -1);
                        }
                    }
                    else {
                        obj->addFunction(line);
                    }
                }
                else {
                    // Check if it's a function
                    if(line.find("(") != std::string::npos) {
                        obj->addFunction(line);
                    }
                    else {
                        obj->addDependent(line);
                    }
                }
            }
        }
        objects.push_back(obj);
    }
}

/*
Saves the UML file
*/
// TODO
void UMLifier::save() {

}

/*
Loads in a UML file
*/
// TODO
bool UMLifier::load() {
    return(false);
}

/*
Controller function for UMLifying files
*/
void UMLifier::umlify() {
    // Make a backup of all the header files so they're at least preserved
    std::string backup = path + "/copies";
    if(mkdir(backup.c_str(), 0755) == -1) {
        return;
    }
    std::system(("cp " + path + "/*.h " + path + "/copies").c_str());

    std::vector<std::thread> threads;
    std::vector<std::string> headers;

    // Loads a list of header files
    struct dirent *entry;
    DIR *dir = opendir(path.c_str());
    if(dir == NULL) {
        return;
    }
    while((entry = readdir(dir)) != NULL) {
        if(entry->d_type == DT_REG) {
            std::string name = entry->d_name;
            if(name.substr(name.size() - 2, name.size() - 1) == ".h") {
                headers.push_back(name);
            }
        }
    }

    // Sends generation tasks off to other threads
    for(auto f = headers.begin(); f != headers.end(); ++f) {
        threads.emplace_back(std::thread (&UMLifier::umlifyOne, this, *f));
    }
    // Waits for all threads to finish
    for(auto& th : threads) {
        th.join();
    }
}

/*
UMLifies individual files
*/
// TODO
void UMLifier::umlifyOne(std::string fileName) {
    std::ifstream file(path + fileName);

    struct cs::charset charset;
    cs::setStandardChars(charset);
}