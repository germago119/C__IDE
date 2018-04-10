//
// Created by karina on 06/04/18.
//
#include <iostream>
#include "JSONparser.h"

/**
 * Writes a JSON document with the subject "Total_Malloc"
 * to request memory allocation for the current program in C!
 * @param totalMem
 * @return
 */
QJsonDocument JSONparser::writeMallocRequest(int totalMem) {
    QJsonObject value;
    value.insert("Value", totalMem);

    QJsonArray content;
    content.push_back(value);

    QJsonObject message;
    message.insert("Subject", "Total_Malloc");
    message.insert("Contents", content);

    QJsonDocument json(message);

    return json;
}

QJsonDocument JSONparser::writeDeclarationRequest(std::string identifier, std::string type) {
    QString str = QString::fromStdString(identifier);
    QJsonObject obj;
    obj.insert("Identifier", str);
    str = QString::fromStdString(type);
    obj.insert("Type", str);

    QJsonArray content;
    content.push_back(obj);

    QJsonObject message;
    message.insert("Subject", "Declaration");
    message.insert("Contents", content);

    QJsonDocument json(message);

    return json;
}

QJsonDocument JSONparser::writeDeclarationRequest(std::string identifier, std::string type, std::string value) {
    QString str = QString::fromStdString(identifier);
    QJsonObject obj;
    obj.insert("Identifier", str);
    str = QString::fromStdString(type);
    obj.insert("Type", str);
    str = QString::fromStdString(value);
    obj.insert("Value", str);

    QJsonArray content;
    content.push_back(obj);


    QJsonObject message;
    message.insert("Subject", "Declaration");
    message.insert("Contents", content);

    QJsonDocument json(message);

    return json;
}

QJsonDocument JSONparser::writeScopeRequest() {
    //QString str = QString::fromStdString(value);
    QJsonDocument json;
    return json;
}

QJsonDocument JSONparser::writeExpressionRequest(std::string var1, std::string var2, std::string oprt) {
    QString str = QString::fromStdString(var1);
    QJsonObject obj;
    obj.insert("Var_1", str);
    str = QString::fromStdString(var2);
    obj.insert("Var_2", str);
    str = QString::fromStdString(oprt);
    obj.insert("Operator", str);

    QJsonArray content;
    content.push_back(obj);

    QJsonObject message;
    message.insert("Subject", "Expression");
    message.insert("Contents", content);

    QJsonDocument json(message);

    return json;
}

QJsonDocument JSONparser::writeAssignationRequest(std::string identifier, std::string value) {
    QString str = QString::fromStdString(identifier);
    QJsonObject obj;
    obj.insert("Identifier", str);
    str = QString::fromStdString(value);
    obj.insert("Value", str);

    QJsonArray content;
    content.push_back(obj);

    QJsonObject message;
    message.insert("Subject", "Assignation");
    message.insert("Contents", content);

    QJsonDocument json(message);

    return json;
}

QJsonDocument JSONparser::writeRAMdata(int dir, std::string value, std::string id, int references) {
    QString str = QString::fromStdString(value);
    QJsonObject obj;
    obj.insert("Direction", dir);
    obj.insert("Value", str);
    str = QString::fromStdString(id);
    obj.insert("Name",str);
    obj.insert("References", references);

    QJsonArray content;
    content.push_back(obj);

    QJsonObject message;
    message.insert("Subject", "RAM");
    message.insert("Contents", content);

    QJsonDocument json(message);

    return json;
}
