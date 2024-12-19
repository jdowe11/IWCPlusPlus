#pragma once

#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <filesystem>
#include <cctype>
#include <regex>
#include <unordered_map>
#include <sstream>
#include "colors.hpp"

class IWCPP{
    /// adding in type defintions for my language, but type definition is not required
    typedef string str;
    typedef double dbl;
    typedef char ch;

    public:
        IWCPP(string filepath = string());
        void run();
    private:
        /// private functions
        /// parsing functions
        void parse(ifstream &filestream, vector<string> &parsed);
        void parseExp(string &statement);
        bool isVar(string str);
        bool isFunction(string str);

        /// evaluate functions & their helper functions
        string eval(vector<string> parsed);
        /// num evaluations
        double evalNums(stack<string> statement);
        bool isNum(std::string str);
        bool isOp(std::string str);
        double operate(string op, double num1, double num2);
        int precedence(string op);

        /// variables
        string file;
        unordered_map<string, string> env;
};