#include "iwcpp.hpp"

bool IWCPP::isVar(string str) const{
    return !isStr(str) && !isInt(str) && !isFlt(str) && !isOp(str) && !str.empty() && str.find('(') == string::npos;
}

bool IWCPP::inEnv(string str) const{
    auto it = env.find(str);
    return it != env.end();
}

bool IWCPP::isFunction(string str) const{
    return true; // TODO
}

bool IWCPP::isInt(std::string str) const{
    try{
        stoi(str);
        if(str.find(".") == string::npos)
            return true;
        else
            return false;
    } catch (const std::invalid_argument& e) {
        // If the string is not a valid number, catch the exception
        return false;
    } catch (const std::out_of_range& e) {
        // If the number is too large or too small, catch the exception
        return false;
    }
}

bool IWCPP::isFlt(std::string str) const{
    try{
        stod(str);
        if(str.find('.') != string::npos)
            return true;
        else
            return false;
    } catch (const std::invalid_argument& e) {
        // If the string is not a valid number, catch the exception
        return false;
    } catch (const std::out_of_range& e) {
        // If the number is too large or too small, catch the exception
        return false;
    }
}

bool IWCPP::isNum(std::string str) const{
    try{
        stod(str);
        return true;
    } catch (const std::invalid_argument& e) {
        // If the string is not a valid number, catch the exception
        return false;
    } catch (const std::out_of_range& e) {
        // If the number is too large or too small, catch the exception
        return false;
    }
}

bool IWCPP::isStr(std::string str) const{
    return str.find('"') != string::npos;
}

bool IWCPP::isOp(std::string str) const{
    return str == "+" || str == "-" || str == "*" || str == "/" || str == "+." || str == "+-" || str == "++";
}

int IWCPP::precedence(string op) const{

    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0; // Invalid operator
}

string IWCPP::declutter(string str){
    size_t first = str.find('"'); /// finds the first occurance
    size_t second = str.find('"', first + 1); /// finds the second occurance
    if(first != string::npos && first != string::npos) /// two "
        return str.substr(first + 1, second - first - 1);
    else if(first != string::npos && first == 0) /// one " at the beginning
        return str.substr(1);
    else if(first != string::npos && first != 0) //// one " at the end
        return str.substr(0, str.length() - 1);
    else{
        cout << RED << "Error: " << RESET << "decluttering mistake on -> " << str << endl;
        exit(0);
    }
}