#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include "token.h"
#include "generator.h"

int main(int argc, char* argv[]) {
    if(argc < 2 || argc > 3) {
        std::cout << "Invalid argument(s)!" << std::endl;
        std::cout << "USEAGE: homepage source.txt out.html" << std::endl;
        return 22;
    }
    std::ifstream sourceFile(argv[1]);
    if(!sourceFile) {
        std::cout << "File not found" << std::endl;
        return 1;
    }
    std::string line;
    std::vector<std::string> sourceLines;
    while(std::getline(sourceFile, line)) {
        sourceLines.push_back(line);
    }
    Tokens tokens(sourceLines);
    /*
    for(Token token : tokens.tokens) {
        switch(token.type) {
            case TokenType::EOL:
                std::cout << "( EOL : ";
                break;
            case TokenType::SEP:
                std::cout << "( SEP: ";
                break;
            case TokenType::CHG:
                std::cout << "( CHG: ";
                break;
            case TokenType::TEXT:
                std::cout << "( TEXT: ";
        }
        std::cout << "'" << token.value << "' )" << std::endl;
    }
    */
    if(argc == 3)
        Generator generator(tokens, argv[2]);
    else
        Generator generator(tokens);
}
