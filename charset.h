/*
charset.h
A header file containing structs indicating character sets
*/
#ifndef CHARSET_H
#define CHARSET_H

#include <string>
namespace cs {
    struct charset {
        std::string pub; // Indicates public
        std::string priv; // Indicates private
        std::string prot; // Indicates protected
        std::string connector; // Line to connect classes
        std::string boxLine; // Line to build class box with
        std::string boxEnd; // Line to end class
        std::string semicolon; // Character to make box exterior
        std::string classStart; // Line to contain actual inheritance statement and {
        std::string clas;
    };

    /*
    Generates the standard character set that's compatible with GCC and clang
    */
    void setStandardChars(charset *chars) {
        chars->pub = "X十";
        chars->priv = "Xー";
        chars->prot = "X＃";
        chars->connector = "ヽ";
        chars->boxLine = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
        chars->boxEnd = "HXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
        chars->semicolon = "X";
        chars->classStart = "Z";
        chars->clas = "Y";
    };
};

#endif // CHARSET_H