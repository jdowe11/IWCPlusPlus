#include "iwcpp.hpp"

/// primary evaluate functions
string IWCPP::eval(vector<string> parsed){
    /// creates the parsed statement into a usable stack
    stack<string> stack;
    for(int i = parsed.size() - 1; i >= 0; i--)
        stack.push(parsed.at(i));

    return to_string(evalNums(stack));
}


/// type specific evaluate functions
double IWCPP::evalNums(stack<string> statement){
    /// variables for evaluation
    stack <string> ops;
    stack <double> nums;

    while(!statement.empty()){
        string token = statement.top();
        statement.pop();

        if(isNum(token)) /// checks if a num
            nums.push(stod(token));
        else{ /// must be an op, then will evaluate
            while (!ops.empty() && precedence(ops.top()) >= precedence(token)) {
                double b = nums.top(); nums.pop();
                double a = nums.top(); nums.pop();
                string op = ops.top(); ops.pop();
                nums.push(operate(op, a, b)); // Apply the operator
            }
            ops.push(token);
        }
    }

    while(!ops.empty()){
        double b = nums.top(); nums.pop();
        double a = nums.top(); nums.pop();
        string op = ops.top(); ops.pop();
        nums.push(operate(op, a, b)); // Apply the operator
    }

    return nums.top();
}

/// HELPER FUNCTIONS
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

double IWCPP::operate(string op, double num1, double num2){
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

