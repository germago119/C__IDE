//
// Created by Roger Valderrama on 3/29/18.
//

#include <AST/CodeParser.hpp>
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
    ramview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    centralWidget = new QWidget();
    auto *applogWidget = new QWidget();

    //QBoxes
    vLayout = new QVBoxLayout();
    titlehLayout = new QHBoxLayout();
    apploghLayout = new QHBoxLayout();
    auto *applogVLayout = new QVBoxLayout();

    //Labels
    applicationLog = new QTextBrowser();
    stdOut = new QTextBrowser();
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

    stepBtn->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

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

    updateAppLog();

    codeEditor->setPlainText("int a = 1;\n struct {int b = 0;\n };\nint c = 9;\n char d = 8;");

    //Server Stuff
    server = new LocalServer(this);
    socket = new QLocalSocket(this);
    currentLine = 0;

    jsonParser = new JSONparser();

    //ramview settings
    setModel();
    ramview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow() {
    server->removeServer("mserver");
    delete jsonParser;
    delete model;
    delete server;
    delete socket;
    delete codeEditor;
}

//METODO DEL BOTON RUN
void MainWindow::runBtnHandler() {
    if (!server->isListening()) {
        startServer();
        bool ok;
        int i = QInputDialog::getInt(this, tr("Set total memory"),
                                     tr("Enter total memory"), 1024, 1, 10240, 1, &ok);
        if (ok && i != 0) {
            client_send(jsonParser->writeMallocRequest(i));
        }
        if(!ok || i== 0) {
            stopBtnHandler();
            QMessageBox::information(nullptr, "Error", "Total malloc necessary to start execution");
        }
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
        client_send(useParser());
        //client_send(jsonParser->writeRAMDataRequest());
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
    QDataStream T(socket);

    QByteArray buffer;
    auto length = (int) socket->bytesAvailable();
    char temp[length];
    if(T.readRawData(temp, length) == -1)
        LOG_F(INFO, "Failed to read data from stream");
    buffer.append(temp, length);

    QJsonDocument receivedData = QJsonDocument::fromJson(buffer.remove(0, 4));
    QString jsonString = receivedData.toJson(QJsonDocument::Compact);
    QJsonObject json = receivedData.object();

    if(json["Subject"] == "RAM"){
        updateLiveRAMView(json);
    }

    const char* logMsg = jsonString.toUtf8().constData();
    LOG_F(INFO, logMsg);
    updateAppLog();
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

void MainWindow::client_send(const QJsonDocument &msg) {
//send a message to the server
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);
    // client writes a QString
    out << msg.toJson(QJsonDocument::Compact);
    out.device()->seek(0);
    socket->write(block);
    socket->flush();
}


void MainWindow::updateAppLog() {
    QFile file("C_IDE_log.log");
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(nullptr, "info", file.errorString());
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
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Name")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Value")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("References")));
    ramview->setModel(model);
}

void MainWindow::updateLiveRAMView(QJsonObject &json) {
    setModel();
    QJsonDocument doc(json);
    QJsonArray contents = json["Contents"].toArray();
    for(int i = 0; i < contents.size(); ++i) {
        QJsonDocument d(contents[i].toObject());
        std::cout << d.toJson(QJsonDocument::Compact).toStdString() << std::endl;
        QList<QStandardItem *> column;

        QStandardItem *direction =
                new QStandardItem(contents[i].toObject().value("Direction").toString());
        column.append(direction);

        QStandardItem *name =
                new QStandardItem(contents[i].toObject().value("Name").toString("no name"));
        column.append(name);

        QVariant val = contents[i].toObject().value("Value").toVariant();
        QString s = QString::fromStdString(val.toString().toStdString());
        QStandardItem* value =
                new QStandardItem(s);
        column.append(value);

        int ref = contents[i].toObject().value("References").toInt(0);
        QString ss = QString::fromStdString(std::to_string(ref));
        QStandardItem *references =
                new QStandardItem(ss);
        column.append(references);
        model->appendRow(column);
    }
}

QJsonDocument MainWindow::useParser() {
    updateAppLog();
    parseCode(codeEditor->toPlainText().toStdString());
    return getJSON();
};
