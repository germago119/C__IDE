//
// Created by Roger Valderrama on 4/10/18.
//

/**
 * @file JSONStruct.hpp
 * @version 1.0
 * @date 4/10/18
 * @author Roger Valderrama
 * @title JSON for Structs
 * @brief JSON Class for saving structs with its variables.
 */


#ifndef C_IDE_JSONSTRUCT_HPP
#define C_IDE_JSONSTRUCT_HPP

#include "JSONVar.hpp"
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>


class JSONStruct {

    /**
     * @brief An array oj Json for the variables of the line of code.
     */
    QJsonArray *variables = new QJsonArray;

    /**
     * @brief json that represent the JsonObject that will be modified.
     */
    QJsonObject *json = new QJsonObject;

public:
    /**
    * @brief It add all variables to a Json and it prints it and add it to the log file.
    */
    void submit();

    /**
    * @brief Converts the JSON into a char so it can be added to the log file.
    */
    const char *toLog();

    /**
    * @brief Converts the JSON into a string.
    */
    std::string toString();

    /**
    * @brief It adds Variables to the JSON for struct.
     * @param jsonVar each json variable it will add.
    */
    void add(JSONVar *jsonVar);

    /**
     * @brief It inserts to the JSON each key with its value.
    */
    void put(std::string, std::string);
};


#endif //C_IDE_JSONSTRUCT_HPP
