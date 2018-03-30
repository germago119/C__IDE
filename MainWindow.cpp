//
// Created by Roger Valderrama on 3/29/18.
//

#include "ui_mainwindow.h"
#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle("C! IDE");
    server = new LocalServer(this);
    socket = new QLocalSocket(this);
}

MainWindow::~MainWindow() {
    delete server;
    delete socket;
    delete ui;
}

//METODO DEL BOTON RUN
void MainWindow::on_runBtn_clicked() {
    startServer();
}


void MainWindow::startServer() {
    //inicia el server
    if(!server ->listen("mserver"))
    {
        //LOG_F(INFO, "Can't connect to server.");
        QMessageBox::critical(this, "Error", server->errorString());
    }else{
        //LOG_F(INFO, "Started server.");
        QMessageBox::information(this, "Server", "Servido iniciado");
        //conecta la señal readyRead del socket para mostrar el mensaje que recibe
        connect(socket, &QLocalSocket::readyRead, [&](){
            client_read();
        });
    }
}

void MainWindow::client_read() {
    QTextStream T(socket);
    QMessageBox::information(this, "Cliente", T.readAll());
}

void MainWindow::client_send(const QString &msg) {
//send a message to the server
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);
    // client writes a QString
    out << msg;
    out.device()->seek(0);
    socket->write(block);
    socket->flush();
}

void MainWindow::server_read() {
    std::cout << "Entering message received" << std::endl;
    if(socket->bytesAvailable() > 0){
        while (socket->bytesAvailable() < (int)sizeof(quint32))
            socket->waitForReadyRead();

        connect(socket, SIGNAL(disconnected()),
                socket, SLOT(deleteLater()));
        QDataStream in(socket);
        in.setVersion(QDataStream::Qt_4_7);
        if (socket->bytesAvailable() < (int)sizeof(quint16)) {
            return;
        }
        QString message;
        in >> message;
        std::cout << "Just received: " << message.toStdString() << std::endl;
    }
    std::cout << "Nothing to read" << std::endl;
}

void MainWindow::server_send(const QString &msg) {
    if(socket){
        QTextStream T(socket);
        T << msg;
        socket->flush();
    }
    else{
        std::cout << "No client connected" << std::endl;
    }
}