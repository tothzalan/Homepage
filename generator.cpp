#include "generator.h"

Generator::Generator(Tokens tokens, std::string destFile) {
    this->generate(tokens, destFile);
}


void Generator::generate(Tokens tokens, std::string destFile) {
    std::ofstream file;
    file.open(destFile);
    for(Token token : tokens.tokens) {
        switch(token.type) {
            case TokenType::EOL:
                file << "\n";
                break;
            case TokenType::SEP:
                file << " | ";
                break;
            case TokenType::CHG:
                file << " ; ";
                break;
            case TokenType::TEXT:
                file << token.value;
        }
    }
    file.close();
}
