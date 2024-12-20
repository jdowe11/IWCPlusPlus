#include "iwcpp.hpp"

void IWCPP::parse(ifstream &filestream){
    filestream.open(file);
    string tmp = string();

    while(!filestream.eof()){ // creates the parsed expression line by line
        string tmp;
        getline(filestream, tmp);
        if(tmp != string()) /// ignores newlines
            parseExp(tmp);
    }
}

void IWCPP::parseExp(string &exp){
    /// variables
    stringstream stream(exp);
    vector<string> mem;
    string tmp = string();

    stream >> tmp;
    if(isVar(tmp)){
        string var = tmp;
        auto it = env.find(var);

        stream >> tmp;
        if(it == env.end()){ /// checks for new declared variables
            string tmpLine;
            getline(stream, tmpLine);
            stringstream line(tmpLine);

            bigStep(tmpLine, mem);

            env.insert(make_pair(var, eval(mem)));
        }
        else if(tmp == "="){ /// sets old variables to new value
            string tmpLine;
            getline(stream, tmpLine);
            stringstream line(tmpLine);

            bigStep(tmpLine, mem);

            it = env.find(var);
            it->second = eval(mem);
        }
        else /// just returns the binded value elsewise
            exp = it->second;
    }

    else if(tmp.substr(0, tmp.find("(") + 1) == "tell(") /// printer function
        tell(exp);

    else{ /// evaluates the expression in big steps
        bigStep(exp, mem);
        exp = eval(mem);
    }
}

void IWCPP::bigStep(string exp, vector <string> &mem){ /// big step evaluation of a statement
    string tmp;
    stringstream line(exp);

    while(line >> tmp){ /// parses it for the memory vector
        if(tmp == "=") line >> tmp; 
        if(isVar(tmp))
            parseExp(tmp);
        mem.push_back(tmp);
    }
}

void IWCPP::tell(string str){
    ofstream outs;
    string innards, ending;
    size_t index;

    index = str.find(">");
    if(index != string::npos){
        ending = str.substr(index + 1);
        stringstream sstr(ending);

        sstr >> ending;
        if(ending == "terminal")
            index = string::npos;
        else
            outs.open(ending);
    }

    innards = str.substr(str.find('(') + 1, str.find(')') - str.find('(') - 1); /// removes the clutter to find just the string inside
    if(innards[0] != '\"' && index == string::npos){ /// if it is not a string, must parse it
        parseExp(innards);
        cout << innards << '\n';
    }
    else if(innards[0] != '\"' && index != string::npos){
        parseExp(innards);
        outs << innards << '\n';
    }
    else if(index != string::npos){
        outs << innards.substr(1, innards.length() - 2) << '\n'; 
    }
    else /// if it is a string to be told, then just output it without quotations
        cout << innards.substr(1, innards.length() - 2) << '\n'; 
}

bool IWCPP::isVar(string str){
    return !isInt(str) && !isFlt(str) && !isOp(str) && !str.empty() && str.find('(') == string::npos && str.find(')') == string::npos;
}

bool IWCPP::isFunction(string str){
    return true; // TODO
}