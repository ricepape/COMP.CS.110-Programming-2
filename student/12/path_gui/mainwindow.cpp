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
    init_textBrowser();
    init_lcdNumberSec();
    init_timeLabel();
    init_secondsLabel();
    init_movesLabel();
    init_moves_madeLabel();
    control_game(false);
}



MainWindow::~MainWindow()
{
    delete ui;
}

QLCDNumber* lcdNumberSec;
QTimer* timer;


void MainWindow::on_lcdNumberSec_overflow()
{
    int sec = lcdNumberSec->intValue();

    sec++;
    lcdNumberSec->display(sec);
}

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

void MainWindow::init_instruction()
{
    instructionButton = new QPushButton(this);
    instructionButton->setText("Instructions");
    instructionButton->setGeometry(30* MARGIN + (NARROW_BUTTON_WIDTH + MARGIN),
                              4* MARGIN + 80,
                              100,
                              DEFAULT_BUTTON_HEIGTH);
    connect(instructionButton, &QPushButton::clicked,
            this, &MainWindow::handle_instruction_clicks);
}

void MainWindow::init_textBrowser()
{
    text_browser_ = new QTextBrowser(this);
    text_browser_->setGeometry(0,
                             400,
                              800,
                               500);
}

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

void MainWindow::init_timeLabel()
{
    QLabel* timeLabel = new QLabel(this);
    timeLabel->setGeometry(3* MARGIN,
                              4* MARGIN,
                              100,
                              DEFAULT_BUTTON_HEIGTH);
    timeLabel->setText("Time: ");
}

void MainWindow::init_secondsLabel()
{
    QLabel* secondLabel = new QLabel(this);
    secondLabel->setGeometry(10.5* MARGIN,
                              4* MARGIN,
                              100,
                              DEFAULT_BUTTON_HEIGTH);
    secondLabel->setText("seconds");
}

void MainWindow::init_movesLabel()
{
    QLabel* moveLabel = new QLabel(this);
    moveLabel->setGeometry(17* MARGIN,
                              4* MARGIN,
                              100,
                              DEFAULT_BUTTON_HEIGTH);
    moveLabel->setText("Moves: ");
}

void MainWindow::init_moves_madeLabel()
{
    moves_made_Label_ = new QLabel(this);
    moves_made_Label_->setGeometry(22* MARGIN,
                              4* MARGIN,
                              100,
                              DEFAULT_BUTTON_HEIGTH);
    moves_made_Label_->setText(0);
}

void MainWindow::control_game(bool enable)
{
    for (int row = 0; row < static_cast<int>(buttons.size()); ++row)
    {
        for (int column = 0; column < static_cast<int>(buttons.at(row).size()); ++column)
        {
            buttons.at(row).at(column)->setEnabled(enable);
        }
    }
}

void MainWindow::handle_start_clicks()
{
    timer->start(1000);
    control_game(true);

}


void MainWindow::handle_instruction_clicks()
{
    QString text = "The purpose is to move buttons ";
        text += "such that finally they are in opposite places than at the beginning. ";
        text += "For example, the green ones are at the top and the red ones at the bottom, ";
        text += "the aim is to reach the situation where green buttons are at the bottom ";
        text += "and the red ones at the top.\n";
        text += "You can move the buttons by clicking at the button and clicking at the position ";
        text += "where you want your button is moved to. ";
        text += "It is not allowed to move a button over another one, but the moves are made along ";
        text += "a path of empty places. A move can be as long as there is such kind of path.\n";
        text += "It is possible to reach this final situation with 31 moves, in minimum.";
        text_browser_->setText(text);
}

void MainWindow::handle_reset_clicks()
{
    for (int row = 0; row < static_cast<int>(copy_buttons.size()); ++row)
    {
        for (int column = 0; column < static_cast<int>(copy_buttons.at(row).size()); ++column)
        {
            for (int check_row = 0; check_row < static_cast<int>(buttons.size()); ++check_row)
            {
                for (int check_column = 0; check_column < static_cast<int>(buttons.at(check_row).size()); ++check_column)
                {
                    if (copy_buttons.at(row).at(column)==buttons.at(check_row).at(check_column))
                    {
                        buttons.at(check_row).at(check_column)->setGeometry(
                                    14* MARGIN + column * (NARROW_BUTTON_WIDTH + MARGIN),
                                    8* MARGIN + row *(NARROW_BUTTON_WIDTH + MARGIN),
                                    NARROW_BUTTON_WIDTH,
                                    DEFAULT_BUTTON_HEIGTH);
                        buttons.at(row).at(column)->setGeometry(
                                    14* MARGIN + check_column * (NARROW_BUTTON_WIDTH + MARGIN),
                                    8* MARGIN + check_row *(NARROW_BUTTON_WIDTH + MARGIN),
                                    NARROW_BUTTON_WIDTH,
                                    DEFAULT_BUTTON_HEIGTH);
                        QPushButton* temp=buttons.at(row).at(column);
                        buttons.at(row).at(column)=
                                 buttons.at(check_row).at(check_column);
                        buttons.at(check_row).at(check_column)=temp;
                    }
                }
            }
        }
    }
    buttons=copy_buttons;
    GameBoard new_board;
    board_used=new_board;
    lcdNumberSec->display(0);
    timer->stop();
    moves_made_Label_->setText(0);
    clicks=0;
    control_game(false);
    text_browser_->setText("The game is now reseted. Please press Start to play.");



}



void MainWindow::init_gridboard()
{
    std::vector<std::vector<Slot_type>> board = board_used.return_board_();
    // Grid layout for letter buttons
    central = new QWidget(this);

    // Defining red brush and palette for letters
    QPalette redPalette;
    redPalette.setColor(QPalette::Button, Qt::red);
    QPalette greenPalette;
    greenPalette.setColor(QPalette::Button, Qt::green);

    // Setting letter buttons in the grid layout and connecting all of
    // them to the same slot (no coordinates needed)
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
                pushButton->setFixedSize(15, 15);
                break;
            case UNUSED:
                pushButton->setFixedSize(1, 1);
                break;
            }
            row_type.push_back(pushButton);
            pushButton->setGeometry(14* MARGIN + column * (NARROW_BUTTON_WIDTH + MARGIN),
                                    8* MARGIN + row *(NARROW_BUTTON_WIDTH + MARGIN),
                                    NARROW_BUTTON_WIDTH,
                                    DEFAULT_BUTTON_HEIGTH);
            connect(pushButton, &QPushButton::clicked,
                    this, &MainWindow::handle_button_clicks);
        }
        buttons.push_back(row_type);
        copy_buttons=buttons;
    }

    setCentralWidget(central);

}

void MainWindow::handle_button_clicks()
{
    clicks+=1;
    std::vector<std::vector<Slot_type>> check_point = board_used.return_board_();
    for (int row = 0; row < static_cast<int>(buttons.size()); ++row)
    {
        for (int column = 0; column < static_cast<int>(buttons.at(row).size()); ++column)
        {
            if (buttons.at(row).at(column) == sender()){
                text_browser_->setText("");
                if (clicks % 2!=0){
                    if(check_point.at(row).at(column)!=GREEN and check_point.at(row).at(column)!=RED){
                        QString text=INVALID_POINT+"\n"+BUTTON_MISSING;
                        text_browser_->setText(text);
                        clicks-=1;
                        break;
                    }
                    button_to_be_moved.y=row;
                    button_to_be_moved.x=column;
                } else {
                    where_to_move.y=row;
                    where_to_move.x=column;
                    if (board_used.move(button_to_be_moved, where_to_move)){
                        buttons.at(button_to_be_moved.y).at(button_to_be_moved.x)->setGeometry(
                                    14* MARGIN + where_to_move.x * (NARROW_BUTTON_WIDTH + MARGIN),
                                    8* MARGIN + where_to_move.y *(NARROW_BUTTON_WIDTH + MARGIN),
                                    NARROW_BUTTON_WIDTH,
                                    DEFAULT_BUTTON_HEIGTH);
                        buttons.at(where_to_move.y).at(where_to_move.x)->setGeometry(
                                    14* MARGIN + button_to_be_moved.x * (NARROW_BUTTON_WIDTH + MARGIN),
                                    8* MARGIN + button_to_be_moved.y *(NARROW_BUTTON_WIDTH + MARGIN),
                                    NARROW_BUTTON_WIDTH,
                                    DEFAULT_BUTTON_HEIGTH);
                        QPushButton* temp=buttons.at(button_to_be_moved.y).at(button_to_be_moved.x);
                        buttons.at(button_to_be_moved.y).at(button_to_be_moved.x)=
                                 buttons.at(where_to_move.y).at(where_to_move.x);
                        buttons.at(where_to_move.y).at(where_to_move.x)=temp;
                    }
                    else {
                        if(check_point.at(row).at(column)==GREEN or check_point.at(row).at(column)==RED){
                            QString text=INVALID_POINT+"\n"+NOT_EMPTY;
                            text_browser_->setText(text);
                        }
                        else if(check_point.at(row).at(column)==check_point.at(button_to_be_moved.y).at(button_to_be_moved.x)){
                            text_browser_->setText(IDENTICAL_POINTS);
                        } else {
                        text_browser_->setText(CANNOT_MOVE);
                        }
                        clicks-=2;
                    }
                }
            }
        }
    }
    int moves_made=(clicks-(clicks%2))/2;
    moves_made_Label_->setText(QString::number(moves_made));
}

