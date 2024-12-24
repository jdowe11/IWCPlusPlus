#include "hdrs/iwcpp.hpp"

using namespace std;

/// functions
IWCPP::IWCPP(string filepath){
    if(!filesystem::exists(filepath)){ /// checks for file existence
        cout << RED << "Error: " << RESET << "File does not exist" << endl;
        exit(0);
    }
    if(filepath.substr(filepath.length() - 4, 4) != ".iwc"){ /// ensures the file extension is valid
        cout << RED << "Error: " << RESET << "File \"" << filepath << "\" is not a valid file" << endl;
        exit(0);
    }
    file = filepath; /// sets the filepath
}

void IWCPP::run(){
    ifstream filestream;
    string code = string();

    filestream.open(file);

    while(getline(filestream, code)){ 
        // Tokenize
        auto tokens = tokenize(code);

        // Parse
        size_t index = 0;
        ASTNode* ast = parse(tokens, index);

        // Execute
        execute(ast);

        // Clean up
        delete ast;
    }
}

/// overloaded operator
ostream& operator<<(ostream& os, const Value& value) {
    // Check which type is stored in the variant and print it accordingly
    if (auto int_value = get_if<int>(&value)) {
        os << *int_value;  // If it's an int, print it
    } else if (auto str_value = get_if<string>(&value)) {
        os << *str_value;  // If it's a string, print it
    }
    else {
        os << "Unknown type";  // If it's an unknown type (shouldn't happen with proper Value types)
    }
    return os;
}