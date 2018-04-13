//
// Created by Roger Valderrama on 4/10/18.
//

#include <Server/loguru.hpp>
#include "CodeParser.hpp"


std::vector<NodeToken *> *Lexer(std::string code) {
    using namespace boost;
    typedef tokenizer<char_separator<char>> tokenizer;

    char_separator<char> separator(" ", "\n+-/*%;{}<>()", drop_empty_tokens);

    auto *result = new std::vector<NodeToken *>();

    tokenizer tokens(code, separator);
    for (tokenizer::iterator beg = tokens.begin(); beg != tokens.end(); ++beg) {
        result->push_back(new NodeToken(*beg));
    }
    return result;
}


std::vector<NodeToken *> *NodeTokens = nullptr;

void parseCode(std::string code) {

    if (NodeTokens == nullptr) {
        NodeTokens = Lexer(code);
    }

    parseCode(NodeTokens);

}

void parseCode(std::vector<NodeToken *> *tokens) {
    int tokensDropped = 0;

    int COMPLETE_REFERENCE = REFERENCE * OPEN_REFERENCE_BRACKET * DATA_TYPE * CLOSE_REFERENCE_BRACKET;

    JSONVar *pJsonVar = nullptr;
    JSONStruct *pJsonStruct = nullptr;

    int counter = 1;
    for (auto &&token:*tokens) {
        tokensDropped++;
        if (token->type == DATA_TYPE || token->type == REFERENCE) {
            if (counter == REFERENCE * OPEN_REFERENCE_BRACKET) {
                std::string newType = pJsonVar->get("Type");
                newType.append(" ").append(token->value);
                pJsonVar->put("Type", newType);
                counter *= DATA_TYPE;
                continue;
            } else if (counter != 1 && pJsonStruct == nullptr) {
                LOG_F(ERROR, "Invalid Syntax");
                return;
            }
            counter *= token->type;
            pJsonVar = new JSONVar();
            pJsonVar->put("Type", token->value);
            pJsonVar->put("Scope", currentScope);

        } else if (token->type == IDENTIFIER) {
            if (counter == DATA_TYPE || counter == COMPLETE_REFERENCE) {

                pJsonVar->put("Identifier", token->value);

            } else if (counter % ASSIGNMENT == 0) {
                pJsonVar->addValue(token->value, token);
            } else if (pJsonStruct != nullptr) {
                pJsonStruct->put("Identifier", token->value);
            } else {
            }

            counter *= IDENTIFIER;
        } else if (token->type == ASSIGNMENT) {
            if (counter == DATA_TYPE * IDENTIFIER ||
                counter == IDENTIFIER || counter == COMPLETE_REFERENCE * IDENTIFIER) {
                counter *= ASSIGNMENT;
            } else {
                delete (pJsonVar);
                LOG_F(ERROR, "Count: %d", counter);
                return;
            }
        } else if (token->type == CHARACTER) {
            if (counter % (DATA_TYPE * IDENTIFIER * ASSIGNMENT) == 0 ||
                counter % (IDENTIFIER * ASSIGNMENT) == 0 ||
                counter % (COMPLETE_REFERENCE * IDENTIFIER * ASSIGNMENT) == 0) {
                pJsonVar->addValue(token->value, token);
            } else {
                LOG_F(ERROR, "Invalid Syntax");
                return;
            }

        } else if (token->type == STATEMENT_TERMINATOR) {
            if (pJsonStruct == nullptr) {
                QJsonDocument u = QJsonDocument(*pJsonVar->get());
                finalJSON = u;
                std::cout << pJsonVar->toString() << std::endl;
                LOG_F(INFO, "%s \n", pJsonVar->toLog());

            } else if (pJsonVar == nullptr) {
                pJsonStruct->submit();
                QString str = QString::fromStdString(pJsonStruct->toString());
                QJsonDocument u = QJsonDocument::fromJson(str.toUtf8());
                finalJSON = u;
                delete (pJsonStruct);
                pJsonStruct = nullptr;

            } else {
                pJsonStruct->add(pJsonVar);
                delete (pJsonVar);
                pJsonVar = nullptr;
                counter = 1;
                continue;
            }
            delete (pJsonVar);
            pJsonVar = nullptr;
            counter = 1;
            break;

        } else if (token->type == OPERATOR) {
            if (pJsonVar != nullptr) {
                pJsonVar->addValue(token->value, token);
            }
        } else if (token->type == OPEN_REFERENCE_BRACKET) {
            if (counter == REFERENCE) {
                counter *= OPEN_REFERENCE_BRACKET;
            } else {
                LOG_F(ERROR, "Syntax Error");
            }
        } else if (token->type == CLOSE_REFERENCE_BRACKET) {
            if (counter == REFERENCE * OPEN_REFERENCE_BRACKET * DATA_TYPE) {
                counter *= CLOSE_REFERENCE_BRACKET;
            } else {
                LOG_F(ERROR, "Syntax Error");
            }
        } else if (token->type == OPEN_BRACKET) {
            if (pJsonStruct != nullptr) {

            } else { currentScope++; }
        } else if (token->type == CLOSE_BRACKET) {
            if (pJsonStruct != nullptr) {

            } else {
                currentScope--;
            }

        } else if (token->type == STRUCT) {
            if (counter != 1) {
                LOG_F(ERROR, "Syntax Error");
                return;
            }
            pJsonStruct = new JSONStruct();
        } else if (token->type == NEW_LINE) {
            continue;
        } else {
            LOG_F(ERROR, "Syntax Error");
            return;
        }
    }
    tokens->erase(tokens->begin(), tokens->begin() + tokensDropped);
    if ((pJsonVar != nullptr || currentScope != 0) && tokens->empty()) {
        LOG_F(ERROR, "Semicolon Missing");
    } else if (pJsonStruct != nullptr) {
        LOG_F(ERROR, "} Missing");
    }
}

QJsonDocument getJSON() {
    return finalJSON;
}

