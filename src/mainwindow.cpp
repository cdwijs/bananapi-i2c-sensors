#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "integrator.h"

integrator myIntegrator;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myIntegrator.initialize();



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{ //stand-in for when the timer fires
    myIntegrator.update();
}
