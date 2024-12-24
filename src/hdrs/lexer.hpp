#pragma once
#include <iostream>

enum TokenType { 
    TELL,
    NUM,
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