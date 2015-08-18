#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "integrator.h"
#include <QTimer>

integrator myIntegrator;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myIntegrator.initialize();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(on_timerFires()));
    timer->start((1000));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{ //stand-in for when the timer fires
    myIntegrator.update();
}

void MainWindow::on_timerFires()
{
    myIntegrator.update();
}
