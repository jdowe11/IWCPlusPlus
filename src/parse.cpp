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
        if(it == env.end() && tmp != "<" && tmp != "<<"){ /// checks for new declared variables
            string tmpLine;
            getline(stream, tmpLine);

            addToEnv(var, tmpLine, mem);
        }
        else if(tmp == "="){ /// sets old variables to new value
            string tmpLine;
            getline(stream, tmpLine);

            addToEnv(var, tmpLine, mem);
        }
        else if(tmp == "<"){ /// allows for input from terminal
            stream >> tmp;
            if(tmp == "con")
                cin >> tmp;
            else{
                ifstream ins(tmp);
                if(ins.fail()){
                    cout << RED << "Error: " << RESET << "Input file: " << tmp << " does not exist" << endl;
                    exit(0);
                }
                ins >> tmp;  
            }
            env.insert(make_pair(var,tmp));
        }
        else if(tmp == "<<"){ /// allows for input from terminal
            stream >> tmp;
            if(tmp == "con")
                getline(cin, tmp);
            else{
                ifstream ins(tmp);
                if(ins.fail()){
                    cout << RED << "Error: " << RESET << "Input file: " << tmp << " does not exist" << endl;
                    exit(0);
                }
                getline(ins, tmp);  
            }
            env.insert(make_pair(var,tmp));
        }
        else if(isOp(tmp)){ /// checks for string operations
            string tmpLine;
            getline(stream, tmpLine);

            mem.push_back(it->second); /// adds an old string into the mix
            mem.push_back(tmp); /// adds the operation
            bigStep(tmpLine, mem);

            exp = eval(mem);
        }
        else{ /// just returns the binded value elsewise
            exp = it->second;
        }
    }

    else if(tmp.substr(0, tmp.find("(") + 1) == "tell(") /// printer function
        tell(exp);

    else{ /// evaluates the expression in big steps
        bigStep(exp, mem);
        for(size_t i = 0; i < mem.size() - 1; i++){
            string str = mem.at(i);
            if(str.find('"') != string::npos){ /// declutters trings
                str = declutter(str);
                mem.at(i) = str;
            }
        }
        exp = eval(mem);
    }
}

void IWCPP::addToEnv(string var, string exp, vector<string> mem){
    auto it = env.find(var); /// checks if exists already

    if(exp.find('"') != string::npos){
        size_t first = exp.find('"');
        size_t second = exp.find('"', first + 1);
        exp = exp.substr(first + 1, second - first - 1); /// allows for string concatenation
        if(it == env.end())
            env.insert(make_pair(var, exp));
        else
            it->second = exp;
    }
    else{
        bigStep(exp, mem);
        if(it == env.end())
            env.insert(make_pair(var, eval(mem)));
        else
            it->second = exp;
    }
}

void IWCPP::bigStep(string exp, vector <string> &mem){ /// big step evaluation of a statement
    string tmp;
    stringstream line(exp);

    while(line >> tmp){ /// parses it for the memory vector
        if(tmp == "=") line >> tmp; 
        if(inEnv(tmp))
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
        if(ending == "con") /// can add terminal, but is not required
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