#include "iwcpp.hpp"

bool IWCPP::isVar(string str) const{
    return !isStr(str) && !isInt(str) && !isFlt(str) && !isOp(str) && !str.empty() && str.find('(') == string::npos;
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