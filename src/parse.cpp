#include "iwcpp.hpp"

void IWCPP::parse(ifstream &filestream, vector<string> &parsed){
    filestream.open(file);
    string tmp = string();

    while(filestream >> tmp)
        parsed.push_back(tmp);
}