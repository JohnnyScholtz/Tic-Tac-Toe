#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>


#include "boardobject.h"

class TicTacToe : public QWidget
{
    Q_OBJECT
public:
    TicTacToe(QWidget *parent = nullptr);
    TicTacToe(int, QWidget *parent = nullptr);
    ~TicTacToe();

private:

    int width;
    int height;
    BoardObject ***board;

    QLabel *output;
    QLabel *winner;
    QPushButton *newGame;
    bool win;
    bool begin;
    void init();
    void computer();
    int whoStarts;
    void who_Starts();

private slots:
    void objectChanged(ObjectState);
    void clearGame();

signals:
    void gameOver();
    void nextState(ObjectState);


};

#endif // TICTACTOE_H
