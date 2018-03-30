//
// Created by Roger Valderrama on 3/29/18.
//

#include "NetServer.hpp"

NetServer::NetServer() {
    adapter = new NetSocket(serverAddress, serverPort);
    adapter->setOnReceive(&receive);
}

bool NetServer::send(QJsonDocument *data) {
    if (data->isObject()) {
        QByteArray message = data->toBinaryData();
        adapter->send(message);
        return true;
    } else {
        return false;
    }
}

NetServer *NetServer::getServerConnection() {
    static NetServer *serverConnection;
    if (serverConnection == nullptr) {
        serverConnection = new NetServer();
    }
    return serverConnection;
}

bool NetServer::receive(QByteArray data) {
    QJsonDocument receivedData = QJsonDocument::fromBinaryData(data);
    if (receivedData.isObject()) {
        NetServer::getServerConnection()->incomingData = receivedData;
        return true;
    } else {
        return false;
    }
}

void NetServer::setServerAddress(QString address, quint64 port) {
    this->serverAddress = address;
    this->serverPort = port;
}