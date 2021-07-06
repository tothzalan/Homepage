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

void Generator::generate(Tokens tokens, std::string destFile) {
    std::ofstream file;
    file.open(destFile);
    file << docStart;

    std::vector<std::string> textsBuffer;
    for(int i = 0; i < tokens.tokens.size(); i++) {
        switch(tokens.tokens[i].type) {
            case TokenType::EOL:
                if(textsBuffer.size() == 2) {
                    file << "\t\t<a href=\"";
                    file << textsBuffer[1];
                    file << "\">";
                    file << textsBuffer[0];
                    file << "</a>\n";
                }
                else if(textsBuffer.size() > 0) {
                    file << "\t\t<p>";
                    file << textsBuffer[0];
                    file << "</p>\n";
                }
                textsBuffer.clear();
                file << "\t\t<br/>\n";
                break;
            case TokenType::SEP:
                if(textsBuffer.size() == 2) {
                    file << "\t\t<a href=\"";
                    file << textsBuffer[1];
                    file << "\">";
                    file << textsBuffer[0];
                    file << "</a>\n";
                }
                else if(textsBuffer.size() > 0) {
                    file << "\t\t<p>";
                    file << textsBuffer[0];
                    file << "</p>\n";
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
