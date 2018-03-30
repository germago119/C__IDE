//
// Created by Roger Valderrama on 3/29/18.
//

#ifndef C_IDE_NETSOCKET_HPP
#define C_IDE_NETSOCKET_HPP

#include <QTcpSocket>

class NetSocket {

private:

    QString address;
    qint64 port;

    QTcpSocket *socket = nullptr;

    bool (*onReceive)(QByteArray);

public:

    bool connect();

    void send(QByteArray);

    NetSocket(QString address, quint64 port);

    void setOnReceive(bool (*func)(QByteArray));

public slots:

    void received();

};


#endif //C_IDE_NETSOCKET_HPP
