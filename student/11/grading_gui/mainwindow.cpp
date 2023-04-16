#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gradecalculator.hh"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBoxN->setMinimum(0);
    ui->spinBoxN->setMaximum(MAX_N_POINTS);

    ui->spinBoxG->setMinimum(0);
    ui->spinBoxG->setMaximum(MAX_G_POINTS);

    ui->spinBoxP->setMinimum(0);
    ui->spinBoxP->setMaximum(MAX_P_POINTS);

    ui->spinBoxE->setMinimum(0);
    ui->spinBoxE->setMaximum(5);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_calculatePushButton_clicked()
{
    QString text = "W-Score: ";
    text += QString::number(score_from_weekly_exercises
                           (ui->spinBoxN->text().toInt(),ui->spinBoxG->text().toInt()));
    text += "\n";
    text += "P-Score: ";
    text +=  QString::number(score_from_projects(ui->spinBoxP->text().toInt()));
    text += "\n";
    text += "Total grade: ";
    text += QString::number(calculate_total_grade(
                                ui->spinBoxN->text().toInt(),
                                ui->spinBoxG->text().toInt(),
                                ui->spinBoxP->text().toInt(),
                                ui->spinBoxE->text().toInt()));
    ui->textBrowser->setText(text);


}
