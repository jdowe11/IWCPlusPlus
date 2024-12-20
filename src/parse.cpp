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

            bigStep(tmpLine, mem);

            env.insert(make_pair(var, eval(mem)));
        }
        else if(tmp == "="){ /// sets old variables to new value
            string tmpLine;
            getline(stream, tmpLine);

            bigStep(tmpLine, mem);

            it = env.find(var);
            it->second = eval(mem);
        }
        else{ /// just returns the binded value elsewise
            if(isNum(it->second)) 
                exp = it->second;
            else /// must be returns as a string for identification
                exp = '\"' + it->second + '\"';
        }
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
    if(index != string::npos){ /// checks if output files are given, terminal is default
        ending = str.substr(index + 1);
        stringstream sstr(ending);

        sstr >> ending;
        if(ending == "terminal") /// can add terminal, but is not required
            index = string::npos;
        else
            outs.open(ending);
    }

    innards = str.substr(str.find('(') + 1, str.find(')') - str.find('(') - 1); /// removes the clutter to find just the string inside
    if(index == string::npos){ /// will output to terminal if not provided an output
        parseExp(innards);
        cout << innards << '\n';
    }
    else{ /// otherwise will output to the given output
        parseExp(innards);
        outs << innards << '\n';
        outs.close();
    }
}