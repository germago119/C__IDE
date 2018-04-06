//
// Created by Roger Valderrama on 3/29/18.
//

#include "MainWindow.hpp"


MainWindow::MainWindow() {

    setWindowTitle("C! IDE");
    auto const wWidth{1200};
    auto const wHeight{750};

    //Set up CodeEditor
    codeEditor = new CodeEditor();

    //Set up Highlighter
    highlighter = new Highlighter(codeEditor->document());

    ramview = new QTableView();
    centralWidget = new QWidget();
    auto *applogWidget = new QWidget();

    //QBoxes
    vLayout = new QVBoxLayout();
    titlehLayout = new QHBoxLayout();
    apploghLayout = new QHBoxLayout();
    auto *applogVLayout = new QVBoxLayout();

    //Labels
    applicationLog = new QTextBrowser();
    stdOut = new QLabel();
    auto *apploglabel = new QLabel("Application Log");
    auto *ramlivelabel = new QLabel("RAM Live View");

    //Buttons
    runBtn = new QPushButton("RUN");
    clearBtn = new QPushButton("Clear");
    stepBtn = new QPushButton("Step");
    stopBtn = new QPushButton("Stop");
    stepBtn->setEnabled(false);
    stopBtn->setEnabled(false);

    //Connect Btns
    connect(runBtn, SIGNAL(clicked()), this, SLOT(runBtnHandler()));
    connect(clearBtn, SIGNAL(clicked()), this, SLOT(clearBtnHandler()));
    connect(stepBtn, SIGNAL(clicked()), this, SLOT(stepBtnHandler()));
    connect(stopBtn, SIGNAL(clicked()), this, SLOT(stopBtnHandler()));

    //Splitters
    auto *verticalSplitter = new QSplitter(Qt::Orientation::Vertical);
    auto *horizontalSplitter = new QSplitter(Qt::Orientation::Horizontal);

    //Spacers
    auto *logspacer = new QWidget();
    logspacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    //Set up Font for Labels
    QFont titlef("Roboto Slab", 17);
    ramlivelabel->setFont(titlef);

    QFont applogf("Roboto Slab", 14);
    apploglabel->setFont(applogf);

    //Set up Font for CodeEditor
    QFont codef("Source Code Pro", 18);
    codeEditor->setFont(codef);



    //Set sizes
    runBtn->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    ramlivelabel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    clearBtn->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    apploglabel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    stopBtn->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    ramlivelabel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    stepBtn->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    ramlivelabel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    //Delete padding in inner Layout
    applogVLayout->setMargin(0);

    //Spacing and setup for titleLayout
    titlehLayout->addSpacing(0);
    titlehLayout->addWidget(runBtn);
    titlehLayout->addWidget(stopBtn);
    titlehLayout->addWidget(stepBtn);
    titlehLayout->addSpacing(650);
    titlehLayout->addWidget(ramlivelabel);
    titlehLayout->addSpacing(180);


    //Setup for appLog Layout
    apploghLayout->addWidget(apploglabel);
    apploghLayout->addWidget(logspacer);
    apploghLayout->addWidget(clearBtn);

    applogVLayout->addLayout(apploghLayout);
    applogVLayout->addWidget(applicationLog);

    applogWidget->setLayout(applogVLayout);

    applicationLog->setStyleSheet("background-color:white;");
    stdOut->setStyleSheet("background-color:white;");

    verticalSplitter->addWidget(codeEditor);
    verticalSplitter->addWidget(stdOut);
    verticalSplitter->addWidget(applogWidget);
    horizontalSplitter->addWidget(verticalSplitter);
    horizontalSplitter->addWidget(ramview);

    vLayout->addLayout(titlehLayout);
    vLayout->addWidget(horizontalSplitter);

    QList<int> widgetWidth;
    widgetWidth << wWidth * 0.65 << wWidth * 0.35;

    QList<int> widgetHeight;
    widgetHeight << wHeight * 0.5 << wHeight * 0.25 << wHeight * 0.35;

    horizontalSplitter->setSizes(widgetWidth);
    verticalSplitter->setSizes(widgetHeight);

    centralWidget->setLayout(vLayout);

    setCentralWidget(centralWidget);

    this->resize(wWidth, wHeight);

    // codeEditor->setPlainText("//\n//  main.cpp\\n//  Test\n//\n//  Created by Roger Valderrama\n//\n#include <iostream>\nint main(int argc, const char * argv[]) {\n// insert code here...\nstd::cout << ""Hello World\n"";\nreturn 0;\n}\nint a = 5;\nlong b = 8;\n char c = 'c';\n float f = 4.0;\n double z = 2.0;\nstruct a {};\nreference<a>;\nvoid getAddr();\nvoid getValue();\nvoid print();\n\"dandelion\"");


    updateAppLog();

    //Server Stuff
    server = new LocalServer(this);
    socket = new QLocalSocket(this);
    currentLine = 0;

    setModel();
}

MainWindow::~MainWindow() {
    server->removeServer("mserver");
    delete server;
    delete socket;
    delete codeEditor;
}

//METODO DEL BOTON RUN
void MainWindow::runBtnHandler() {
    if (!server->isListening()) {
        startServer();
    }
    LOG_F(INFO, "Code execution started");
    updateAppLog();
    setModel();
    runBtn->setEnabled(false);
    stopBtn->setEnabled(true);
    stepBtn->setEnabled(true);

}

//METODO DEL BOTON CLEAR
void MainWindow::clearBtnHandler() {
    applicationLog->clear();
}

//Método del botón stop
void MainWindow::stopBtnHandler() {
    if(!runBtn->isEnabled()){
        runBtn->setEnabled(true);
        stopBtn->setEnabled(false);
        stepBtn->setEnabled(false);
        currentLine = 0;
        LOG_F(INFO, "Code execution stopped");
        updateAppLog();
    }
}

//Método del botón step
void MainWindow::stepBtnHandler() {
    QStringList lines = codeEditor->toPlainText().split('\n', QString::SkipEmptyParts);
    if (currentLine < codeEditor->document()->blockCount()) {
        client_send(lines.at(currentLine));
        updateAppLog();
        currentLine += 1;
    } else
        stopBtnHandler();
}

void MainWindow::startServer() {
    //inicia el server
    if(!server ->listen("mserver"))
    {
        LOG_F(INFO, "Can't connect to server.");
        QMessageBox::critical(this, "Error", server->errorString());
    }else{
        LOG_F(INFO, "Started server.");
        currentLine = 0;
        //conecta la señal readyRead del socket para mostrar el mensaje que recibe
        socket->connectToServer("mserver");
        connect(socket, &QLocalSocket::readyRead, [&](){
            client_read();
        });
    }
}

void MainWindow::client_read() {
    QTextStream T(socket);
    //QMessageBox::information(this, "Cliente", T.readAll());
    QStandardItem *item = new QStandardItem(QString(T.readAll()));
    model->appendRow(item);
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


void MainWindow::updateAppLog() {

    QFile file("C_IDE_log.log");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "info", file.errorString());
    }

    QTextStream stream(&file);
    stream.seek(159);

    applicationLog->setText(stream.readAll());
    applicationLog->verticalScrollBar()->setValue(applicationLog->verticalScrollBar()->maximum());

    file.close();
}

void MainWindow::setModel() {
    //Set model to ramview
    model = new QStandardItemModel(0,4,this); //0 Rows and 4 Columns
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Direction")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Value")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("References")));
    ramview->setModel(model);
}