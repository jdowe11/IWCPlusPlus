#include "hdrs/lexer.hpp"
#include <string>
#include <vector>
#include <regex>

std::vector<Token> tokenize(const std::string &code) {
    std::vector<Token> tokens;
    std::regex token_regex(R"(\s*(\d+|tell|\+|\-|\*|\/|\(|\)|[a-zA-Z_]\w*|\"[^\"]*\"|=))");
    std::smatch match;
    std::string::const_iterator search_start(code.cbegin());
    
    while (std::regex_search(search_start, code.cend(), match, token_regex)) {
        std::string token = match[1].str();
        if (token == "tell") tokens.push_back({TELL, token});
        else if (std::isdigit(token[0])) tokens.push_back({NUM, token});
        else if (token == "+") tokens.push_back({PLUS, token});
        else if (token == "-") tokens.push_back({MINUS, token});
        else if (token == "*") tokens.push_back({MULT, token});
        else if (token == "/") tokens.push_back({DIV, token});
        else if (token == "(") tokens.push_back({LPAREN, token});
        else if (token == ")") tokens.push_back({RPAREN, token});
        else if (token.front() == '"') tokens.push_back({STR, token}); // Handle string literals
        else if (std::isalpha(token[0]) || token[0] == '_') tokens.push_back({IDENT, token}); // Handle identifiers (variables or function names
        else if (token == "=") tokens.push_back({EQUAL, token});  // Handle equal sign (assignment)
        else tokens.push_back({UNKNOWN, token});

        search_start = match.suffix().first;
    }
    return tokens;
}
