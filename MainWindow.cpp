//
// Created by Roger Valderrama on 3/29/18.
//

#include "MainWindow.hpp"


MainWindow::MainWindow() {

    setWindowTitle("C! IDE");
    auto const wWidth{1000};
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
    applicationLog = new QLabel();
    stdOut = new QLabel();
    auto *apploglabel = new QLabel("Application Log");
    auto *ramlivelabel = new QLabel("RAM Live View");

    //Buttons
    runBtn = new QPushButton("RUN");
    clearBtn = new QPushButton("Clear");

    //Connect Btns
    connect(runBtn, SIGNAL(clicked()), this, SLOT(runBtnHandler()));
    connect(clearBtn, SIGNAL(clicked()), this, SLOT(clearBtnHnadler()));

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
    QFont codef("Source Code Pro", 12);
    codeEditor->setFont(codef);



    //Set sizes
    runBtn->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    ramlivelabel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    clearBtn->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    apploglabel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));


    //Delete padding in inner Layout
    applogVLayout->setMargin(0);

    //Spacing and setup for titleLayout
    titlehLayout->addSpacing(0);
    titlehLayout->addWidget(runBtn);
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
    widgetWidth << wWidth * 0.7 << wWidth * 0.3;

    QList<int> widgetHeight;
    widgetHeight << wHeight * 0.5 << wHeight * 0.25 << wHeight * 0.35;

    horizontalSplitter->setSizes(widgetWidth);
    verticalSplitter->setSizes(widgetHeight);

    centralWidget->setLayout(vLayout);

    setCentralWidget(centralWidget);

    this->resize(wWidth, wHeight);

/*
    codeEditor->setPlainText("hello\n"
                             "hi\n"
                             "hola\n"
                             "hhh");

    QStringList lines = codeEditor->toPlainText()
            .split('\n', QString::SkipEmptyParts);
    if (lines.count() > 3)
        qDebug() << "fourth line:" << lines.at(3);

*/


    //Server Stuff
    server = new LocalServer(this);
    socket = new QLocalSocket(this);
    currentLine = 0;
}

MainWindow::~MainWindow() {
    server->removeServer("mserver");
    delete server;
    delete socket;
    delete codeEditor;
}

//METODO DEL BOTON RUN
void MainWindow::runBtnHandler() {
    qDebug() << "IT RUN";
    startServer();
}

void MainWindow::clearBtnHnadler() {
    qDebug() << "IT WILL CLEAR";
    startDebug();
}

void MainWindow::startDebug() {
    QStringList lines = codeEditor->toPlainText().split('\n', QString::SkipEmptyParts);
    //if(currentLine != ) {
        client_send(lines.at(currentLine));
        currentLine += 1;
    //}
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
        //QMessageBox::information(this, "Server", "Servido iniciado");
        //conecta la señal readyRead del socket para mostrar el mensaje que recibe
        socket->connectToServer("mserver");
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
    server->send(msg);
    /*if(socket){
        QTextStream T(socket);
        T << msg;
        socket->flush();
    }
    else{
        std::cout << "No client connected" << std::endl;
    }*/
}

QString MainWindow::getLine(int lineNum) {
    QStringList lines = codeEditor->toPlainText().split('\n', QString::SkipEmptyParts);
    return lines.at(lineNum);
}