#include<iostream>
#include<string>
#include<vector>
#pragma once

enum TokenType {
    EOL, SEP, CHG, TEXT
};

class Token {
    public:
        std::string value;
        TokenType type;
        Token(TokenType type, std::string value);
};


class Tokens {
    public:
        std::vector<Token> tokens;
        Tokens(std::vector<std::string> lines);
    private:
        std::vector<Token> tokenizer(std::vector<std::string> lines);
};
