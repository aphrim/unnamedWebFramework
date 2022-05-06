#include <vector>
#include <string>

#include "token.hpp"

using namespace std;

class Lexer {

public:
    Lexer(std::string& code);

    vector<Token> lex();


private:
    int line;
    int indexInLine; //Index within current line
    long int index; //Incase the code is greater than 2^31 characters. I hope that this never happens.

    char peek();
    char next();
    void skipWhitespace();

    void throwError(string& error);

    Token consumeToken();
}
