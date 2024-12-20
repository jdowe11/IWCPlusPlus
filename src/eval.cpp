#include "iwcpp.hpp"

/// primary evaluate functions
string IWCPP::eval(vector<string> parsed){
    /// creates the parsed statement into a usable stack
    stack<string> stack;
    bool typeChecker = true;

    for(int i = parsed.size() - 1; i >= 0; i--){
        if(isFlt(parsed.at(i)))
            typeChecker = false;
        stack.push(parsed.at(i));
    }

    if(typeChecker)
        return to_string(evalInt(stack));
    else if(!typeChecker)
        return to_string(evalFloat(stack));
    else
        return "GUH";
}

int IWCPP::evalInt(stack<string> statement){
    /// variables for evaluation
    stack <string> ops;
    stack <int> nums;

    while(!statement.empty()){
        string token = statement.top();
        statement.pop();

        if(isNum(token)) /// checks if a num exists
            nums.push(stoi(token));
        else{ /// must be an op, then will evaluate
            while (!ops.empty() && precedence(ops.top()) >= precedence(token)) {
                float b = nums.top(); nums.pop();
                float a = nums.top(); nums.pop();
                string op = ops.top(); ops.pop();
                nums.push(operate(op, a, b)); // Apply the operator
            }
            ops.push(token);
        }
    }

    while(!ops.empty()){
        float b = nums.top(); nums.pop();
        float a = nums.top(); nums.pop();
        string op = ops.top(); ops.pop();
        nums.push(operate(op, a, b)); // Apply the operator
    }

    return nums.top();
}

/// type specific evaluate functions
float IWCPP::evalFloat(stack<string> statement){
    /// variables for evaluation
    stack <string> ops;
    stack <float> nums;

    while(!statement.empty()){
        string token = statement.top();
        statement.pop();

        if(isNum(token)) /// checks if a num exists
            nums.push(stod(token));
        else{ /// must be an op, then will evaluate
            while (!ops.empty() && precedence(ops.top()) >= precedence(token)) {
                float b = nums.top(); nums.pop();
                float a = nums.top(); nums.pop();
                string op = ops.top(); ops.pop();
                nums.push(operate(op, a, b)); // Apply the operator
            }
            ops.push(token);
        }
    }

    while(!ops.empty()){
        float b = nums.top(); nums.pop();
        float a = nums.top(); nums.pop();
        string op = ops.top(); ops.pop();
        nums.push(operate(op, a, b)); // Apply the operator
    }

    return nums.top();
}

/// HELPER FUNCTIONS
bool IWCPP::isInt(std::string str){
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

bool IWCPP::isFlt(std::string str){
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

bool IWCPP::isNum(std::string str){
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

bool IWCPP::isOp(std::string str){
    return str == "+" || str == "-" || str == "*" || str == "/";
}

int IWCPP::precedence(string op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0; // Invalid operator
}

template<typename T>
T IWCPP::operate(string op, T num1, T num2){
    if(op == "+")
        return num1 + num2;
    else if(op == "-")
        return num1 - num2;
    else if(op == "*")
        return num1 * num2;
    else if(op == "/"){
        if(num2 == 0){
            cout << RED << "Error: " << RESET << "Division by Zero" << endl;
            exit(0);
        }
        else
            return num1 / num2;
    }
    else{
        cout << RED << "Error: " << RESET << "Invalid Operation" << endl;
        exit(0);
    }

}

