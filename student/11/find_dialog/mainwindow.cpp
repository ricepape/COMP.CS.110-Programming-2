#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
using namespace std;

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


void MainWindow::on_fileLineEdit_returnPressed()
{
    ifstream file;
    QString file_name_=ui->fileLineEdit->text();
    std::string str = file_name_.toStdString();
    file.open(str);
    if (file)
    {
        on_keyLineEdit_returnPressed();
    } else
    {
        ui->textBrowser->setText("File not found");
        return;
    }


}


void MainWindow::on_keyLineEdit_returnPressed()
{
    ifstream file;
    file.open(ui->fileLineEdit->text().toStdString());
    QString string_to_find_=ui->keyLineEdit->text();
    if (string_to_find_.isEmpty()){
        ui->textBrowser->setText("File found");
        return;
    }
    string str = string_to_find_.toStdString();
    bool is_found=false;
    for( std::string line; getline( file, line ); )
    {
        if (ui->matchCheckBox->isChecked()){
            std::string upper_line = line;
            transform(upper_line.begin(), upper_line.end(), upper_line.begin(), ::toupper);
            transform(str.begin(), str.end(), str.begin(), ::toupper);
            size_t found = upper_line.find(str);
            if (found!=string::npos){
                is_found = true;
            }
        } else {
            size_t found = line.find(str);
            if (found!=string::npos){
                is_found = true;
            }
        }
    }
    if (is_found){
        ui->textBrowser->setText("Word found");
    } else ui->textBrowser->setText("Word not found");
}




void MainWindow::on_findPushButton_clicked()
{
    on_fileLineEdit_returnPressed();

}

