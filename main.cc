/*
main.cc
Developed by Adam Payzant 07/06/2020
*/
#include <iostream>

#include "UMLifier.h"

main(int argc, char **argv) {
    if(argc < 2) {
        std::cout << "Please specify target directory" << std::endl;
        return;
    }

    UMLifier *umlifier;

    if(argc == 2) {
        std::string dir(argv[1]);
        umlifier = new UMLifier(dir);
        umlifier->generate();
        umlifier->umlify();
        std::cout<<"Done";
        return;
    }
    else if(argc == 3) {
        std::string dir(argv[2]);
        umlifier = new UMLifier(dir);

        if(argv[1] == "-g") {
            umlifier->generate();
            std::cout << "Done";
            return;
        }
        else if(argv[1] == "-u") {
            if(umlifier->load()) {
                umlifier->umlify();
                std::cout << "Done";
                return;
            }
            std::cout << "valid UML file not found";
            return;
        }
        else {
            std::cout << "Unknown Argument" << std::endl;
            return;
        }
    }
    else {
        std::cout << "Too many arguments" << std::endl;
        return;
    }
}