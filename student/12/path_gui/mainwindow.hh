#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QPushButton>
#include <QTimer>
#include <QLCDNumber>
#include <QTextBrowser>
#include <QLabel>
#include <gameboard.hh>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    Ui::MainWindow *ui;

    std::vector<std::vector<QPushButton*>> buttons;
    std::vector<std::vector<QPushButton*>> copy_buttons;

    //counting the clicks of the player
    int clicks=0;

    //GameBoard used in the game
    GameBoard board_used;

    //the point for the initial and destination button
    Point button_to_be_moved;
    Point where_to_move;

    QPushButton* startButton;
    QPushButton* resetButton;
    QPushButton* instructionButton;
    QPushButton* pause_resumeButton;
    QTextBrowser* text_browser_;

    bool pause=true;

    /**
     * @brief init_start(): implement the Start button on the GUI.
     */
    void init_start();

    /**
     * @brief init_reset(): implement the Reset button on the GUI.
     */
    void init_reset();

    /**
     * @brief init_instruction(): implement the Instruction button on the GUI.
     */
    void init_instruction();

    /**
     * @brief init_close(): implement the Close button on the GUI.
     */
    void init_close();

    /**
     * @brief init_textBrowser(): implement the text browser section on the GUI
     * for later informations to the player.
     */
    void init_textBrowser();

    /**
     * @brief init_pause_resume(): implement the Pause/Resume button on the GUI.
     */
    void init_pause_resume();


    // Space between elements, both horizontally and vertically
    const int MARGIN = 20;

    // Constants for push buttons
    const int NARROW_BUTTON_WIDTH = 20;
    const int DEFAULT_BUTTON_HEIGTH = 30;

    // Errors string of movement.
    QString INVALID_POINT = "Invalid start/destination point.";
    QString BUTTON_MISSING = "Button missing in start point.";
    QString NOT_EMPTY = "Destination point is not empty.";
    QString IDENTICAL_POINTS = "Given points are the same.";   // Actually useless
    QString CANNOT_MOVE = "There is no path between start point and destination point.";
};
#endif // MAINWINDOW_HH
