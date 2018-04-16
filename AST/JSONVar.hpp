//
// Created by Roger Valderrama on 4/10/18.
//

/**
 * @file JSONVar.hpp
 * @version 1.0
 * @date 4/10/18
 * @author Roger Valderrama
 * @title
 * @brief
 */


#ifndef C_IDE_JSONVAR_HPP
#define C_IDE_JSONVAR_HPP

#include <iostream>
#include <vector>
#include <QtCore/QJsonObject>
#include "NodeToken.hpp"
#include <QtCore/QJsonDocument>


class JSONVar {

private:
    /**
     * @brief json that represent the JsonObject that will be modified.
     */
    QJsonObject *json = new QJsonObject();

public:
    /**
 * @brief Convert JSON to char for the log file.
 */
    const char *toLog();

/**
 * @brief Convert JSON to string.
 */
    std::string toString();

    /**
 * @brief Getter for the json attribute.
 */
    QJsonObject *get();

    /**
 * @brief Getter using the key.
 */
    std::string get(std::string);

    /**
 * @brief Set up the JSON when the value its an int.
 */
    void put(std::string, int);

    /**
 * @brief Set up the JSON when the value its a char.
 */
    void put(std::string, char);

    /**
 * @brief Set up the JSON when the value its a long.
 */
    void put(std::string, long);

    /**
 * @brief Set up the JSON when the value its a double.
 */
    void put(std::string, double);

    /**
 * @brief Set up the JSON when the value its a string.
 */
    void put(std::string, std::string);

    /**
 * @brief Sets value to each token.
     * @param value
     * @param token
 */
    void addValue(std::string value, NodeToken *token);
};


#endif //C_IDE_JSONVAR_HPP
