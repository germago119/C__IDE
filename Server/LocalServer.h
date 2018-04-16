//
// Created by karina on 29/03/18.
//

/**
 * @file LocalServer.h
 * @version 1.2
 * @date 29/03/18
 * @author Karina Martínez Guerrero
 * @title Clase de servidor local
 * @brief Clase de servidor para comunicación cliente-servidor
 */

#ifndef C_IDE_LOCALSERVER_H
#define C_IDE_LOCALSERVER_H

#include "Server/loguru.hpp"
#include <QLocalServer>
#include <QLocalSocket>
#include <QTextStream>
#include <iostream>
#include <QMessageBox>
#include <JSON/JSONparser.h>
#include <QtCore/QJsonDocument>
#include <boost/lexical_cast.hpp>
#include <boost/lexical_cast.hpp>
#include <DataStructures/SimpleLinkedList.h>
#include <DataStructures/MemoryNode.h>

class QLocalSocket;
class LocalServer : public QLocalServer
{
Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param parent Objeto padre donde se llama la clase
     */
    explicit LocalServer(QObject *parent = nullptr);
    /**
     * @brief Envía un mensaje al cliente a través del QLocalSocket
     * @param msg Mensaje de tipo QString
     */
    void send(const QString &msg);
    /**
     * @brief Envía un mensaje al cliente a través del QLocalSocket
     * @param msg Mensaje de tipo QJsonDocument
     */
    void send(const QJsonDocument &msg);
    /**
     * @brief Lee los mensajes recibidos a tráves del QLocalSocket
     */
    void read();
private:
    /**
     * @brief Socket para la comunicación cliente-servidor
     */
    QLocalSocket *clientSocket;
    /**
     * @brief Parser para leer mensaje JSON
     */
    JSONparser *parser;

    void memoryAllocation(int total);

    void readMsg(QJsonObject &msg);

    QJsonDocument getRAMdata();

    char *memoryBlock = nullptr;

    SimpleLinkedList<MemoryNode> *list;

    size_t getBytesToMove();

signals:

public slots:
};

#endif //C_IDE_LOCALSERVER_H
