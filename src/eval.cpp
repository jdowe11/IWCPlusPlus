#include "iwcpp.hpp"

/// primary evaluate functions
string IWCPP::eval(vector<string> parsed){
    /// variables
    stack<string> stack;
    bool typeChecker = true;

    if(parsed.size() == 0) /// error checking
        cout << RED << "Error: " << RESET << "No data given to a variable" << endl;

    if(isStr(parsed.at(0))) /// checks if a string, returns if so
        return evalStr(parsed);

    /// creates the parsed statement into a usable stack
    for(int i = parsed.size() - 1; i >= 0; i--){
        if(isFlt(parsed.at(i))) /// checks if the stack has any floats
            typeChecker = false;
        stack.push(parsed.at(i));
    }

    if(typeChecker)
        return to_string(evalInt(stack));
    else
        return to_string(evalFloat(stack));
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
    string whole;

    for(size_t i = 0; i < strs.size(); i++){ /// allowing for string concatenation
        if(strs[i][0] == '"' && strs[i][strs[i].length() - 1] == '"'){
            whole += strs[i].substr(1, strs[i].length() - 2); /// normal string, remove quotes
        }
        else if(strs[i] == "+" && i + 1 < strs.size()){ /// operation for string concatenation with no autoformating
            i++; // Move to the next string
            whole += strs[i].substr(1, strs[i].length() - 2);
        }
        else if(strs[i] == "+." && i + 1 < strs.size()){ /// dot after concat indicates a space
            i++;
            whole += " " + strs[i].substr(1, strs[i].length() - 2);
        }
        else if(strs[i] == "++" && i + 1 < strs.size()){  /// double plus indicates newline
            i++;
            whole += "\n" + strs[i].substr(1, strs[i].length() - 2);
        }
        else if(strs[i] == "+-" && i + 1 < strs.size()){ /// dash indicates tab
            i++;
            whole += "\t" + strs[i].substr(1, strs[i].length() - 2);
        }
        else{ /// error checking!
            cout << RED << "Error: " << RESET << "Invalid string operation or malformed input: " << strs[i] << endl; 
            exit(0);
        }
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

