//
// Created by Roger Valderrama on 4/10/18.
//

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

std::vector<NodeToken *> *Lexer(std::string);


#endif //C_IDE_CODEPARSER_HPP
