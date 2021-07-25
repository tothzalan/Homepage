#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#pragma once

class Template {
    public:
        std::vector<std::string> templateLines;
        int startLine;
        bool foundTemplate;
        Template(std::string fileName);
    private:
        std::vector<std::string> readInTemplate(std::string fileName);
        std::string trim(std::string input);
};
