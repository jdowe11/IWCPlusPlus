#include "hdrs/lexer.hpp"
#include "hdrs/parser.hpp"
#include <vector>

using namespace std;

ASTNode* parsePrimary(const vector<Token> &tokens, size_t &index){
    if (tokens[index].type == INT) {
        int value = stoi(tokens[index].value);
        index++;
        return new IntNode(value);
    } 
    else if (tokens[index].type == DBL) {
        double value = stod(tokens[index].value);
        index++;
        return new DblNode(value);
    }
    else if(tokens[index].type == BOOL){
        if(tokens[index].value == "true")
            return new BoolNode(true);
        if(tokens[index].value == "false")
            return new BoolNode(false);
    }
    else if (tokens[index].type == IDENT) {
        string var_name = tokens[index].value;
        index++;
        return new IdentNode(var_name); // Return a VariableNode for variable reference
    }
    else if (tokens[index].type == STR) {
        string str_value = tokens[index].value.substr(1, tokens[index].value.size() - 2); // Remove quotes
        index++;
        return new StringNode(str_value); // Return a StringNode for string literal
    }
    else if (tokens[index].type == LPAREN) {
        index++;
        ASTNode* expr = parseExpression(tokens, index);
        if (tokens[index].type == RPAREN) {
            index++;
            return expr;
        }
    }
    return nullptr;
}

ASTNode* parseAssignment(const std::vector<Token>& tokens, size_t& index) {
    if (tokens[index].type == IDENT) {
        std::string var_name = tokens[index].value;
        index++; // Skip variable name
        
        if (tokens[index].type == EQUAL) {
            index++; // Skip '='
            ASTNode* expr = parseExpression(tokens, index); // Parse the right-hand expression
            return new AssignNode(var_name, expr); // Return an AssignNode
        }
    }
    return nullptr;
}

ASTNode* parseTerm(const vector<Token> &tokens, size_t &index) {
    ASTNode* left = parsePrimary(tokens, index); // Parse the first operand

    while (index < tokens.size() &&
           (tokens[index].type == MULT || tokens[index].type == DIV)) {
        TokenType op = tokens[index].type;
        index++; // Skip the operator
        ASTNode* right = parsePrimary(tokens, index); // Parse the next operand

        if (op == MULT) {
            left = new MultNode(left, right);
        } else if (op == DIV) {
            left = new DivNode(left, right);
        }
    }

    return left;
}

ASTNode* parseExpression(const vector<Token> &tokens, size_t &index) {
    ASTNode* left = parseTerm(tokens, index); // Parse the first term (handles * and /)

    while (index < tokens.size() &&
           (tokens[index].type == PLUS || tokens[index].type == MINUS)) {
        TokenType op = tokens[index].type;
        index++; // Skip the operator
        ASTNode* right = parseTerm(tokens, index); // Parse the next term

        if (op == PLUS) {
            left = new AddNode(left, right);
        } else if (op == MINUS) {
            left = new SubNode(left, right);
        }
    }

    return left;
}

ASTNode* parse(const vector<Token> &tokens, size_t &index) {
    if (index < tokens.size()) {
        // Handle TELL statements
        if (tokens[index].type == TELL) {
            index++; // Skip 'tell'
            if (tokens[index].type == LPAREN) {
                index++; // Skip '('
                ASTNode* expr = parseExpression(tokens, index); // Parse the inner expression
                if (tokens[index].type == RPAREN) {
                    index++; // Skip ')'
                    return new TellNode(expr);
                } else {
                    throw runtime_error("Mismatched parentheses in TELL");
                }
            } else {
                throw runtime_error("Expected '(' after TELL");
            }
        }

        // Handle assignments
        ASTNode* assignment = parseAssignment(tokens, index);
        if (assignment) {
            return assignment;
        }

        // Default to parsing expressions
        return parseExpression(tokens, index);
    }

    throw runtime_error("Unexpected end of input");
}
