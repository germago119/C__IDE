//
// Created by Roger Valderrama on 3/29/18.
//

#ifndef C_IDE_NETSERVER_HPP
#define C_IDE_NETSERVER_HPP

#include <QJsonDocument>
#include "NetSocket.hpp"

class NetServer {

private:
    NetSocket *adapter;
    QJsonDocument incomingData;
    QString serverAddress = "localhost";
    quint64 serverPort = 8080;

    NetServer();


public:
    static NetServer *getServerConnection();

    bool send(QJsonDocument *data);

    bool static receive(QByteArray data);

    void setServerAddress(QString address, quint64 port);
};


#endif //C_IDE_NETSERVER_HPP
