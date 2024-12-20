/**
 *     @file: iwcpp.hpp
 *     @date: 12/18/24
 *   @author: Jayden Dowell
 *    @brief: This file is the header file for the IWCPP language, which is an interpreted
 *            language using C++ and the files end with a .iwc extension
 */
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
    public:
        /** Default Constructor
         *  @param filepath - filepath to file, empty if not given
         */
        IWCPP(string filepath = string());
        /** run - function that runs the file given
         */
        void run();
    private:
        /// private functions

        /// parsing functions

        /** parse - parses the file into individual lines
         *  @param filestream - the file that is being read in from
         */
        void parse(ifstream &filestream);
        /** parseExp - parses and evaluates a given expression
         *  @param statement - the statement to be parsed
         */
        void parseExp(string &statement);
        /** bigStep - helper function for the parser, separates all objects and desugars all values
         *  @param exp - the expression that is parsed
         *  @param mem - the memory that the expression is parsed to
         */
        void bigStep(string exp, vector <string> &mem);
        /** tell - function that handles printing to console 
         *  @param str - string to be printed
         */
        void tell(string str);
        /** isVar - checks if a string is a valid variable
         *  @param str - the string to be checked
         *  @return - boolean depending on string
         */
        bool isVar(string str) const;
        /** isFunction - checks if a string is a valid function
         *  @param str - the string to be checked
         *  @return - boolean depending on string
         */
        bool isFunction(string str) const;

        /// evaluate functions & helper functions

        /** eval - evaluates a parsed expression
         *  @param parsed - the parsed expression
         *  @return - the value of the expression
         */
        string eval(vector<string> parsed);
        /** evalInt - evaluates a set of integers in an expression
         *  @param statement - the stack of numbers and operations
         *  @return - the value
         */
        int evalInt(stack<string> statement) const;
        /** isInt - checks if a string is an integer
         *  @param str - the string to be checked
         *  @return - boolean depending on string
         */
        bool isInt(std::string str) const;
        /** evalFloat - evaluates a set of floating points numbers in an expression
         *  @param statement - the stack of numbers and operations
         *  @return - the value
         */
        float evalFloat(stack<string> statement) const;
        /** isFlt - checks if a string is a floating point number
         *  @param str - the string to be checked
         *  @return - boolean depending on string
         */
        bool isFlt(std::string str) const;
        /** evalFloat - evaluates a set of strings in an expression and allow concatenation
         *  @param statement - the vector of strings
         *  @return - the value
         */
        string evalStr(vector<std::string> strs) const;
        /** isStr - checks if a string passed is a string
         *  @param str - the string to be checked
         *  @return - boolean depending on string
         */
        bool isStr(std::string str) const;
        /** isNum - checks if a string is a a number
         *  @param str - the string to be checked
         *  @return - boolean depending on string
         */
        bool isNum(std::string str) const;
        /** isOp - checks if a string is an operator
         *  @param str - the string to be checked
         *  @return - boolean depending on string
         */
        bool isOp(std::string str) const;
        /** operate - performs a given operation on two numbers
         *  @param op - the operation to be done
         *  @param num1 - the first number
         *  @param num2 - the second number
         */
        template<typename T>
        T operate(string op, T num1, T num2) const;
        /** precedence - function to check operator precedence in an equation (CURRENTLY FOLLOW MDAS, no PE)
         *  @param op - the operator
         *  @return - precedence of operator, higher or lowering depending
         */
        int precedence(string op) const;

        /// variables
        string file;
        unordered_map<string, string> env; /// the environment for storing values
};