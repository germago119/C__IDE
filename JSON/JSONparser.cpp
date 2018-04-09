//
// Created by karina on 06/04/18.
//
#include <iostream>
#include "JSONparser.h"

QJsonDocument JSONparser::writeMallocRequest(int totalMem) {

    QJsonObject value;
    value.insert("Value", totalMem);

    QJsonArray content;
    content.push_back(value);

    QJsonObject message;
    message.insert("Subject", "Total_Malloc");
    message.insert("Contents", content);

    QJsonDocument json(message);
    std::cout << "Enviando json de malloc" << std::endl;

    return json;
}

QJsonDocument JSONparser::writeDeclarationRequest(char identifier, char type) {
    QJsonObject value;
    value.insert("Value", identifier);

    QJsonArray content;
    content.push_back(value);

    QJsonObject message;
    message.insert("Subject","Total_Malloc");
    message.insert("Contents", content);

    QJsonDocument json(message);

    return json;
}

QJsonDocument JSONparser::writeDeclarationRequest(char identifier, char type, char value) {
    QJsonDocument json;
    return json;
}

QJsonDocument JSONparser::writeScopeRequest() {
    QJsonDocument json;
    return json;
}

QJsonDocument JSONparser::writeExpressionRequest() {
    QJsonDocument json;
    return json;
}
