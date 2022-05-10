#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include <fstream>

#include "token.hpp"

#pragma once

using namespace std;

class Lexer {

public:
    Lexer(string code, string filePath);

    vector<Token> lex();


private:
    int m_line;
    int m_indexInLine; //Index within current line
    long int m_index; //Incase the code is greater than 2^31 characters. I hope that this never happens.
    string m_code;
    string m_filePath;

    char peek();
    char peek(int offset);
    char next();
    void skipWhitespace();
    void skipLine();

    string getVariable();
    string getString();
    string getNumber();

    bool isAlpha(char c);
    bool isNumber(char c);
    bool isStringMatch(std::string target);

    void throwError(string error);

    bool consumeToken(Token& token);
};
