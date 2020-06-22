/*
charset.h
A header file containing structs indicating character sets
*/
#ifndef CHARSET_H
#define CHARSET_H

#include <string>
namespace cs {
    struct charset {
        bool set = false;
        std::string pub; // Indicates public
        std::string priv; // Indicates private
        std::string prot; // Indicates protected
        std::string openCom; // Open Comment
        std::string closeCom; // Close comment
        std::string connector; // Line to connect classes
    };

    /*
    Generates the standard character set that's compatible with GCC and clang
    */
    void setStandardChars(charset &chars) {
        chars.pub = "十";
        chars.priv = "ー";
        chars.prot = "＃";
        chars.openCom = "⼁";
        chars.closeCom = "︳";
        chars.connector = "ヽ";

        chars.set = true;
    };
};

#endif // CHARSET_H