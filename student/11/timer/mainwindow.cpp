#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lcdNumberMin->setStyleSheet("background-color:green;");
    ui->lcdNumberSec->setStyleSheet("background-color:dark_green;");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_lcdNumberSec_overflow()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    timer->start(1000);
}

void MainWindow::on_resetButton_clicked()
{
    ui->lcdNumberMin->display(0);
    ui->lcdNumberSec->display(0);
}

void MainWindow::on_stopButton_clicked()
{
    timer->stop();
}

void MainWindow::on_lcdNumberSec_overflow()
{
    int sec = ui->lcdNumberSec->intValue();
    int min = ui->lcdNumberMin->intValue();

    sec++;
    if (sec == 60) {
        sec = 0;
        min++;
        ui->lcdNumberMin->display(min);
    }
    ui->lcdNumberSec->display(sec);
}
