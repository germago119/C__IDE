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
        //Crea un json desde los datos recibidos y elimina los primero 4 bytes
        QJsonDocument receivedData = QJsonDocument::fromJson(buffer.remove(0,4));
        QString jsonString = receivedData.toJson(QJsonDocument::Compact);
        std::cout << "Qstring from json: " << jsonString.toStdString() << std::endl;
        const char* logMsg = jsonString.toUtf8().constData();
        LOG_F(INFO, "%s", logMsg);


        QJsonObject json = receivedData.object();
        QJsonArray array = json["Contents"].toArray();
        if(json["Subject"] == "Total_Malloc")
            memoryAllocation(array[0].toObject().value("Value").toInt());
        send(parser->writeRAMdata(1000, "Saludo", "Hola", 2));
    }
    else
        LOG_F(INFO, "No message to read.");
}

void LocalServer::memoryAllocation(int total) {
    //Buscar error
    memoryBlock = (int*)malloc(sizeof(int)*total);
    size_t size = malloc_usable_size(memoryBlock);
    //Elliminar después
    const char* msg = size + " bytes were allocated";
    LOG_F(INFO, msg);
    std::cout << "Malloc size: " << size << std::endl;

}


