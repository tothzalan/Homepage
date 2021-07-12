#include "template.h"

Template::Template(std::string fileName) {
    this->templateLines = this->readInTemplate(fileName);
}

std::string trimm(std::string input) {
    auto start = input.begin();
    while(start != input.end() && std::isspace(*start)) {
        start++;
    }
    auto end = input.end();
    do {
        end--;
    } while(std::distance(start,end) > 0 && std::isspace(*end));
    return std::string(start, end+1);
}

std::vector<std::string> Template::readInTemplate(std::string fileName) {
    std::ifstream templateFile(fileName);
    std::vector<std::string> lines;
    if(!templateFile) {
        std::cout << "Template file not found" << std::endl;
        std::cout << "Using a default one" << std::endl;
        this->foundTemplate = false;
        return lines;
    }
    std::string line;
    int index = 0;
    bool foundStart = false;
    while(std::getline(templateFile, line)) {
        lines.push_back(line + "\n");
        if(trimm(line) == "{::}" && !foundStart) {
            this->startLine = index;
            foundStart = true;
        }
        index++;
    }
    if(foundStart)
        this->foundTemplate = true;
    else {
        std::cout << "Content template start '{::}' was not found" << std::endl;
        this->foundTemplate = false;
    }
    return lines;
}
