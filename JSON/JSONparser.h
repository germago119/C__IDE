//
// Created by karina on 06/04/18.
//
/**
 * @file JSONparser.h
 * @version 1.0
 * @date 06/04/18
 * @author Karina Martínez Guerrero
 * @title Parseador de JSON
 * @brief Clase de escritura para JSON
 */

#ifndef C_IDE_JSONPARSER_H
#define C_IDE_JSONPARSER_H


#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonArray>

class JSONparser {

public:
    /**
     * @brief Crea un JSON con formato para solicitar memoria
     * @param total_mem Cantidad total de memoria
     * @return JSON del request de memoria
     */
    QJsonDocument writeMallocRequest(int total_mem);
    /**
     * @brief Crea un JSON con formato para solicitar una declaración de variable
     * @param identifier Identificador de la variable
     * @param type Tipo de la variable
     * @return JSON del request
     */
    QJsonDocument writeDeclarationRequest(std::string identifier, std::string type);
    /**
     * @brief Crea un JSON con formato para solicitar una declaración de variable y su
     * inicialización
     * @param identifier Identificador de la variable
     * @param type Tipo de la variable
     * @param value Valor de la variable
     * @return JSON del request
     */
    QJsonDocument writeDeclarationRequest(std::string identifier, std::string type, std::string value);
    /**
     * @brief Crea un JSON para solicitar la asignación de un valor a una variable
     * @param identifier Identificador de la variable
     * @param value Valor a asignar
     * @return JSON del request
     */
    QJsonDocument writeAssignationRequest(std::string identifier, std::string value);
    QJsonDocument writeScopeRequest();
    /**
     * @brief Crea un JSON para solicitar el cálculo de una expresión
     * @param var1 Primer término
     * @param var2 Segundo término
     * @param optr operador de la expresión
     * @return JSON del request
     */
    QJsonDocument writeExpressionRequest(std::string var1, std::string var2, std::string optr);
    /**
     * @brief Crea un JSON con los datos para el LiveRAMView
     * @param dir Dirección de memoria
     * @param name Identificador
     * @param value Valor en memoria
     * @param references Cantidad de referencias
     * @return
     */
    QJsonDocument writeRAMdata(int dir , std::string name, std::string value, int references);
};


#endif //C_IDE_JSONPARSER_H
