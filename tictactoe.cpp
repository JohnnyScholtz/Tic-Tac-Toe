#include "tictactoe.h"
#include <QRandomGenerator>

TicTacToe::TicTacToe(QWidget *parent) : QWidget(parent)
{
    width = 3;
    height = 3;
}

TicTacToe::~TicTacToe()
{
}

TicTacToe::TicTacToe(int size, QWidget *parent) : QWidget(parent)
{
    width = size;
    height = size;
    init();
}

void TicTacToe::init()
{
    win = false;

    setGeometry(500, 50, 100*width+130, 100*height+130);

    board = new BoardObject**[width];
        for (int x = 0; x < height; ++x)
            board[x] = new BoardObject*[height];

    QLabel *ticTacToe = new QLabel(this);
    ticTacToe->setText("Tic-Tac-Toe");
    ticTacToe->setStyleSheet("font-weight: bold; font: 30pt");
    ticTacToe->setGeometry(10, 10, width*100, 50);
    ticTacToe->setAlignment(Qt::AlignCenter);

    output = new QLabel(this);
    output->setText("");
    output->setStyleSheet("font-weight: bold; font: 20pt");
    output->setGeometry(10, 60, width*100, 50);
    output->setAlignment(Qt::AlignCenter);

    newGame = new QPushButton(this);
    newGame->setGeometry(100*width+20, 120, 100, 40);
    newGame->setText("New Game");
    newGame->setStyleSheet("font: 9pt; font-weight: bold");

    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            BoardObject *o = new BoardObject(this);
            o->move(100*x+10, 100*y+120);
            o->show();
            connect(o, SIGNAL(iwaschanged(ObjectState)), this, SLOT(objectChanged(ObjectState)));
            connect(newGame, SIGNAL(clicked()), o, SLOT(clear()));
            connect(this, SIGNAL(nextState(ObjectState)), o, SLOT(nextState(ObjectState)));
            connect(this, SIGNAL(gameOver()), o, SLOT(makeGameOver()));
            board[x][y] = o;
        }
    }

    connect(newGame, SIGNAL(clicked()), this, SLOT(clearGame()));

    setMinimumSize(100*width+130, 100*height+130);

    begin = true;

    who_Starts();

}

void TicTacToe::who_Starts()
{

    whoStarts = QRandomGenerator::global()->bounded(0,2);
    if (whoStarts == 0)
    {
        output->setText("It's your turn");
    }
    else if (whoStarts == 1)
    {
        output->setText("It's the computer's turn");
        win = false;
        computer();

    }
}

void TicTacToe::computer()
{
    int randomXvalue;
    int randomYvalue;

    if (!win)
    {
        do
        {
            randomXvalue = QRandomGenerator::global()->bounded(0,width);
            randomYvalue = QRandomGenerator::global()->bounded(0,height);
        }while(board[randomXvalue][randomYvalue]->state() != blank);

        board[randomXvalue][randomYvalue]->computerToPlay();
    }
}



void TicTacToe::objectChanged(ObjectState prevState)
{
    ObjectState winner;
    win = false;


    for (int y = 0; y < height; ++y)
    {
        bool fullRow = true;
        for (int x = 1; x < width; ++x)
        {
            if (board[x-1][y]->state() != board[x][y]->state())
            {
                fullRow = false;
                break;
            }
        }
        if (fullRow && (board[0][y]->state() != blank))
        {
            win = true;
            winner = board[0][y]->state();
            break;
        }
    }

    for (int x = 0; x < width; ++x)
    {
        bool fullColumn = true;
        for (int y = 1; y < height; ++y)
        {
            if (board[x][y-1]->state() != board[x][y]->state())
            {
                fullColumn = false;
                break;
            }
        }
        if (fullColumn && (board[x][0]->state() != blank))
        {
            win = true;
            winner = board[x][0]->state();
            break;
        }
    }

    bool fullDiagonal1 = true;
    for (int y = 1; y < height; ++y)
    {
        if (board[y-1][y-1]->state() != board[y][y]->state())
        {
            fullDiagonal1 = false;
            break;
        }
    }
    if (fullDiagonal1 && (board[0][0]->state() != blank))
    {
        win = true;
        winner = board[0][0]->state();
    }

    bool fullDiagonal2 = true;
    for (int y = 1; y < height; ++y)
    {
        if (board[width-y][y-1]->state() != board[width-y-1][y]->state())
        {
            fullDiagonal2 = false;
            break;
        }
    }
    if (fullDiagonal2 && (board[width-1][0]->state() != blank))
    {
        win = true;
        winner = board[width-1][0]->state();
    }

    if (prevState == O)
    {
        emit nextState(X);
        if (whoStarts == 0)
        {
            output->setText("It's your turn");
        }
        else
        {
            output->setText("");
            computer();
        }
    }
    else if (prevState == X)
    {
        emit nextState(O);
        if (whoStarts == 0)
        {
            output->setText("");

            computer();
        }
        else
        {
            output->setText("It's your turn");
        }
    }
    else if (whoStarts == 1 && begin)
    {
        computer();
        begin = false;
    }
    else
    {
        emit nextState(X);
        if (whoStarts == 0)
        {
            output->setText("It's your turn");
        }
        else
        {
            output->setText("");
            computer();
        }
    }


    if (win)
    {
        if (winner == 1)
        {
            if (whoStarts == 0)
            {
                output->setText("You Win!!");
            }
            else if (whoStarts == 1)
            {
                output->setText("The Computer Wins :(");
            }
        }

        else if (winner == 2)
        {
            if (whoStarts == 1)
            {
                output->setText("You Win!!");
            }
            else if (whoStarts == 0)
            {
                output->setText("The Computer Wins :(");
            }
        }

        for (int y = 0; y < height; ++y)
            for (int x = 0; x < width; ++x)
                gameOver();
    }

    bool tie = true;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (board[x][y]->state() == blank)
            {
                tie = false;
                break;
            }
        }
        if (!tie)
            break;
    }

    if (tie && !win)
        output->setText("It's a Tie!!");
}

void TicTacToe::clearGame()
{
    who_Starts();
}

