#pragma once
#include <vector>
#include "lexer.hpp"
#include "ast.hpp"

ASTNode* parsePrimary(const std::vector<Token> &tokens, size_t &index);

ASTNode* parseTerm(const std::vector<Token> &tokens, size_t &index);

ASTNode* parseExpression(const std::vector<Token> &tokens, size_t &index);

ASTNode* parse(const std::vector<Token> &tokens, size_t &index);

