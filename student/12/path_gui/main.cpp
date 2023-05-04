/* Path_GUI - main.cpp
 * The file instructs a Path game for the user, in which the user moves all the
 * objects from one side to the other within a special path.
 *
 * Program author
 * Name: Vu Dinh Thi (Thi Vu)
 * Student number: 151394898
 * UserID: tpthvu
 * E-Mail: thi.vu@tuni.fi
 *
 * Notes about the program and it's implementation (if any): None
 *
 * */
#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
