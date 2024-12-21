#include "iwcpp.hpp"

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
    parse(filestream); /// adds filestream to parser
    filestream.close();
}