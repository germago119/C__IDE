//
// Created by karina on 29/03/18.
//

#include <QtCore/QJsonDocument>
#include "LocalServer.h"
#include "Server/loguru.hpp"

LocalServer::LocalServer(QObject *parent) : QLocalServer(parent)
{
    clientSocket = nullptr;
    connect(this, &LocalServer::newConnection, [&](){
        clientSocket = nextPendingConnection();
        connect(clientSocket, &QLocalSocket::readyRead, [&](){
            read();
        });
        LOG_F(INFO, "Local server signal connected to socket");
    });
}

void LocalServer::send(const QString &msg)
{
    if(clientSocket){
        QTextStream T(clientSocket);
        T << msg;
        clientSocket->flush();
        LOG_F(INFO, "Message sent to client");
    }
    else{
        LOG_F(INFO, "Send failed. No client connected");
    }
}

void LocalServer::send(const QJsonDocument &msg)
{
    if(clientSocket){
        //send a message to the server
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_7);
        // client writes a QString
        out << msg.toJson(QJsonDocument::Compact);
        out.device()->seek(0);
        clientSocket->write(block);
        clientSocket->flush();
        LOG_F(INFO, "Message sent to client");
    }
    else{
        LOG_F(INFO, "Send failed. No client connected");
    }
}

void LocalServer::read(){
    LOG_F(INFO, "Reading incoming message.");
    if(clientSocket->bytesAvailable() > 0){
        while (clientSocket->bytesAvailable() < (int)sizeof(quint32))
            clientSocket->waitForReadyRead();

        connect(clientSocket, SIGNAL(disconnected()),
                clientSocket, SLOT(deleteLater()));

        QDataStream in(clientSocket);
        in.setVersion(QDataStream::Qt_4_7);
        if (clientSocket->bytesAvailable() < (int)sizeof(quint16)) {
            return;
        }

        QByteArray buffer;
        auto length = (int)clientSocket->bytesAvailable();
        char temp [length];
        int test = in.readRawData (temp, length);
        buffer.append (temp, length);

        QJsonDocument receivedData = QJsonDocument::fromJson(buffer.remove(0,4));
        QString jsonString = receivedData.toJson(QJsonDocument::Compact);
        std::cout << "Qstring from json: " << jsonString.toStdString() << std::endl;
        const char* logMsg = jsonString.toStdString().c_str();
        LOG_F(INFO, logMsg);
        send(parser->writeRAMdata(10, "hfr", "h", 10));
        /*QString message;
        in >> message;
        message.insert(0, "Message received: ");
        const char* logMsg = message.toStdString().c_str();
        std::cout << message.toStdString() << std::endl;
        LOG_F(INFO, logMsg);
        send(message);*/
    }
    else
        LOG_F(INFO, "No message to read.");
}
