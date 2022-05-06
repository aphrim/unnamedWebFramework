#include <vector>
#include <string>
#include <iostream>

#include "token.hpp"

using namespace std;

class Lexer {

public:
    Lexer(std::string& code);

    vector<Token> lex();


private:
    int m_line;
    int m_indexInLine; //Index within current line
    long int m_index; //Incase the code is greater than 2^31 characters. I hope that this never happens.
    string& m_code;

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
