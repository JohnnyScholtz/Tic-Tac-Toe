#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include "boardobject.h"
#include "tictactoe.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();



public slots:


private:

    //static const int width;
    //static const int height;

    //BoardObject *board[width][height];
    TicTacToe *game;
    QSpinBox *sizeOfGame;
    QLabel *sizeOfGameLabel;
    QPushButton *startGame;


private slots:
    void beginToPlay();


signals:



};
#endif // WIDGET_H
