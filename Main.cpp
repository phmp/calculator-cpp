#include <iostream>
#include <vector>
#include <ctype.h>
#include <string> 


std::vector < std::string > parse (std::string input){
    std::vector < std::string > inputData;
    std::string begin;
    begin.push_back(input.at(0));
    inputData.push_back(begin);

    for ( int i = 1 ; i < input.size() ; i++){
        if (std::isdigit(input.at(i)) && std::isdigit(input.at(i-1)) ){
            std::string last = inputData.back();
            std::string back = (last) + input[i];
            inputData.pop_back();
            inputData.push_back(back);
        } else if (std::isalpha(input.at(i)) && std::isalpha(input.at(i-1)) ){
            std::string last = inputData.back();
            std::string back = (last) + input[i];
            inputData.pop_back();
            inputData.push_back(back);
        } else {
            std::string s;
            s.push_back(input[i]);
            inputData.push_back(s);
        }
    }
    return inputData;
    
}

calculate(int a , std::string math_operator, int b){

    std::cout << std::endl<< a << math_operator<< b << std::endl;
   
    if (math_operator == "+"){
        return a + b;
    } else if (math_operator == "-"){
        return a - b;
    } else if (math_operator == "*"){
        return a * b;
    } else if (math_operator == "/"){
        return a / b;
    } else return 0;

}

int prio(std::string math_operator){
    if (math_operator == "+"){
        return 1;
    } else if (math_operator == "-"){
        return 1;
    } else if (math_operator == "*"){
        return 2;
    } else if (math_operator == "/"){
        return 2;
    } else return 0;
}

int findOperator(std::vector < std::string > inputData){
    int max = 1;
    int maxP = prio(inputData[1]);
    for (int i =1; i<inputData.size(); i=i+2){
        if (maxP < prio(inputData[i])){
            max = i;
            maxP = prio(inputData[i]);
        }
    }
    return max;
}

bool containBracket(std::vector < std::string > inputData){
    for (int i = 0; i<inputData.size(); i++){
        if (inputData[i] == "("){
            return true;
        }
    }
    return false;
}

int calculate(std::vector < std::string > inputData){

    std::cout << "[";
    for (int i = 0; i < inputData.size(); i++){
        std::cout << inputData[i] << " ";
    }
    std::cout << "]\n";

    if (inputData.size()==3){
        return calculate(stoi(inputData[0]),inputData[1], stoi(inputData[2]));
    } if ( containBracket(inputData)){
                    std::cout << " () \n";

        int open;
        int close;
        for (int i = 0; i<inputData.size(); i++){
            if (inputData[i] == "("){
                open = i;
            }
            if (inputData[i] == ")"){
                close = i;
                break;
            }
        }
        std::vector<std::string> newVec (inputData.begin()+open+1, inputData.begin()+close);
        int result = calculate(newVec);

        for (int i = open ; i <close ; i++){
            inputData.erase(inputData.begin()+open);
        }
        inputData[open] = std::to_string(result);
        return calculate(inputData);

    } else {
        int i = findOperator(inputData);
            // std::cout << i <<" operator\n";
        int result = calculate(stoi(inputData[i-1]),inputData[i], stoi(inputData[i+1]));
        inputData.erase(inputData.begin()+i);
        inputData.erase(inputData.begin()+i);
        inputData[i-1] = std::to_string(result);
        return calculate(inputData);
    }
}

int main(int argc, char * argv[]) {
    std::string a = "1+(5-2)*2";
    // std::cout << "podaj dzialanie" <<std::endl;
    // std::cin >> a;

    std::vector<std::string> path = parse(a);
    for (int i = 0; i < path.size(); i++){
        std::cout << path[i] << " ";
    }
    std::cout << " = \n\n" << calculate(path);
    return 0;
}