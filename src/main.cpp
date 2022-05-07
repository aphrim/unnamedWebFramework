#include <fstream> 
#include <map>
#include <string>

#include "ast/lex.hpp"
#include "ast/preprocessor.hpp"

using namespace std;

void compileFile(char* path) {

    map<string, string>* includedFiles = new map<string, string>();
    PreProcessor preprocessor = PreProcessor(path, includedFiles);
    preprocessor.process();

    vector<Token> lexedCode;

    for (auto it : *includedFiles) {
        Lexer lexer = Lexer(it.second, it.first);
        vector<Token> fileLexed = lexer.lex();
        lexedCode.insert(lexedCode.begin(), fileLexed.begin(), fileLexed.end());
    }
}

int main(int argc, char** argv) {
    compileFile(argv[1]);
}
