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
    if(argc == 3)
        Generator generator(tokens, argv[2]);
    else
        Generator generator(tokens);
}
