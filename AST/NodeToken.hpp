//
// Created by Roger Valderrama on 4/10/18.
//

/**
 * @file NodeToken.hpp
 * @version 1.0
 * @date 4/10/18
 * @author Roger Valderrama
 * @title Tokens for CodeParser
 * @brief TokenType and NodeToken for CodeParser
 */


#ifndef C_IDE_NODETOKEN_HPP
#define C_IDE_NODETOKEN_HPP

#include <regex>
#include <iostream>
#include <boost/lexical_cast.hpp>

/**
 * @brief Enum for the posible Types of token.
 */
enum TokenType {
    IDENTIFIER = 2,
    STRUCT = 3,
    OPERATOR = 5, // + - * % /
    NEW_LINE = 7, // \n
    CHARACTER = 11, // [a-z0-9]
    REFERENCE = 13, //
    DATA_TYPE = 15, // char int float long double
    ASSIGNMENT = 17, // =
    OPEN_BRACKET = 19, // {
    CLOSE_BRACKET = 21, // }
    STATEMENT_TERMINATOR = 23, // ;
    OPEN_REFERENCE_BRACKET = 25, // <
    CLOSE_REFERENCE_BRACKET = 27, // >
    ADDRESS = 29, // getAddr()
    PRINT = 31, // print func
    VALUE = 33 //getValue()

};

class NodeToken {

public:
    TokenType type;
    std::string value;

    /**
    * @brief Constructor that needs a value.
     * @param value.
    */
    explicit NodeToken(std::string value);


private:
    TokenType TokenLinter(std::string);
};


#endif //C_IDE_NODETOKEN_HPP
