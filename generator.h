#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include "token.h"
#pragma once

class Generator {
    public:
        Generator(Tokens tokens, std::string destFile = "homepage.html");
    private:
        void generate(Tokens tokens, std::string destFile);
};
