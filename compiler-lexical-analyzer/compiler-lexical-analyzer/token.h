#include <string>
#include <iostream>
using namespace std;

#ifndef TOKEN_H
#define TOEKN_H

enum TOKEN_TYPE
{
    TYPE,
    NUMBER, CHAR, STRING, BOOLEAN,
    ID,
    IF, ELSE, WHILE, RETURN,
    ASSIGN, COMPARE,
    LPAREN, RPAREN,
    LBRACE, RBRACE,
    LBRACKET, RBRACKET,
    COMMA, SEMICOLON,
    WSPACE,
    CLASS,
    OPER
};

const char *token_str[] = 
{   
    "TYPE",
    "NUMBER", "CHAR", "STRING", "BOOLEAN",
    "ID",
    "IF", "ELSE", "WHILE", "RETURN",
    "ASSIGN", "COMPARE",
    "LPAREN", "RPAREN",
    "LBRACE", "RBRACE",
    "LBRACKET", "RBRACKET",
    "COMMA", "SEMICOLON",
    "WSPACE",
    "CLASS",
    "OPER"
};

class Token{
public:
    TOKEN_TYPE type;
    string value;
	Token() {};
    Token(TOKEN_TYPE t, string v): type(t), value(v) {};
    friend ostream& operator<<(ostream& os, const Token& token);
};

ostream& operator<<(ostream& os, const Token& token){
    os << "<" << token_str[token.type] << ", " << token.value << ">";
	return os;
}

#endif