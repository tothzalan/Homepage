#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include "token.h"
#include "template.h"
#pragma once

class Generator {
    public:
        Generator(Tokens tokens, std::string destFile = "homepage.html");
    private:
        std::vector<std::string> generate(Tokens tokens);
        void writeToFile();
        std::vector<std::string> fileLines;
        std::string destFile;
        Template tlmp;
};
