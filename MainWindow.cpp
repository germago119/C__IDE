//
// Created by Roger Valderrama on 3/29/18.
//

#include "MainWindow.hpp"

MainWindow::MainWindow() {
    tableView = new QTableView();
    centralWidget = new QWidget();
    vLayout = new QVBoxLayout();
    applicationLog = new QLabel();
    stdOut = new QLabel();
    editor = new QPlainTextEdit();
    toolbar = new QToolBar();
    connectBtn = new QPushButton();

    connectBtn->setText("Connect");

    QSplitter *verticalSplitter = new QSplitter(Qt::Orientation::Vertical);
    QSplitter *horizontalSplitter = new QSplitter(Qt::Orientation::Horizontal);

    applicationLog->setStyleSheet("background-color:white;");
    stdOut->setStyleSheet("background-color:white;");

    verticalSplitter->addWidget(connectBtn);
    verticalSplitter->addWidget(editor);
    verticalSplitter->addWidget(stdOut);
    verticalSplitter->addWidget(applicationLog);
    horizontalSplitter->addWidget(verticalSplitter);
    horizontalSplitter->addWidget(tableView);

    vLayout->addWidget(horizontalSplitter);

    QList<int> widgetWidth;
    widgetWidth << windowWidth * 0.7 << windowWidth * 0.3;

    QList<int> widgetHeight;
    widgetHeight << windowHeight * 0.5 << windowHeight * 0.25 << windowHeight * 0.25;

    horizontalSplitter->setSizes(widgetWidth);
    verticalSplitter->setSizes(widgetHeight);

    centralWidget->setLayout(vLayout);

    setCentralWidget(centralWidget);

    this->addToolBar(toolbar);
    this->resize(windowWidth, windowHeight);

};