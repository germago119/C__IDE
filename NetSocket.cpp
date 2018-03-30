//
// Created by Roger Valderrama on 3/29/18.
//

#include "NetSocket.hpp"

NetSocket::NetSocket(QString address, quint64 port) {

    this->port = port;
    this->address = address;

}

bool NetSocket::connect() {

    socket = new QTcpSocket();
    socket->connectToHost(address, port);
    socket->waitForConnected();
    if (socket->state() == QTcpSocket::ConnectedState) {
        return true;
    } else {
        return false;
    }
}

void NetSocket::received() {
    QByteArray data = "";
    data.append(socket->readAll());
    bool isComplete = this->onReceive(data);
    while (!isComplete) { //Better loop condition
        data.append(socket->readAll());
    }
}

void NetSocket::send(QByteArray data) {

    socket->write(data);

}

void NetSocket::setOnReceive(bool (*func)(QByteArray)) {
    this->onReceive = func;
}
