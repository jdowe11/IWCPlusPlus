#pragma once
#include <string>

struct ASTNode {
    virtual ~ASTNode() = default;
};

struct IntNode : ASTNode {
    int value;
    IntNode(int value) : value(value) {}
};

struct DblNode : ASTNode {
    double value;
    DblNode(double value) : value(value) {}
};

struct AddNode : ASTNode {
    ASTNode *left;
    ASTNode *right;
    AddNode(ASTNode *left, ASTNode *right) : left(left), right(right) {}
};

struct SubNode : ASTNode {
    ASTNode *left;
    ASTNode *right;
    SubNode(ASTNode *left, ASTNode *right) : left(left), right(right) {}
};

struct MultNode : ASTNode {
    ASTNode *left;
    ASTNode *right;
    MultNode(ASTNode *left, ASTNode *right) : left(left), right(right) {}
};

struct DivNode : ASTNode {
    ASTNode *left;
    ASTNode *right;
    DivNode(ASTNode *left, ASTNode *right) : left(left), right(right) {}
};

// Add a new ASTNode for string literals
struct StringNode : ASTNode {
    std::string value;
    StringNode(const std::string& value) : value(value) {}
};

struct IdentNode : ASTNode {
    std::string name;
    IdentNode(const std::string& name) : name(name) {}
};

struct AssignNode : ASTNode {
    std::string var_name;
    ASTNode* expr;
    AssignNode(const std::string& var_name, ASTNode* expr)
        : var_name(var_name), expr(expr) {}
};

struct TellNode : ASTNode {
    ASTNode *expr;
    TellNode(ASTNode *expr) : expr(expr) {}
};