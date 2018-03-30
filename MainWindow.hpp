//
// Created by Roger Valderrama on 3/29/18.
//

#ifndef C_IDE_MAINWINDOW_HPP
#define C_IDE_MAINWINDOW_HPP


#include <QMainWindow>
#include <QtWidgets>
#include <QDebug>
#include <QLocalSocket>
#include "Server/LocalServer.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void startServer();
    QLocalSocket *socket;
    LocalServer *server;
    void client_send(const QString &msg);
    void client_read();
    void server_send(const QString &msg);
    void server_read();

private slots:

    void on_runBtn_clicked();

};


#endif //C_IDE_MAINWINDOW_HPP