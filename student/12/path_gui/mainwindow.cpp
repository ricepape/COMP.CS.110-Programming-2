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
