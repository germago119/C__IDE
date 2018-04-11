//
// Created by Roger Valderrama on 4/10/18.
//

#ifndef C_IDE_JSONSTRUCT_HPP
#define C_IDE_JSONSTRUCT_HPP

#include "JSONVar.hpp"
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>


class JSONStruct {
    QJsonArray *variables = new QJsonArray;
    QJsonObject *json = new QJsonObject;

public:
    void submit();

    const char *toLog();

    std::string toString();

    void add(JSONVar *jsonVar);

    void put(std::string, std::string);
};


#endif //C_IDE_JSONSTRUCT_HPP
