#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include "base-converter.h"

class Parse
{
    public:
        std::queue<std::string> infixToPostfix(const std::string equation);
        double evalPostfix(std::queue<std::string> eq, const int base);
        bool isBalance(std::string equation);

    private:
        bool isSymbol(const char& check);
        bool isDigit(const char& check);
        bool isValidDigit(const std::string& str);
        const int priorityNumber(const char& symbol);
        bool isOpenCloseMatch(const char& open, const char& close);
        bool isOpenParen(const char& symbol);
        bool isCloseParen(const char& symbol);
};


bool isBalance(std::string equation);
double evaluatePostfix(std::queue<std::string> eq, const int base);
std::queue<std::string> parseInfixToPostfix(const std::string equation);

#endif