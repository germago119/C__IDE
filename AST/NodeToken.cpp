//
// Created by Roger Valderrama on 4/10/18.
//

#include "NodeToken.hpp"

int NodeToken::lineNumber = 1;

TokenType NodeToken::TokenLinter(std::string token) {
    char types[][7] = {"int", "char", "long", "double", "float"};
    for (char *type : types) {
        std::string stringType(type);
        if (stringType == token) {
            return DATA_TYPE;
        }
    }
    if (token == "=") {
        return ASSIGNMENT;
    } else if (token == ";") {
        return STATEMENT_TERMINATOR;
    } else if (token == "\n") {
        lineNumber++;
        return NEW_LINE;
    } else if (token == "{") {
        return OPEN_BRACKET;
    } else if (token == "}") {
        return CLOSE_BRACKET;
    } else if (token == "reference") {
        return REFERENCE;
    } else if (token == "<") {
        return OPEN_REFERENCE_BRACKET;
    } else if (token == ">") {
        return CLOSE_REFERENCE_BRACKET;
    } else if (token == "struct") {
        return STRUCT;
    } else if (token == "getAddr") {
        return ADDRESS;
    } else if (token == "print") {
        return PRINT;
    } else if (token == "getValue") {
        return VALUE;
    } else {

        std::regex regexIdentifier("[_a-zA-Z][_a-zA-Z0-9]*");
        if (regex_match(token, regexIdentifier)) {
            return IDENTIFIER;
        }
        std::regex regex("\'[A-Za-z]\'");
        if (regex_match(token, regex)) {
            return CHARACTER;
        }

        char arithmeticOperators[][2] = {"+", "-", "*", "/", "%", "(", ")"};
        for (char *arithmeticOperator:arithmeticOperators) {
            std::string stringOperator(arithmeticOperator);
            if (token == arithmeticOperator) {
                return OPERATOR;
            }
        }
        return CHARACTER;

    }
}

NodeToken::NodeToken(std::string value) {
    this->value = value;
    this->type = TokenLinter(value);
    this->line = lineNumber;
}

NodeToken::NodeToken(std::string value, TokenType type) {
    this->value = value;
    this->type = type;
    this->line = -1;
}
