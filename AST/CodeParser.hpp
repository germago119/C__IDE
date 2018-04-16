//
// Created by Roger Valderrama on 4/10/18.
//

/**
 * @file CodeParser.hpp
 * @version 1.0
 * @date 4/10/18
 * @author Roger Valderrama
 * @title Code Parser
 * @brief Methods that receives code as a string from GUI and it parse it into tokens
 */


#ifndef C_IDE_CODEPARSER_HPP
#define C_IDE_CODEPARSER_HPP


#include <vector>
#include <iostream>
#include <QJsonObject>
#include "JSONVar.hpp"
#include "NodeToken.hpp"
#include "JSONStruct.hpp"
#include <boost/tokenizer.hpp>

static int currentScope = 0;

/**
 * @brief Receives a String it Lexes it into tokens and the send it to the other parseCode.
 */
void parseCode(std::string);

/**
 * @brief Receives a pointer of a vector of NodeTokens that it classify it token into a TokenType Enum.
 */
void parseCode(std::vector<NodeToken *> *);

/**
 * @brief It gets a QJsonDocument that represents the finalJSON.
 */
QJsonDocument getJSON();

/**
 * @brief It use Boost Tokenizer to lex the code and separate it into a vector of NodeToken.
 */
std::vector<NodeToken *> *Lexer(std::string);
static QJsonDocument finalJSON;

#endif //C_IDE_CODEPARSER_HPP
