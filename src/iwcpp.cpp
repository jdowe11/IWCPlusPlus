#include "iwcpp.hpp"

/// functions
IWCPP::IWCPP(string filepath){
    if(!filesystem::exists(filepath)){
        cout << RED << "Error: " << RESET << "File does not exist" << endl;
        exit(1);
    }
    file = filepath;
}

void IWCPP::run(){
    ifstream filestream;
    
    vector <string> parsed;
    parse(filestream, parsed);
    filestream.close();

    cout << eval(parsed);
}

int main(int argc, char* argv[]){
    if(argc < 2){
        cout << RED << "Error: " << RESET << "No input files" << endl;
        exit(0);
    }
    IWCPP code(argv[1]);
    code.run();
    return 1;
}