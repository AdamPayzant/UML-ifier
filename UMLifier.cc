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
                            obj->addDependentLine(line);
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
    cs::charset *charset;

    charset = new cs::charset;
    cs::setStandardChars(charset);
    // Sends generation tasks off to other threads
    int i = 0;
    for(auto f = objects.begin(); f != objects.end(); ++f) {
        threads.emplace_back(std::thread (&UMLifier::umlifyOne, this, *f, charset, i));
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
void UMLifier::umlifyOne(Object *obj, cs::charset *charset, int i) {
    std::ifstream inFile(path + obj->getFileName());
    std::ofstream outFile(path + "temp" + std::to_string(i));

    std::string line;
    bool status = false;

    while(getline(inFile, line)) {
        if(status) {
            if(line.compare("};") == 0) {
                // I've already put one foot in the hole with this damn project, might as well use a goto for funsies.
                // In my defense this goto is effectively a function, but the scope of umlifyOne is preserved for it.
                // If you think gotos are inheritently evil, I strongly advise reading Dijkstra's paper against gotos, where he does actually defend some uses.
                // It's worth noting that the originally egregious uses of gotos have been phased out of modern programming, and
                // much of the debate resembles the current OO vs functional paradigm war
                goto filewrite;
            }
            else {
                // Deletes all of the actual class content
                line.replace(0, line.length() - 1, "");
            }
        }
        else {
            if(line.substr(0, 6).compare("class ") == 0) {
                status = true;
                line.replace(0,line.length() - 1, "");
            }
        }
        outFile << line << std::endl;
        loopReturn: ;
    }


    return;

    // Something about bad practice here
    // TODO: Figure out how I'm connecting UMLs
    // TODO: Figure out how I'm doing object dependencies
    if(false) {
        filewrite: ;
        // TODO: write includes for lines
        outFile << "#define " << charset->pub << " public:" << std::endl;
        outFile << "#define " << charset->priv << " private:" << std::endl;
        outFile << "#define " << charset->prot << " protected:" << std::endl;
        outFile << "#define " << charset->boxLine << std::endl;
        outFile << "#define " << charset->boxEnd << " };" << std::endl;
        outFile << "#define " << charset->semicolon << " ;" << std::endl;
        outFile << "#define " << charset->clas << " class" << std::endl;
        if(!obj->getParent().empty()) {
            outFile << "#define " << charset->classStart << ": public " << obj->getParent() << " {" << std::endl;
        }
        else {
            outFile << "#define " << charset->classStart << " {" << std::endl;
        }

        outFile << "\n" << std::endl;

        // Write out the UMLs
        outFile << charset->boxLine << std::endl;
        outFile << charset->clas << " " << obj->getClassName();
        for(int i = 0; i < (57 - obj->getClassName().length() - 2); i++) {
            outFile << " ";
        }
        outFile << charset->classStart << std::endl;
        outFile << charset->boxLine << std::endl;

        // Adds all of the functions
        for(auto iter = obj->getFunctions().begin(); iter != obj->getFunctions().end(); ++iter) {
            std::string acc = iter->substr(0, 1);
            if(acc.compare("+") == 0) {
                outFile << charset->pub;
            }
            else if(acc.compare("-") == 0) {
                outFile << charset->priv;
            }
            else {
                outFile << charset->prot;
            }

            outFile << " " << iter->substr(1, iter->length() - 2);
            for(int i = 0; i < (56 - obj->getClassName().length() - 2); i++) {
                outFile << " ";
            }
            outFile << charset->semicolon << std::endl;
        }
        
        outFile << charset->boxLine << std::endl;

        // Adds all of the values
        for(auto iter = obj->getValues().begin(); iter != obj->getValues().end(); ++iter) {
            std::string acc = iter->substr(0, 1);
            if(acc.compare("+") == 0) {
                outFile << charset->pub;
            }
            else if(acc.compare("-") == 0) {
                outFile << charset->priv;
            }
            else {
                outFile << charset->prot;
            }

            outFile << " " << iter->substr(1, iter->length() - 2);
            for(int i = 0; i < (56 - obj->getClassName().length() - 2); i++) {
                outFile << " ";
            }
            outFile << charset->semicolon << std::endl;
        }

        outFile << charset->boxEnd << std::endl;

        // TODO: Draw other boxes and draw lines

        goto loopReturn;
    }
}