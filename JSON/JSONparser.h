//
// Created by karina on 06/04/18.
//

#ifndef C_IDE_JSONPARSER_H
#define C_IDE_JSONPARSER_H


#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>

class JSONparser {

public:
    QJsonDocument writeMallocRequest(int);
    QJsonDocument writeDeclarationRequest(char, char);
    QJsonDocument writeDeclarationRequest(char, char, char);
    QJsonDocument writeAssignationRequest(char, char);
    QJsonDocument writeScopeRequest();
    QJsonDocument writeExpressionRequest(char, char, char);
    QJsonDocument writeRAMdata(int, std::string, std::string, int);
};


#endif //C_IDE_JSONPARSER_H
