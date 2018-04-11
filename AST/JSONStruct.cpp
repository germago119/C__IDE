//
// Created by Roger Valderrama on 4/10/18.
//

#include "JSONStruct.hpp"
#include <Server/loguru.hpp>

void JSONStruct::submit() {
    auto *qJsonValue = new QJsonValue(*variables);
    this->json->insert("Variables", *qJsonValue);
    delete (qJsonValue);
    std::cout << this->toString() << std::endl;
    LOG_F(INFO, "%s \n", this->toLog());
}

const char *JSONStruct::toLog() {
    QJsonDocument doc(*this->json);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    return strJson.toUtf8().constData();
}

std::string JSONStruct::toString() {
    QJsonDocument doc(*this->json);
    QString strJson(doc.toJson(QJsonDocument::Compact));
    return strJson.toStdString();
}

void JSONStruct::add(JSONVar *jsonVar) {
    QJsonValue qJsonValue = QJsonValue(*jsonVar->get());
    this->variables->append(qJsonValue);
}

void JSONStruct::put(std::string key, std::string value) {
    QJsonValue *qJsonValue = new QJsonValue(QString::fromStdString(value));
    this->json->insert(QString::fromStdString(key), *qJsonValue);
    delete (qJsonValue);
}
