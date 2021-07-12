#include "generator.h"

//TODO: template file support
const char* docStart =
    "<!DOCTYPE html>\n"
    "<html>\n\t<head>\n"
    "\t\t<title>Homepage</title>\n"
    "\t</head>\n\t<body>\n";

const char* docEnd =
    "\t</body>\n<style>\n"
    "\thtml, body {\n"
    "\t\twidth: 80vw;\n"
    "\t\tmargin: 0 auto;\n\t}\n"
    "\tdiv * {\n"
    "\t\tmargin: 10px;\n"
    "\t\tdisplay: inline;\n"
    "\t}\n</style>\n"
    "</html>";

Generator::Generator(Tokens tokens, std::string destFile) : tlmp("template/template.html") {
    this->fileLines = this->generate(tokens);
    this->destFile = destFile;
    this->writeToFile();
}

std::string createAnchor(std::string href, std::string text) {
    std::string tag = "\t\t\t<a href=\"";
    tag += href;
    tag += "\">";
    tag += text;
    tag += "</a>\n";
    return tag;
}

std::string createParagraph(std::string text) {
    std::string tag = "\t\t\t<p>";
    tag += text;
    tag += "</p>\n";
    return tag;
}

std::vector<std::string> Generator::generate(Tokens tokens) {
    std::vector<std::string> lines;
    std::vector<std::string> textsBuffer;
    if(!this->tlmp.foundTemplate) {
        lines.push_back(docStart);
    }
    bool isNewLine = true;
    for(int i = 0; i < tokens.tokens.size(); i++) {
        if(isNewLine) {
            lines.push_back("\t\t<div>\n");
            isNewLine = false;
        }
        switch(tokens.tokens[i].type) {
            case TokenType::EOL:
                if(textsBuffer.size() == 2) {
                    lines.push_back(createAnchor(textsBuffer[1], textsBuffer[0]));
                }
                else if(textsBuffer.size() > 0) {
                    lines.push_back(createParagraph(textsBuffer[0]));
                }
                textsBuffer.clear();
                isNewLine = true;
                lines.push_back("\t\t</div>\n");
                break;
            case TokenType::SEP:
                if(textsBuffer.size() == 2) {
                    lines.push_back(createAnchor(textsBuffer[1], textsBuffer[0]));
                }
                else if(textsBuffer.size() > 0) {
                    lines.push_back(createParagraph(textsBuffer[0]));
                }
                textsBuffer.clear();
                break;
            case TokenType::TEXT:
                textsBuffer.push_back(tokens.tokens[i].value);
                break;
        }
    }
    if(!this->tlmp.foundTemplate)
        lines.push_back(docEnd);
    else {
        this->tlmp.templateLines.erase(this->tlmp.templateLines.begin()+this->tlmp.startLine);
        this->tlmp.templateLines.insert(this->tlmp.templateLines.begin()+this->tlmp.startLine, lines.begin(), lines.end());
        return this->tlmp.templateLines;    
    }
    return lines;
}

void Generator::writeToFile() {
    std::ofstream file(this->destFile);
    if(file.is_open()) {
        for(std::string line : this->fileLines) {
            file << line;
        }
    } else
        std::cout << "Error opening the destination file" << std::endl;
}
