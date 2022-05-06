#include <fstream> 

#include "ast/lex.hpp"

using namespace std;

void compileFile(char* path) {
    ifstream file;
    file.open(path, ios::in);
    string chunk, data;
    while (getline(file, chunk)) data += chunk + '\n';
    file.close();

    Lexer lexer = Lexer(data);
    lexer.lex();
}

int main(int argc, char** argv) {
    compileFile(argv[1]);
}
