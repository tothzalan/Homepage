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

Generator::Generator(Tokens tokens, std::string destFile) {
    this->generate(tokens, destFile);
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

void Generator::generate(Tokens tokens, std::string destFile) {
    std::ofstream file;
    file.open(destFile);
    file << docStart;

    std::vector<std::string> textsBuffer;
    bool isNewLine = true;
    for(int i = 0; i < tokens.tokens.size(); i++) {
        if(isNewLine) {
            file << "\t\t<div>\n";
            isNewLine = false;
        }
        switch(tokens.tokens[i].type) {
            case TokenType::EOL:
                if(textsBuffer.size() == 2) {
                    file << createAnchor(textsBuffer[1], textsBuffer[0]);
                }
                else if(textsBuffer.size() > 0) {
                    file << createParagraph(textsBuffer[0]);
                }
                textsBuffer.clear();
                isNewLine = true;
                file << "\t\t</div>\n";
                break;
            case TokenType::SEP:
                if(textsBuffer.size() == 2) {
                    file << createAnchor(textsBuffer[1], textsBuffer[0]);
                }
                else if(textsBuffer.size() > 0) {
                    file << createParagraph(textsBuffer[0]);
                }
                textsBuffer.clear();
                break;
            case TokenType::TEXT:
                textsBuffer.push_back(tokens.tokens[i].value);
                break;
        }
    }
    file << docEnd;
    file.close();
}
