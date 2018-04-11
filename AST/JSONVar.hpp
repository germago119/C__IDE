//
// Created by Roger Valderrama on 4/10/18.
//

#ifndef C_IDE_JSONVAR_HPP
#define C_IDE_JSONVAR_HPP

#include <iostream>
#include <vector>
#include <QtCore/QJsonObject>
#include "NodeToken.hpp"
#include <QtCore/QJsonDocument>


class JSONVar {

private:
    QJsonObject *json = new QJsonObject();

public:
    const char *toLog();

    std::string toString();

    QJsonObject *get();

    std::string get(std::string);

    void put(std::string, int);

    void put(std::string, char);

    void put(std::string, long);

    void put(std::string, double);

    void put(std::string, std::string);

    void addValue(std::string value, NodeToken *token);
};


#endif //C_IDE_JSONVAR_HPP
