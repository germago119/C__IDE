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
    /**
    * @brief Constructor of the GUI.
    */
    MainWindow();

    /**
    * @brief Destructor of MainWindow.
     */
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

    QPushButton *printBtn;

    QPushButton *clearBtn;

    Highlighter *highlighter;

    QStandardItemModel *model;

    /**
    * @brief Updates the QTextBrowser for the GUI log.
    */
    void updateAppLog();

    /**
    * @brief Sets model for the RAMView.
    */
    void setModel();

    //Botón para ejecutar por pasos
    QPushButton *stepBtn;
    QPushButton *stopBtn;
    JSONparser *jsonParser;


    //SERVER STUFF

    QLocalSocket *socket;
    LocalServer *server;

    /**
    * @brief Send a QString msg through a socket.
    */
    void client_send(const QString &msg);

    /**
    * @brief Send a Json msg through a socket.
    */
    void client_send(const QJsonDocument &msg);

    /**
    * @brief Read what the server send through a socket.
     */
    void client_read();

    /**
    * @brief Starts and sets up the server.
    */
    void startServer();

    /**
    * @brief Update the QTableView as it parsers the code.
    */
    void updateLiveRAMView(QJsonObject &message);

    int currentLine;


private slots:

    /**
    * @brief Controller for the Run Button.
    */
    void runBtnHandler();

    /**
    * @brief Controller for the Clear Button.
    */
    void clearBtnHandler();

    /**
    * @brief Controller for the Stop Button.
     */
    void stopBtnHandler();

    /**
     * @brief Controller for the Step Button.
     */
    void stepBtnHandler();

    /**
     * @brief Call parseCode method so it can parse code from CodeEditor.
     */
    QJsonDocument useParser();

    void usePrinter();

};


#endif //C_IDE_MAINWINDOW_HPP