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
    if (token->type == IDENTIFIER) {
        JSONVar *pJSONVar = findVariable(token->value);
        if (pJSONVar == nullptr) {
            LOG_F(ERROR, "Variable doesn't exist");
            return;
        }
        if (pJSONVar->get("Type") != this->get("Type")) {
            LOG_F(ERROR, "Types don't match");
            std::cout << "types don't match" << std::endl;
            return;
        }
        value = pJSONVar->get("Value");
    } else if (token->type == CHARACTER) {
        std::cout << "is " << value << " of type " << this->get("Type") << std::endl;
    } else if (token->type == OPERATOR) {
        std::string type = this->get("Type");
        if (type != "int" && type != "double" && type != "float" && type != "long") {
            LOG_F(ERROR, "Invalid Syntax");
            return;
        }
    }
    this->put("Value", this->get("Value").append(value));

}
