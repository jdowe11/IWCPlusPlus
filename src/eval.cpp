#include "iwcpp.hpp"

/// primary evaluate functions
string IWCPP::eval(vector<string> parsed){
    /// variables
    stack<string> stack;
    bool numChecker = true;
    bool typeChecker = true;

    if(parsed.size() == 0) /// error checking
        cout << RED << "Error: " << RESET << "No data given to a variable" << endl;

    /// creates the parsed statement into a usable stack
    for(int i = parsed.size() - 1; i >= 0; i--){
        string curr = parsed.at(i);
        if(!isNum(curr) && !isOp(curr))
            numChecker = false;
        if(isFlt(curr)) /// checks if the stack has any floats
            typeChecker = false;
        stack.push(curr);
    }

    if(typeChecker && numChecker)
        return to_string(evalInt(stack));
    else if(!typeChecker && numChecker)
        return to_string(evalFloat(stack));
    else
        return evalStr(parsed);
}

int IWCPP::evalInt(stack<string> statement) const{
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
float IWCPP::evalFloat(stack<string> statement) const{
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

string IWCPP::evalStr(vector<std::string> strs) const{
    string whole = string();

    if(strs.size() == 1) /// means no concatenation
        return strs.at(0).substr(1, strs.at(0).length() - 2);

    for(size_t i = 0; i < strs.size(); i++){ /// allowing for string concatenation
        string curr = strs.at(i);
        if(!isOp(curr))
            whole += curr;
    }

    return (whole); /// removes quotes
}

template<typename T>
T IWCPP::operate(string op, T num1, T num2) const{
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

