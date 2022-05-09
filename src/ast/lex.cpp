#include "lex.hpp"

using namespace std;

Lexer::Lexer(string code, string filePath) : m_filePath(filePath), m_code(code) {
    m_line = 1;
    m_indexInLine = 0;
    m_index = 0;
}

void Lexer::throwError(string error) {
    string positionalErrorData;
    cout << m_filePath << ": Error on line " << m_line << " at index " << m_indexInLine - 1 << ": \n" << error << endl;

    for (int i = 0; i < m_indexInLine + 10; i++) {
        char c = peek(i - m_indexInLine + 1);
        if (c == '\n' || c == '\0') break;

        if (i == m_indexInLine - 2) positionalErrorData += "\x1B[31m";
        else positionalErrorData += "\033[0m";

        positionalErrorData += c;
    }
    cout << m_line << "| " << positionalErrorData << endl;

    for (int i = 0; i <= log10(m_line); i++) cout << " ";
    cout << "| ";
    for (int i = 0; i < m_indexInLine - 2; i++) cout << " ";
    cout << "^ \033[0m" << std::endl;

    exit(1);
}

char Lexer::peek() {
    return m_code[m_index];
}

char Lexer::peek(int offset) {
    return m_code[m_index + offset];
}

char Lexer::next() {
    if (m_index + 1 <= m_code.size()) {
        char c = m_code[m_index++];
        m_indexInLine++;
        if (c == '\n')
            m_line++, m_indexInLine = 1;
        return c;
    }
    else return '\0';
}


void Lexer::skipWhitespace() {
    char c = peek();
    if (!(c == ' ' || c == '\t' || c == '\n')) return;
    while (true) {
        c = peek();

        if (!(c == ' ' || c == '\t' || c == '\n')) break;
        next();
    }
}

void Lexer::skipLine() {
    char c = peek();
    if (c == '\n') return;
    while (true) {
        if (c == '\n' || c == '\0') break;
        c = next();
    }
}

string Lexer::getVariable() {
    string ret;
    while (true) {
        char c = peek();
        if (c == '\0') break;
        if (isAlpha(c) || isNumber(c)) ret.push_back(c);
        else break;
        next();
    }
    return ret;
}

string Lexer::getString() {
    string ret;
    char c;
    while (true) {
        c = peek();
        if (c == '\0') throwError("Unterminated string");
        if (c == '\n') m_line++;
        if (c == '"' && peek(-1) != '\\') { next(); break; }
        if (c == '\\' && peek(-1) != '\\') { next(); continue; }
        ret.push_back(c);
        next();
    }
    return ret;
}

string Lexer::getNumber() {
    string consumed;
    bool decimal = false;
    while (true) {
        char c = peek();
        if (c == '\0') break;
        if (isNumber(c)) consumed.push_back(c);
        else if (c == '.')
            if (decimal) throwError("Unexpected second decimal in number");
            else { decimal = true; consumed.push_back(c); }
        else break;
        next();
    }
    return consumed;
}

bool Lexer::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c == '_');
}

bool Lexer::isNumber(char c) {
    return (c >= '0' && c <= '9');
}

bool Lexer::isStringMatch(std::string target) {
    for (int i = 0; i < target.size(); i++)
        if (peek(i - 1) != target[i])
            return false;
    if (isAlpha(peek(target.size() - 1)) || isNumber(peek(target.size() - 1))) return false;
    for (int i = 0; i < target.size(); i++) next();
    return true;
}

bool Lexer::consumeToken(Token& t) {
    skipWhitespace();
    t = Token();
    t.type = TOKEN_NONE;
    char c = next();

    switch (c) {
        case '(':
            t.type = TOKEN_LEFT_PARENTHESIS;
            break;
        case ')':
            t.type = TOKEN_RIGHT_PARENTHESIS;
            break;
        case '{':
            t.type = TOKEN_LEFT_BRACE;
            break;
        case '}':
            t.type = TOKEN_RIGHT_BRACE;
            break;
        case '<':
            t.type = TOKEN_LEFT_BRACKET;
            if (isStringMatch("<=")) t.type = TOKEN_LESS_EQUAL;
            break;
        case '>':
            t.type = TOKEN_RIGHT_BRACKET;
            if (isStringMatch(">=")) t.type = TOKEN_GREATER_EQUAL;
            break;
        case '[':
            t.type = TOKEN_LEFT_SQUARE_BRACKET;
            break;
        case ']':
            t.type = TOKEN_RIGHT_SQUARE_BRACKET;
            break;
        case '$':
            t.type = TOKEN_DOLLAR_SIGN;
            break;
        case ',':
            t.type = TOKEN_COMMA;
            break;
        case ';':
            t.type = TOKEN_SEMICOLON;
            break;

        case '|':
            t.type = TOKEN_BITWISE_OR;
            if (isStringMatch("||")) t.type = TOKEN_OR;
            break;
        case '&':
            t.type = TOKEN_BITWISE_AND;
            if (isStringMatch("&&")) t.type = TOKEN_AND;
            break;
        case '!':
            t.type = TOKEN_NOT;
            break;
        case '~':
            t.type = TOKEN_BITWISE_NOT;
            break;
        case '^':
            t.type = TOKEN_BITWISE_XOR;
            break;

        case '=':
            t.type = TOKEN_EQUAL;
            if (isStringMatch("==")) t.type = TOKEN_EQUAL_EQUAL;
            break;

        case '+':
            t.type = TOKEN_PLUS;
            if (isStringMatch("++")) t.type = TOKEN_PLUS_PLUS;
            break;
        case '-':
            t.type = TOKEN_SUBTRACT;
            if (isStringMatch("--")) t.type = TOKEN_SUBTRACT_SUBTRACT;
            break;
        case '/':
            t.type = TOKEN_DIVIDE;
            if (isStringMatch("//")) skipLine();
            t.type = TOKEN_NONE;
            return true;
        case '*':
            t.type = TOKEN_MULTIPLY;
            break;
        case '%':
            t.type = TOKEN_MODULO;
            break;

        case '#':
            skipLine();
            t.type = TOKEN_NONE;
            return true;

        case 'C':
            if (isStringMatch("Component")) { t.type = TOKEN_COMPONENT_DEF; break; }
        case 'a':
            if (isStringMatch("and")) { t.type = TOKEN_AND; break; }
        case 'e':
            if (isStringMatch("else")) { t.type = TOKEN_ELSE; break; }
            if (isStringMatch("elif")) { t.type = TOKEN_ELSE_IF; break; }
        case 'f':
            if (isStringMatch("func")) { t.type = TOKEN_FUNCTION_DEF; break; }
        case 'i':
            if (isStringMatch("if")) { t.type = TOKEN_IF; break; }
            if (isStringMatch("is")) { t.type = TOKEN_EQUAL; break; }
        case 'o':
            if (isStringMatch("or")) { t.type = TOKEN_OR; break; }
        case 'n':
            if (isStringMatch("not")) { t.type = TOKEN_NOT; break; }

        case '\0':
            t.type = TOKEN_EOF;
    }

    if (t.type == TOKEN_NONE) {
        if (isNumber(c)) {
            t.type = TOKEN_NUMBER;
            t.data.tokenValue = getNumber();
        } else if (c == '"') {
            t.type = TOKEN_STRING;
            t.data.tokenValue = getString();
        } else if (isAlpha(c)) {
            t.type = TOKEN_VARIABLE;
            t.data.tokenValue = getVariable();
        } else {
            throwError("Invalid token");
        }
    }

    t.data.line = m_line;
    t.data.index = m_indexInLine;

    return false;
}

vector<Token> Lexer::lex() {
    cout << endl << m_filePath << ": " << endl;
    vector<Token> ret;
    Token consumed;
    consumeToken(consumed);

    while (consumed.type != TOKEN_EOF) {
        cout << consumed.typeStr() << endl;
        if (consumed.type != TOKEN_NONE) 
            ret.push_back(consumed);
        consumeToken(consumed);
    }

    return ret;
}
