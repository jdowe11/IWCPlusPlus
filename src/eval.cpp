#include "hdrs/lexer.hpp"
#include "hdrs/parser.hpp"
#include "hdrs/iwcpp.hpp"

using namespace std;

Value IWCPP::evaluate(ASTNode *node) {
    if (auto num_node = dynamic_cast<NumberNode*>(node))
        return num_node->value;

    else if (auto add_node = dynamic_cast<AddNode*>(node))
        return get<int>(evaluate(add_node->left)) + get<int>(evaluate(add_node->right));

    else if (auto sub_node = dynamic_cast<SubNode*>(node))
        return get<int>(evaluate(sub_node->left)) - get<int>(evaluate(sub_node->right));

    else if (auto mult_node = dynamic_cast<MultNode*>(node))
        return get<int>(evaluate(mult_node->left)) * get<int>(evaluate(mult_node->right));

    else if (auto div_node = dynamic_cast<DivNode*>(node))
        return get<int>(evaluate(div_node->left)) / get<int>(evaluate(div_node->right));

    else if(auto assign_node = dynamic_cast<AssignNode*>(node)){
        Value expr_value = evaluate(assign_node->expr);
        auto it = env.find(assign_node->var_name); /// checks if exists already
        if(it == env.end())
            env.insert(make_pair(assign_node->var_name, expr_value));
        else
            it->second = expr_value;
        return expr_value;
    } 
    else if (auto var_node = dynamic_cast<IdentNode*>(node)) {
        auto it = env.find(var_node->name);
        if (it != env.end())
            return it->second;
        else
            throw runtime_error("Variable not found: " + var_node->name);
    } 
    else if (auto str_node = dynamic_cast<StringNode*>(node))
        return str_node->value;
    else
        throw runtime_error("Unknown ASTNode");
}

void IWCPP::execute(ASTNode *node) {
    if (auto *tell = dynamic_cast<TellNode*>(node)) {
        // Evaluate the expression in TellNode
        auto result = evaluate(tell->expr);
        
        // If the result is an integer, print it
        cout << result << endl;
        
        // If the result is a string, print it
        // (evaluate should be modified to handle strings if necessary)
    }
    else
        Value nut = evaluate(node);
}
