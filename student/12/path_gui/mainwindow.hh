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

    void init_gridboard();
    void handle_button_clicks();
    void on_lcdNumberSec_overflow();
    void init_start();
    void init_reset();
    void init_instruction();
    void init_textBrowser();
    void init_lcdNumberSec();
    void init_timeLabel();
    void init_secondsLabel();
    void init_movesLabel();
    void init_moves_madeLabel();
    void control_game(bool enable);
    void handle_start_clicks();
    void handle_instruction_clicks();
    void handle_reset_clicks();
    void init_game();

private:
    Ui::MainWindow *ui;

    std::vector<std::vector<QPushButton*>> buttons;
    std::vector<std::vector<QPushButton*>> copy_buttons;


    int clicks=0;

    GameBoard board_used;

    Point button_to_be_moved;
    Point where_to_move;

    QPushButton* startButton;
    QPushButton* resetButton;
    QPushButton* instructionButton;
    QTextBrowser* text_browser_;
    QLabel* moves_made_Label_;
    QWidget* central;

    // Space between elements, both horizontally and vertically
    const int MARGIN = 20;

    // Constants for push buttons
    const int NARROW_BUTTON_WIDTH = 20;
    const int DEFAULT_BUTTON_HEIGTH = 30;

    // Size of the text browser
    const int DISPLAY_WIDTH = 200;
    const int DISPLAY_HEIGTH = 30;

    // Location of the graphics view and scene
    const int VIEW_X = 20;
    const int VIEW_Y = 350;

    QString INVALID_POINT = "Invalid start/destination point.";
    QString BUTTON_MISSING = "Button missing in start point.";
    QString NOT_EMPTY = "Destination point is not empty.";
    QString IDENTICAL_POINTS = "Given points are the same.";   // Actually useless
    QString CANNOT_MOVE = "There is no path between start point and destination point.";
    QString GAME_OVER = "Game over. Congratulations!";
    QString MOVES_MADE = " move(s) made.";
};
#endif // MAINWINDOW_HH
