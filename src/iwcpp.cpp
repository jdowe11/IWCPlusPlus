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

/// variants require overloaded operators

ostream& operator<<(ostream& os, const Value& value) {
    // Check which type is stored in the variant and print it accordingly
    if (auto int_value = get_if<int>(&value)) {
        os << *int_value;  // If it's an int, print it
    } else if (auto str_value = get_if<string>(&value)) {
        os << *str_value;  // If it's a string, print it
    }
    else if (auto dbl_value = get_if<double>(&value)) {
        os << *dbl_value;  // If it's a string, print it
    }
    else {
        os << "Unknown type";  // If it's an unknown type (shouldn't happen with proper Value types)
    }
    return os;
}

Value operator+(const Value& left, const Value& right) {
    // Check if both left and right are int
    if (auto left_val = get_if<int>(&left)) {
        if (auto right_val = get_if<int>(&right)) {
            return *left_val + *right_val; // Use dereferenced pointers
        }
    }
    
    // Check if both left and right are double
    if (auto left_val = get_if<double>(&left)) {
        if (auto right_val = get_if<double>(&right)) {
            return *left_val + *right_val; // Use dereferenced pointers
        }
    }

    // Handle mixed types: int + double or double + int
    if (auto left_int = get_if<int>(&left)) {
        if (auto right_double = get_if<double>(&right)) {
            return static_cast<double>(*left_int) + *right_double;
        }
    }
    if (auto left_double = get_if<double>(&left)) {
        if (auto right_int = get_if<int>(&right)) {
            return *left_double + static_cast<double>(*right_int);
        }
    }

    // If we reach here, types are incompatible
    throw std::runtime_error("Invalid types for operator+");
}

Value operator-(const Value& left, const Value& right) {
    // Check if both left and right are int
    if (auto left_val = get_if<int>(&left)) {
        if (auto right_val = get_if<int>(&right)) {
            return *left_val - *right_val; // Use dereferenced pointers
        }
    }
    
    // Check if both left and right are double
    if (auto left_val = get_if<double>(&left)) {
        if (auto right_val = get_if<double>(&right)) {
            return *left_val - *right_val; // Use dereferenced pointers
        }
    }

    // Handle mixed types: int - double or double - int
    if (auto left_int = get_if<int>(&left)) {
        if (auto right_double = get_if<double>(&right)) {
            return static_cast<double>(*left_int) - *right_double;
        }
    }
    if (auto left_double = get_if<double>(&left)) {
        if (auto right_int = get_if<int>(&right)) {
            return *left_double - static_cast<double>(*right_int);
        }
    }

    // If we reach here, types are incompatible
    throw std::runtime_error("Invalid types for operator-");
}

Value operator*(const Value& left, const Value& right) {
    // Check if both left and right are int
    if (auto left_val = get_if<int>(&left)) {
        if (auto right_val = get_if<int>(&right)) {
            return *left_val * *right_val; // Use dereferenced pointers
        }
    }
    
    // Check if both left and right are double
    if (auto left_val = get_if<double>(&left)) {
        if (auto right_val = get_if<double>(&right)) {
            return *left_val * *right_val; // Use dereferenced pointers
        }
    }

    // Handle mixed types: int * double or double * int
    if (auto left_int = get_if<int>(&left)) {
        if (auto right_double = get_if<double>(&right)) {
            return static_cast<double>(*left_int) * *right_double;
        }
    }
    if (auto left_double = get_if<double>(&left)) {
        if (auto right_int = get_if<int>(&right)) {
            return *left_double * static_cast<double>(*right_int);
        }
    }

    // If we reach here, types are incompatible
    throw std::runtime_error("Invalid types for operator*");
}

Value operator/(const Value& left, const Value& right) {
    // Check if both left and right are int
    if (auto left_val = get_if<int>(&left)) {
        if (auto right_val = get_if<int>(&right)) {
            return *left_val / *right_val; // Use dereferenced pointers
        }
    }
    
    // Check if both left and right are double
    if (auto left_val = get_if<double>(&left)) {
        if (auto right_val = get_if<double>(&right)) {
            return *left_val / *right_val; // Use dereferenced pointers
        }
    }

    // Handle mixed types: int / double or double / int
    if (auto left_int = get_if<int>(&left)) {
        if (auto right_double = get_if<double>(&right)) {
            return static_cast<double>(*left_int) / *right_double;
        }
    }
    if (auto left_double = get_if<double>(&left)) {
        if (auto right_int = get_if<int>(&right)) {
            return *left_double / static_cast<double>(*right_int);
        }
    }

    // If we reach here, types are incompatible
    throw std::runtime_error("Invalid types for operator/");
}