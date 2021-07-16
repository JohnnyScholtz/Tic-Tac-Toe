#include "boardobject.h"

BoardObject::BoardObject(QWidget *parent) : QLabel(parent)
{
    setFixedSize(100, 100);
    nextstate = X;
    clear();
}

void BoardObject::mousePressEvent(QMouseEvent *e)
{
    if (objectState == blank)
    {
        if (nextstate == O)
            makeO();
        else if (nextstate == X)
            makeX();
    }

}

void BoardObject::clear()
{
    objectState = blank;
    setText("");
    nextstate = X;
    setStyleSheet("background-color: white; border: 2px solid black;");
}

void BoardObject::makeX()
{
    objectState = X;
    setText("X");
    setStyleSheet("font: 60pt; border: 2px solid black; background-color: white");
    setAlignment(Qt::AlignCenter);
    emit iwaschanged(objectState);
}

void BoardObject::makeO()
{
    objectState = O;
    setText("O");
    setStyleSheet("color: red; font: 60pt; border: 2px solid black; background-color: white");
    setAlignment(Qt::AlignCenter);
    emit iwaschanged(objectState);
}

void BoardObject::computerToPlay()
{
    QMouseEvent *e;
    mousePressEvent(e);
}

void BoardObject::nextState(ObjectState nextS)
{
     nextstate = nextS;
}

void BoardObject::makeGameOver()
{
    objectState = gameover;
}

ObjectState BoardObject::state()
{
    return objectState;
}
