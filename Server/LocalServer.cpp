//
// Created by karina on 29/03/18.
//

#include "LocalServer.h"
#include "Server/loguru.hpp"

LocalServer::LocalServer(QObject *parent) : QLocalServer(parent)
{
    clientSocket = nullptr;
    connect(this, &LocalServer::newConnection, [&](){
        clientSocket = nextPendingConnection();
        connect(clientSocket, &QLocalSocket::readyRead, [&](){
            LOG_F(INFO, "Local server signal connected to socket");
            read();
        });
    });
}

void LocalServer::send(const QString &msg)
{
    if(clientSocket){
        QTextStream T(clientSocket);
        T << msg;
        clientSocket->flush();
    }
    else{
        LOG_F(INFO, "Send failed. No client connected");
        std::cout << "Nadie conectado" << std::endl;
    }
}

void LocalServer::read(){
    std::cout << "Entering message received" << std::endl;
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

        QString message;
        in >> message;
        std::cout << "Just received: " << message.toStdString() << std::endl;
        LOG_F(INFO, "Message received.");
    }

    LOG_F(INFO, "No message to read.");
    std::cout << "Nothing to read" << std::endl;
}

QLocalSocket* LocalServer::getSocket(){
    return clientSocket;
}


