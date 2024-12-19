#include "iwcpp.hpp"

void IWCPP::parse(ifstream &filestream, vector<string> &parsed){
    filestream.open(file);
    string tmp = string();

    while(!filestream.eof()){
        string tmp;
        getline(filestream, tmp);
        parseExp(tmp);
        parsed.push_back(tmp);
    }
}

void IWCPP::parseExp(string &exp){
    stringstream stream(exp);
    vector<string> mem;
    string tmp = string();

    stream >> tmp;
    if(isVar(tmp)){
        auto it = env.find(tmp);
        if(it == env.end()){
            string tmpLine, var = tmp;
            getline(stream, tmpLine);
            stringstream line(tmpLine);

            line >> tmp; /// ignores the equal sign

            while(line >> tmp){
                if(isVar(tmp))
                    parseExp(tmp);
                mem.push_back(tmp);
            }

            env.insert(make_pair(var, eval(mem)));
        }
        else
            exp = it->second;
    }

    else if(tmp.substr(0, 6) == "print("){
        string tmpLine = tmp.substr(6, tmp.length() - 7);
        parseExp(tmpLine);
        cout << tmpLine << '\n';
    }

    else{
        stringstream line(exp);
        while(line >> tmp)
            mem.push_back(tmp);
        tmp = eval(mem);
    }
}

bool IWCPP::isVar(string str){
    return !isNum(str) && !isOp(str) && str.length() != 0 && !isNum(str.substr(0, 1)) && str[str.length() - 1] != ')';
}

bool IWCPP::isFunction(string str){
    return true; // TODO
}