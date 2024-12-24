#include "hdrs/iwcpp.hpp"

int main(int argc, char* argv[]){ /// main program, will run the code
    if(argc < 2){
        cout << RED << "Error: " << RESET << "No input files" << endl;
        exit(0);
    }
    IWCPP code(argv[1]);
    code.run();
    return 1;
}