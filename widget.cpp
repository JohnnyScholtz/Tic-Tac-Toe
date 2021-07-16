#include "widget.h"
#include "tictactoe.h"
#include <QSpinBox>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    setGeometry(500, 50, 500, 400);

    sizeOfGameLabel = new QLabel(this);
    sizeOfGameLabel->setText("Enter the size of the Tic-Tac-Toe game:");
    sizeOfGameLabel->setStyleSheet("font-weight: bold; font: 12pt");
    sizeOfGameLabel->setGeometry(0,100,500,30);
    sizeOfGameLabel->setAlignment(Qt::AlignCenter);

    sizeOfGame = new QSpinBox(this);
    sizeOfGame->setRange(3,7);
    sizeOfGame->setGeometry(225,150,50,30);
    sizeOfGame->setStyleSheet("font-weight: bold; font: 12pt");

    startGame = new QPushButton(this);
    startGame->setText("Start Game");
    startGame->setStyleSheet("font-weight: bold; font: 12pt");
    startGame->setGeometry(170,200,150,40);


    connect(startGame, SIGNAL(clicked()), this, SLOT(beginToPlay()));
}

Widget::~Widget()
{
}

void Widget::beginToPlay()
{
    game = new TicTacToe(sizeOfGame->value());
    game->show();
}

