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
}

MainWindow::~MainWindow() {
    delete ui;
}

//METODO DEL BOTON RUN
void MainWindow::on_runBtn_clicked() {

    qDebug() << "IT RUNS";

}