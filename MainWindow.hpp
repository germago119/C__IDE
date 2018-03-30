//
// Created by Roger Valderrama on 3/29/18.
//

#ifndef C_IDE_MAINWINDOW_HPP
#define C_IDE_MAINWINDOW_HPP


#include <QtWidgets>
#include "Server/LocalServer.h"

class MainWindow : public QMainWindow {

public:

    MainWindow();

private:
    LocalServer *server;
    QLocalSocket *socket;

private slots:

    QWidget *centralWidget;

    QVBoxLayout *vLayout;

    QPlainTextEdit *editor;

    QLabel *stdOut;

    QLabel *applicationLog;

    QTableView *tableView;

    QToolBar *toolbar;

    QPushButton *connectBtn;

    int const windowWidth = 800;

    int const windowHeight = 600;
    void connectToServer();

};


#endif //C_IDE_MAINWINDOW_HPP