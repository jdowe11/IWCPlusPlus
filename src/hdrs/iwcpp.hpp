#pragma once

#include "lexer.hpp"
#include "parser.hpp"
#include "colors.hpp"
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <unordered_map>

using Value = std::variant<int, std::string>;

class IWCPP{
    public:
        /** Default Constructor
         *  @param filepath - filepath to file, empty if not given
         */
        IWCPP(std::string filepath = std::string());
        /** run - function that runs the file given
         */
        void run();

        /// evaluate functions 
        Value evaluate(ASTNode *node);

        void execute(ASTNode *node);

    private:
        string file;
        unordered_map<string, Value> env; /// the environment for storing values
};

std::ostream& operator<<(std::ostream& os, const Value& value);