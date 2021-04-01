#include <string>

#ifndef TOKEN_H
#define TOEKN_H

enum TOKEN_TYPE{
    TYPE,
    NUMBER,
    CHAR,
    STRING
};

class Token{
    TOKEN_TYPE type;
    std::string value;
};

#endif