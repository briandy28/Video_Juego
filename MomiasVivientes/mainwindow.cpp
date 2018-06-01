#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    inicio *preguntas = new inicio();
    preguntas->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
