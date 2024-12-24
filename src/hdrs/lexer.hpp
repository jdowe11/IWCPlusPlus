#pragma once
#include <iostream>

enum TokenType { 
    TELL,
    INT,
    DBL,
    BOOL,
    IDENT,
    STR,
    PLUS,
    MINUS,
    MULT,
    DIV,
    LPAREN,
    RPAREN,
    EQUAL,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
};

std::vector<Token> tokenize(const std::string &code);

