/* Class: MainWindow
 * -----------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -----------------
 * Class representing a main window of the graphical user interfaces for the path game
 *
 * Program author
 * Name: Vu Dinh Thi (Thi Vu)
 * Student number: 151394898
 * UserID: tpthvu
 * E-Mail: thi.vu@tuni.fi
 *
 * Notes about the program and it's implementation (if any): None
 *
 *
 * */
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


    /**
     * @brief control_game: enable or disable the game buttons
     * @parameter enable, bool: true if the buttons need to be enabled, false if the
     * buttons need to be disabled.
     */
    void control_game(bool enable);

    /**
     * @brief handle_start_clicks(): Handling the functioning of the program when the
     * player wants to start playing, including enable the game buttons, start the
     * timer and start counting the moves
     */
    void handle_start_clicks();

    /**
     * @brief handle_instruction_clicks(): Displaying the instructions of the
     * game to the player from the text Browser section.
     */
    void handle_instruction_clicks();

    /**
     * @brief handle_close_clicks(): Handling the closing of the program.
     */
    void handle_close_clicks();

    /**
     * @brief handle_reset_clicks(): Reseting all components of the game to
     * initial stage before starting the game.
     */
    void handle_reset_clicks();

    /**
     * @brief check_if_the_player_wins(): heck if all the buttons have been
     * arranged correctly to win according to the rules. Also different
     * scenarios for winning is applied based on the number of moves the player used.
     */
    void check_if_the_player_wins();

    /**
     * @brief set_geometry_game_buttons(): assign the game button to a specific coordinate
     * with given constants.
     * @parameter button, QPushButton* : the button that needs to set up
     * @parameter x_coordinate, y_coordinate, int: the coordinates that will be put in for
     * setting the geometry, according to the position of the button in the vector.
     **/
    void set_geometry_game_buttons(QPushButton* button, int x_coordinate, int y_coordinate);


    /**
     * @brief handle_button_clicks(): handling the process of the game button,
     * including the validity of the chosen button, the movement of the button.
     **/
    void handle_button_clicks();

    /**
     * @brief handle_pause_resume_clicks(): Handling the pausation and the resumation of
     * the game while playing
     **/
    void handle_pause_resume_clicks();



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

    //push button for the necessary commands on the game
    QPushButton* startButton;
    QPushButton* resetButton;
    QPushButton* instructionButton;
    QPushButton* pause_resumeButton;
    //text browser for informing
    QTextBrowser* text_browser_;
    QLabel* moves_made_Label_;
    QWidget* central;
    QLCDNumber* lcdNumberSec;
    QTimer* timer;

    //a flag denote if the game is needed to be paused or not
    bool pause=true;

    /**
     * @brief init_gridboard(): implementing the gridboard for the game
     * on the GUI.
     */
    void init_gridboard();

    /**
     * @brief on_lcdNumberSec_overflow(): manage the time display
     * when the signal is overflown
     */
    void on_lcdNumberSec_overflow();

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
     * @brief init_lcdNumberSec(): implement the QLCD number for the time display
     * on the GUI.
     */
    void init_lcdNumberSec();

    /**
     * @brief init_timeLabel(): implement the label "Time: " on the window
     */
    void init_timeLabel();

    /**
     * @brief init_secondsLabel(): implement the label "seconds" on the window
     */
    void init_secondsLabel();

    /**
     * @brief init_secondsLabel(): implement the label "Moves: " on the window
     */
    void init_movesLabel();

    /**
     * @brief init_moves_madeLabel(): implement the label displaying the number of moves
     * the player has used on the window
     */
    void init_moves_madeLabel();

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
