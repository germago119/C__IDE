//
// Created by Roger Valderrama on 4/10/18.
//

/**
 * @file CodeParser.hpp
 * @version 1.0
 * @date 4/10/18
 * @author Roger Valderrama
 * @title
 * @brief
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

void parseCode(std::string);

void parseCode(std::vector<NodeToken *> *);

QJsonDocument getJSON();

std::vector<NodeToken *> *Lexer(std::string);
static QJsonDocument finalJSON;

#endif //C_IDE_CODEPARSER_HPP
