/*
 
    token.hpp

Purpose: 
    Defintions for structs and enums relating to tokens

TokenType - Enum for types of tokens
TokenData - Struct for storing data about a token
Token - Stores type of token (TokenType), and data of token (TokenData)
 */

#pragma once

#include <string>

using namespace std;

typedef enum {

    //

    TOKEN_COMPONENT_DEF, TOKEN_FUNCTION_DEF, 

    //

    TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE, 
    TOKEN_LEFT_BRACKET, TOKEN_RIGHT_BRACKET,
    TOKEN_LEFT_PARENTHESIS, TOKEN_RIGHT_PARENTHESIS,
    TOKEN_LEFT_SQUARE_BRACKET, TOKEN_RIGHT_SQUARE_BRACKET,
    TOKEN_DOLLAR_SIGN, TOKEN_COMMA,
    TOKEN_SEMICOLON,

    //
    
    TOKEN_IF, TOKEN_ELSE, TOKEN_ELSE_IF,

    //

    TOKEN_OR, TOKEN_AND, TOKEN_NOT,
    TOKEN_BITWISE_OR, TOKEN_BITWISE_AND, TOKEN_BITWISE_NOT, TOKEN_BITWISE_XOR,

    //

    TOKEN_EQUAL,
    TOKEN_PLUS, TOKEN_PLUS_PLUS,
    TOKEN_SUBTRACT, TOKEN_SUBTRACT_SUBTRACT,
    TOKEN_DIVIDE, TOKEN_MULTIPLY, TOKEN_MODULO,

    //

    TOKEN_EQUAL_EQUAL,
    TOKEN_GREATER_EQUAL,
    TOKEN_LESS_EQUAL,

    //

    TOKEN_VARIABLE, 
    TOKEN_NUMBER,
    TOKEN_STRING,

    //

    TOKEN_NONE,
    TOKEN_RETURN,
    TOKEN_ERROR,
    TOKEN_EOF,

} TokenType;

typedef struct {
    int line;
    int index;
    string tokenValue;
} TokenData;

typedef struct {
    TokenType type;
    TokenData data;

    string typeStr() {
        switch (type) {
            case TOKEN_COMPONENT_DEF: return "TOKEN_COMPONENT_DEF";
            case TOKEN_FUNCTION_DEF: return "TOKEN_FUNCTION_DEF";
            
            case TOKEN_LEFT_BRACE: return "TOKEN_LEFT_BRACE";
            case TOKEN_RIGHT_BRACE: return "TOKEN_RIGHT_BRACE";
            case TOKEN_LEFT_BRACKET: return "TOKEN_LEFT_BRACKET";
            case TOKEN_RIGHT_BRACKET: return "TOKEN_RIGHT_BRACKET";
            case TOKEN_LEFT_PARENTHESIS: return "TOKEN_LEFT_PARENTHESIS";
            case TOKEN_RIGHT_PARENTHESIS: return "TOKEN_RIGHT_PARENTHESIS";
            case TOKEN_LEFT_SQUARE_BRACKET: return "TOKEN_LEFT_SQUARE_BRACKET";
            case TOKEN_RIGHT_SQUARE_BRACKET: return "TOKEN_RIGHT_SQUARE_BRACKET";

            case TOKEN_DOLLAR_SIGN: return "TOKEN_DOLLAR_SIGN";
            case TOKEN_COMMA: return "TOKEN_COMMA";
            case TOKEN_SEMICOLON: return "TOKEN_SEMICOLON";

            case TOKEN_IF: return "TOKEN_IF";
            case TOKEN_ELSE: return "TOKEN_ELSE";
            case TOKEN_ELSE_IF: return "TOKEN_ELSE_IF";

            case TOKEN_OR: return "TOKEN_OR";
            case TOKEN_AND: return "TOKEN_AND";
            case TOKEN_NOT: return "TOKEN_NOT";
            
            case TOKEN_BITWISE_OR: return "TOKEN_BITWISE_OR";
            case TOKEN_BITWISE_AND: return "TOKEN_BITWISE_AND";
            case TOKEN_BITWISE_NOT: return "TOKEN_BITWISE_NOT";
            case TOKEN_BITWISE_XOR: return "TOKEN_BITWISE_XOR";

            case TOKEN_EQUAL: return "TOKEN_EQUAL";
            case TOKEN_PLUS: return "TOKEN_PLUS";
            case TOKEN_PLUS_PLUS: return "TOKEN_PLUS_PLUS";
            case TOKEN_SUBTRACT: return "TOKEN_SUBTRACT";
            case TOKEN_SUBTRACT_SUBTRACT: return "TOKEN_SUBTRACT_SUBTRACT";
            case TOKEN_DIVIDE: return "TOKEN_DIVIDE";
            case TOKEN_MULTIPLY: return "TOKEN_MULTIPLY";
            case TOKEN_MODULO: return "TOKEN_MODULO";

            case TOKEN_EQUAL_EQUAL: return "TOKEN_EQUAL_EQUAL";
            case TOKEN_GREATER_EQUAL: return "TOKEN_GREATER_EQUAL";
            case TOKEN_LESS_EQUAL: return "TOKEN_LESS_EQUAL";

            case TOKEN_VARIABLE: return "TOKEN_VARIABLE";
            case TOKEN_NUMBER: return "TOKEN_NUMBER";
            case TOKEN_STRING: return "TOKEN_STRING";

            case TOKEN_RETURN: return "TOKEN_RETURN";
            case TOKEN_NONE: return "TOKEN_NONE";
            case TOKEN_ERROR: return "TOKEN_ERROR";
            case TOKEN_EOF: return "TOKEN_EOF";
            default: return "UNKNOWN TOKEN";
        }
    }
} Token;
