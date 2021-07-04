#include "token.h"

Token::Token(TokenType type, std::string value = "") {
    this->type = type;
    this->value = value;
}

Tokens::Tokens(std::vector<std::string> lines) {
    this->tokens = this->tokenizer(lines);
}

std::vector<Token> Tokens::tokenizer(std::vector<std::string> lines) {
    std::vector<Token> tokens;
    for(int i = 0; i < lines.size(); i++) {
        std::string buffer = "";
        for(char letter : lines[i]) {
            if(letter == '|') { //SEP
                tokens.push_back(Token(TokenType::TEXT, buffer));
                tokens.push_back(Token(TokenType::SEP));
                buffer = "";               
            }
            else if(letter == ';') { //CHG
                tokens.push_back(Token(TokenType::TEXT, buffer));
                tokens.push_back(Token(TokenType::CHG));
                buffer = "";
            }
            else {
                buffer.push_back(letter); 
            }
        }
        if(buffer.size() > 0) {
            tokens.push_back(Token(TokenType::TEXT, buffer));
        }
        tokens.push_back(Token(TokenType::EOL));
    }
    return tokens;
}
