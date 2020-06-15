/*
charset.h
A header file containing structs indicating character sets
*/

#include <string>

void setStandardChars(charset &);

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
Generates the standard character set that's compatible with GCC and clangs
*/
void setStandardChars(charset &chars) {
    chars.pub = "十";
    chars.priv = "ー";
    chars.prot = "＃";
    chars.openCom = "⼁";
    chars.closeCom = "︳";
    chars.connector = "ヽ";

    chars.set = true;
}