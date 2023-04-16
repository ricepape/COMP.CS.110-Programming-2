#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <iostream>
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_fileLineEdit_returnPressed();

    void on_keyLineEdit_returnPressed();

    void on_findPushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HH
