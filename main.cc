/*
main.cc
Developed by Adam Payzant 07/06/2020
*/
#include <iostream>

#include "UMLifier.h"

// I know using namespaces has become somewhat frowned upon, but in this specific circumstance there should be no namespace collisions
// I would also like to say this is the only file it's used
using namespace std;

int main(int argc, char **argv) {
    if(argc < 2) {
        cout << "Please specify target directory" << endl;
        return -1;
    }

    UMLifier *umlifier;

    if(argc == 2) {
        std::string dir(argv[1]);
        umlifier = new UMLifier(dir);
        umlifier->generate();
        umlifier->umlify();
        cout << "Done" << endl;
        delete(umlifier);
        return 0;
    }
    else if(argc == 3) {
        string dir(argv[2]);
        umlifier = new UMLifier(dir);

        if(argv[1] == "-g") {
            umlifier->generate();
            umlifier->save();
            cout << "Done" << endl;
            delete(umlifier);
            return 0;
        }
        else if(argv[1] == "-u") {
            if(umlifier->load()) {
                umlifier->umlify();
                cout << "Done" << endl;
                delete(umlifier);
                return 0;
            }
            cout << "valid UML file not found" << endl;
            return -1;
        }
        else {
            cout << "Unknown Argument" << endl;
            return -1;
        }
    }
    else {
        cout << "Too many arguments" << endl;
        return -1;
    }
}