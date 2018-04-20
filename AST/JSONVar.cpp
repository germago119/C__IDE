//
// Created by Roger Valderrama on 4/10/18.
//

#include "JSONVar.hpp"
#include <Server/loguru.hpp>

void JSONVar::put(std::string key, std::string value) {
    auto *qJsonValue = new QJsonValue(QString::fromStdString(value));
    this->json->insert(QString::fromStdString(key), *qJsonValue);
    delete (qJsonValue);
}

void JSONVar::put(std::string key, int value) {
    auto *qJsonValue = new QJsonValue(value);
    this->json->insert(QString::fromStdString(key), *qJsonValue);
    delete (qJsonValue);
}


QJsonObject *JSONVar::get() {
    return this->json;
}

const char *JSONVar::toLog() {
    QJsonDocument doc(*this->json);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    return strJson.toUtf8().constData();
}

std::string JSONVar::toString() {
    QJsonDocument doc(*this->json);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    return strJson.toStdString();
}

std::string JSONVar::get(std::string key) {

    const QJsonValue &qJsonValue = json->value(QString::fromStdString(key));
    if (qJsonValue.isUndefined()) {
        return "";
    }
    return qJsonValue.toString().toStdString();
}

JSONVar *findVariable(const std::string &) {
    return nullptr;
};

void JSONVar::addValue(std::string value, NodeToken *token) {
    std::string errorMessage = "";
    const char *logError = "";
    if (token->type == IDENTIFIER) {
        value = token->value;
        JSONVar *pJSONVar = findVariable(token->value);
        if (pJSONVar == nullptr) {
            LOG_F(ERROR, "Variable doesn't exist");
            return;
        }
    } else if (token->type == CHARACTER) {
        if (this->get("Type") == "long") {
            try {
                boost::lexical_cast<long>(value);
            } catch (boost::bad_lexical_cast) {
                errorMessage =
                        "Error in line" + std::to_string(token->line) + " : Variable \"" + this->get("Identifier") +
                        "\" is not of type long\n";
                logError = errorMessage.c_str();
                return LOG_F(ERROR, logError);
            }
        } else if (this->get("Type") == "int") {
            try {
                boost::lexical_cast<int>(value);
            } catch (boost::bad_lexical_cast) {
                errorMessage =
                        "Error in line" + std::to_string(token->line) + " : Variable \"" + this->get("Identifier") +
                        "\" is not of type int\n";
                logError = errorMessage.c_str();
                return LOG_F(ERROR, logError);
            }
        } else if (this->get("Type") == "float") {
            try {
                boost::lexical_cast<float>(value);
            } catch (boost::bad_lexical_cast) {
                errorMessage =
                        "Error in line" + std::to_string(token->line) + " : Variable \"" + this->get("Identifier") +
                        "\" is not of type float\n";
                logError = errorMessage.c_str();
                return LOG_F(ERROR, logError);
            }
        } else if (this->get("Type") == "double") {
            try {
                boost::lexical_cast<double>(value);
            } catch (boost::bad_lexical_cast) {
                errorMessage =
                        "Error in line" + std::to_string(token->line) + " : Variable \"" + this->get("Identifier") +
                        "\" is not of type double\n";
                logError = errorMessage.c_str();
                return LOG_F(ERROR, logError);
            }
        } else if (this->get("Type") == "char") {
            if (!regex_match(value, std::regex("\'[A-Za-z]\'"))) {
                errorMessage =
                        "Error in line" + std::to_string(token->line) + " : Variable \"" + this->get("Identifier") +
                        "\" is not of type double\n";
                logError = errorMessage.c_str();
                return LOG_F(ERROR, logError);
            }
        }
    } else if (token->type == OPERATOR) {
        std::string type = this->get("Type");
        if (type != "int" && type != "double" && type != "float" && type != "long" && type != "") {
            errorMessage = "Error in line" + std::to_string(token->line) + " : Can't use <" + token->value +
                           "> operator with non numeric data type\n";
            logError = errorMessage.c_str();
            return LOG_F(ERROR, logError);
        }
    }
    this->put("Value", this->get("Value").append(value));
    return LOG_F(INFO, logError);
}
