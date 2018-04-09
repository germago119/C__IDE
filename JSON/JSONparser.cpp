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

    return json;
}

QJsonDocument JSONparser::writeDeclarationRequest(char identifier, char type) {
    QJsonObject id_obj;
    id_obj.insert("Identifier", identifier);

    QJsonObject type_obj;
    type_obj.insert("Type", type);

    QJsonArray content;
    content.push_back(type_obj);
    content.push_back(id_obj);

    QJsonObject message;
    message.insert("Subject", "Declaration");
    message.insert("Contents", content);

    QJsonDocument json(message);

    return json;
}

QJsonDocument JSONparser::writeDeclarationRequest(char identifier, char type, char value) {
    QJsonObject id_obj;
    id_obj.insert("Identifier", identifier);

    QJsonObject type_obj;
    type_obj.insert("Type", type);

    QJsonObject value_obj;
    value_obj.insert("Value", value);

    QJsonArray content;
    content.push_back(type_obj);
    content.push_back(id_obj);
    content.push_back(value_obj);

    QJsonObject message;
    message.insert("Subject", "Declaration");
    message.insert("Contents", content);

    QJsonDocument json(message);

    return json;
}

QJsonDocument JSONparser::writeScopeRequest() {
    QJsonDocument json;
    return json;
}

QJsonDocument JSONparser::writeExpressionRequest(char var1, char var2, char operator_) {
    QJsonObject var1_obj;
    var1_obj.insert("Var_1", var1);

    QJsonObject var2_obj;
    var2_obj.insert("Var_2", var2);

    QJsonObject operator_obj;
    operator_obj.insert("Operator", operator_);

    QJsonArray content;
    content.push_back(var1_obj);
    content.push_back(var2_obj);
    content.push_back(operator_obj);

    QJsonObject message;
    message.insert("Subject", "Expression");
    message.insert("Contents", content);

    QJsonDocument json(message);

    return json;
}

QJsonDocument JSONparser::writeAssignationRequest(char identifier, char value) {
    QJsonObject id_obj;
    id_obj.insert("Identifier", identifier);

    QJsonObject value_obj;
    value_obj.insert("Value", value);

    QJsonArray content;
    content.push_back(id_obj);
    content.push_back(value_obj);

    QJsonObject message;
    message.insert("Subject", "Assignation");
    message.insert("Contents", content);

    QJsonDocument json(message);

    return json;
}

QJsonDocument JSONparser::writeRAMdata(int dir, std::string value, std::string id, int references) {
    QJsonObject obj;
    obj.insert("Direction", "0x0002");
    obj.insert("Value", "100");
    obj.insert("Name", "Total_mem");
    obj.insert("References", "1");

    QJsonArray content;
    content.push_back(obj);

    QJsonObject message;
    message.insert("Subject", "RAM");
    message.insert("Contents", content);

    QJsonDocument json(message);

    return json;
}
