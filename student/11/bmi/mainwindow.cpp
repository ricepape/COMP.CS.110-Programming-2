#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_countButton_clicked()
{
    on_weightLineEdit_editingFinished();
}





void MainWindow::on_weightLineEdit_editingFinished()
{
    if (ui->weightLineEdit->text().isEmpty() or ui->heightLineEdit->text().isEmpty()
            or ui->heightLineEdit->text().toDouble()==0){
         ui->resultLabel->setText("Cannot count.");
         return;
    }
    double weight = ui->weightLineEdit->text().toDouble();
    double height = ui->heightLineEdit->text().toDouble()/100;
    double BMI = (weight/(height*height));
    ui->resultLabel->setText(QString::number(BMI));
    if (BMI>25){
        ui->infoTextBrowser->setText("You are overweight.");
    } else if (BMI<18.5){
        ui->infoTextBrowser->setText("You are underweight.");
    } else ui->infoTextBrowser->setText("Your weight is normal.");
}

