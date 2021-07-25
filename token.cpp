#include "token.h"

Token::Token(TokenType type, std::string value = "") {
    this->type = type;
    this->value = value;
}

Tokens::Tokens(std::vector<std::string> lines) {
    this->tokens = this->tokenizer(lines);
}

std::string Tokens::trim(std::string input) {
    auto start = input.begin();
    while (start != input.end() && std::isspace(*start)) {
        start++;
    }

    auto end = input.end();
    do {
        end--;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

std::vector<Token> Tokens::tokenizer(std::vector<std::string> lines) {
    std::vector<Token> tokens;
    for(int i = 0; i < lines.size(); i++) {
        std::string buffer = "";
        for(char letter : lines[i]) {
            if(letter == '|') { //SEP
                tokens.push_back(Token(TokenType::TEXT, this->trim(buffer)));
                tokens.push_back(Token(TokenType::SEP));
                buffer = "";
            }
            else if(letter == ';') { //CHG
                tokens.push_back(Token(TokenType::TEXT, this->trim(buffer)));
                tokens.push_back(Token(TokenType::CHG));
                buffer = "";
            }
            else {
                buffer.push_back(letter);
            }
        }
        if(buffer.size() > 0) {
            tokens.push_back(Token(TokenType::TEXT, this->trim(buffer)));
        }
        tokens.push_back(Token(TokenType::EOL));
    }
    return tokens;
}
