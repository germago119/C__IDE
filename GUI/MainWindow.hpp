//
// Created by Roger Valderrama on 3/29/18.
//

#ifndef C_IDE_MAINWINDOW_HPP
#define C_IDE_MAINWINDOW_HPP


#include <QtWidgets>
#include <QDebug>
#include <QLocalSocket>
#include <JSON/JSONparser.h>
#include "Server/LocalServer.h"
#include "Server/loguru.hpp"
#include "CodeEditor.hpp"
#include "Highlighter.hpp"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow();

    ~MainWindow() override;

private:
    CodeEditor *codeEditor;

    QWidget *centralWidget;

    QVBoxLayout *vLayout;

    QTextBrowser *stdOut;

    QTextBrowser *applicationLog;

    QTableView *ramview;

    QHBoxLayout *titlehLayout;

    QHBoxLayout *apploghLayout;

    QPushButton *runBtn;

    QPushButton *clearBtn;

    Highlighter *highlighter;

    QStandardItemModel *model;

    void updateAppLog();

    void setModel();

    //Botón para ejecutar por pasos
    QPushButton *stepBtn;
    QPushButton *stopBtn;
    JSONparser *jsonParser;


    //SERVER STUFF

    QLocalSocket *socket;
    LocalServer *server;
    void client_send(const QString &msg);
    void client_send(const QJsonDocument &msg);
    void client_read();
    int currentLine;
    void startServer();

    void updateLiveRAMView(QJsonObject &message);


private slots:

    void runBtnHandler();

    void clearBtnHandler();

    void stopBtnHandler();
    void stepBtnHandler();

private slots:

    QJsonDocument useParser();
};


#endif //C_IDE_MAINWINDOW_HPP