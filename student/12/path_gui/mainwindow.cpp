#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include "gameboard.hh"
#include <vector>
#include <QGridLayout>
#include <QLayout>
#include <QPushButton>
#include <QTimer>
#include <QLCDNumber>
#include <QTextBrowser>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init_gridboard();
    init_start();
    init_reset();
    init_instruction();
    init_close();
    init_textBrowser();
    init_lcdNumberSec();
    init_timeLabel();
    init_secondsLabel();
    init_movesLabel();
    init_moves_madeLabel();
    control_game(false);
    init_pause_resume();
    central->setStyleSheet("background-color:white;");
}

/**
 * @Function ~MainWindow: The destructor of the MainWindow function, deleting the ui
 * object that was created in the MainWindow constructor. The ui object is a pointer
 * to the user interface object that was created using Qt Designer, deleting memory
 * that was allocated during the lifetime of the MainWindow object, preventing any
 * memory leaks or other issues that could arise from not properly releasing memory.
 **/
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @Function init_start: setting up the Start button in the GUI
 **/
void MainWindow::init_start()
{
    startButton = new QPushButton(this);
    startButton->setText("Start");
    startButton->setGeometry(30* MARGIN + (NARROW_BUTTON_WIDTH + MARGIN),
                              4* MARGIN,
                              100,
                              DEFAULT_BUTTON_HEIGTH);
    connect(startButton, &QPushButton::clicked,
            this, &MainWindow::handle_start_clicks);
}

/**
 * @Function init_start: setting up the Reset button in the GUI
 **/
void MainWindow::init_reset()
{
    resetButton = new QPushButton(this);
    resetButton->setText("Reset");
    resetButton->setGeometry(30* MARGIN + (NARROW_BUTTON_WIDTH + MARGIN),
                              4* MARGIN + 40,
                              100,
                              DEFAULT_BUTTON_HEIGTH);
    connect(resetButton, &QPushButton::clicked,
            this, &MainWindow::handle_reset_clicks);
}

/**
 * @Function init_instruction: setting up the Instruction button in the GUI
 **/
void MainWindow::init_instruction()
{
    instructionButton = new QPushButton(this);
    instructionButton->setText("Instructions");
    instructionButton->setGeometry(30* MARGIN + (NARROW_BUTTON_WIDTH + MARGIN),
                              4* MARGIN + 120,
                              100,
                              DEFAULT_BUTTON_HEIGTH);
    connect(instructionButton, &QPushButton::clicked,
            this, &MainWindow::handle_instruction_clicks);
}

/**
 * @Function init_close: setting up the Close button in the GUI
 **/
void MainWindow::init_close()
{
    QPushButton* closeButton = new QPushButton(this);
    closeButton->setText("Close");
    closeButton->setGeometry(30* MARGIN + (NARROW_BUTTON_WIDTH + MARGIN),
                              4* MARGIN + 160,
                              100,
                              DEFAULT_BUTTON_HEIGTH);
    connect(closeButton, &QPushButton::clicked,
            this, &MainWindow::handle_close_clicks);
}

/**
 * @Function init_textBrowser: setting up the Text browser section in the GUI to inform the
 * information such as instructions, announcements, warning of the game,... to the player
 **/
void MainWindow::init_textBrowser()
{
    text_browser_ = new QTextBrowser(this);
    text_browser_->setGeometry(0,
                             400,
                              800,
                               500);
}

/**
 * @Function init_lcdNumberSec(): setting up an object of the QLCDNumber class to display
 * the elapsed time in the GUI
 **/
void MainWindow::init_lcdNumberSec()
{
    lcdNumberSec = new QLCDNumber(this);
    lcdNumberSec->setGeometry(5* MARGIN,
                              4* MARGIN,
                              100,
                              DEFAULT_BUTTON_HEIGTH);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout,
            this, &MainWindow::on_lcdNumberSec_overflow);
}

/**
 * @Function init_timeLabel(): setting up the "Time" label on the GUI to accompany with
 * the time display object.
 **/
void MainWindow::init_timeLabel()
{
    QLabel* timeLabel = new QLabel(this);
    timeLabel->setGeometry(3* MARGIN,
                              4* MARGIN,
                              100,
                              DEFAULT_BUTTON_HEIGTH);
    timeLabel->setText("Time: ");
}

/**
 * @Function init_secondsLabel: setting up the label with content "seconds" on the GUI
 * to accompany with the time display object.
 **/
void MainWindow::init_secondsLabel()
{
    QLabel* secondLabel = new QLabel(this);
    secondLabel->setGeometry(10.5* MARGIN,
                              4* MARGIN,
                              100,
                              DEFAULT_BUTTON_HEIGTH);
    secondLabel->setText("seconds");
}

/**
 * @Function init_movesLabel: setting up the label with content "Moves: " on the GUI
 * to accompany with the moves the player has used's display object.
 **/
void MainWindow::init_movesLabel()
{
    QLabel* moveLabel = new QLabel(this);
    moveLabel->setGeometry(17* MARGIN,
                              4* MARGIN,
                              100,
                              DEFAULT_BUTTON_HEIGTH);
    moveLabel->setText("Moves: ");
}


/**
 * @Function init_moves_madeLabel: setting up the label displaying the number of moves
 * the player has used on the GUI.
 **/
void MainWindow::init_moves_madeLabel()
{
    moves_made_Label_ = new QLabel(this);
    moves_made_Label_->setGeometry(22* MARGIN,
                              4* MARGIN,
                              100,
                              DEFAULT_BUTTON_HEIGTH);
    moves_made_Label_->setText(0);
}

/**
 * @Function init_pause_resume: setting up the Pause/Resume button in the GUI
 **/
void MainWindow::init_pause_resume()
{
    pause_resumeButton = new QPushButton(this);
    pause_resumeButton->setText("Pause/Resume");
    pause_resumeButton->setGeometry(30* MARGIN + (NARROW_BUTTON_WIDTH + MARGIN),
                              4* MARGIN + 80,
                              100,
                              DEFAULT_BUTTON_HEIGTH);
    pause_resumeButton->setDisabled(true);
    connect(pause_resumeButton, &QPushButton::clicked,
            this, &MainWindow::handle_pause_resume_clicks);
}

/**
 * @Function set_geometry_game_buttons(): assign the game button to a specific coordinate
 * with given constants.
 * QPushButton* button: the button that needs to set up
 * int x_coordinate, y_coordinate: the coordinates that will be put in for setting the geometry,
 * according to the position of the button in the vector.
 **/
void MainWindow::set_geometry_game_buttons(QPushButton *button,
                                           int x_coordinate, int y_coordinate)
{
    button->setGeometry(14* MARGIN + x_coordinate * (NARROW_BUTTON_WIDTH + MARGIN),
                        8* MARGIN + y_coordinate *(NARROW_BUTTON_WIDTH + MARGIN),
                        NARROW_BUTTON_WIDTH,
                        DEFAULT_BUTTON_HEIGTH);
}


/**
 * @Function init_gridboard(): implementing the initial stage of the game, including a gridboard
 * with the buttons on top and bottom and the buttons for the empty slots
 **/
void MainWindow::init_gridboard()
{
    std::vector<std::vector<Slot_type>> board = board_used.return_board_();
    // Grid layout for game buttons
    central = new QWidget(this);

    // Defining red brush and palette for buttons at top and bottom row, respectively
    QPalette redPalette;
    redPalette.setColor(QPalette::Button, Qt::red);
    QPalette greenPalette;
    greenPalette.setColor(QPalette::Button, Qt::green);

    // Setting game buttons in the grid layout and connecting all of
    // them to the same slot
    for (int row = 0; row < static_cast<int>(board.size()); ++row)
    {
        std::vector<QPushButton*> row_type;
        for (int column = 0; column < static_cast<int>(board.at(row).size()); ++column)
        {
            QPushButton* pushButton = new QPushButton(this);
            switch (board.at(row).at(column))
            {
            case RED:
                pushButton->setFixedSize(30, 30);
                pushButton->setPalette(redPalette);
                break;
            case GREEN:
                pushButton->setFixedSize(30, 30);
                pushButton->setPalette(greenPalette);
                break;
            case EMPTY:
                pushButton->setFixedSize(20, 20);
                break;
            case UNUSED:
                pushButton->setFixedSize(1, 1);
                break;
            }
            row_type.push_back(pushButton);
            set_geometry_game_buttons(pushButton,column,row);
            connect(pushButton, &QPushButton::clicked,
                    this, &MainWindow::handle_button_clicks);
        }
        buttons.push_back(row_type);
        // create a similar vector for reset game use
        copy_buttons=buttons;
    }

    setCentralWidget(central);

}
