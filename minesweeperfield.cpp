#include "minesweeperfield.h"
#include <QMouseEvent>
#include <QPainter>
#include <QRandomGenerator>

MineSweeperField::MineSweeperField(int _x, int _y)
{
    x = _x;
    y = _y;

    labelImage = QPixmap(50,50);
    labelImage.fill(Qt::white);
    mineImage = QPixmap(":/mineImages/mineImages/mineImage.png");
    markedImage = QPixmap(":/mineImages/mineImages/flag.png");
    hiddenImage = QPixmap(":/mineImages/mineImages/basic.png");
    setPixmap(hiddenImage.scaled(xsize,ysize));
}

MineSweeperField::~MineSweeperField() {}

void MineSweeperField::mark(bool isMarked)
{
    if (isMarked) {
        setPixmap(markedImage.scaled(xsize, ysize));
    } else {
        setPixmap(hiddenImage.scaled(xsize, ysize));
    }
}

void MineSweeperField::show(int fieldNum)
{
    if (fieldNum == -1) {
        setPixmap(mineImage.scaled(xsize,ysize));
    } else {
        labelImage.fill(Qt::white);

        if (fieldNum > 0) {
            QPainter painter(&labelImage);
            painter.setFont(QFont("Arial", 25));
            painter.drawText( QRect(0,0,xsize*2,ysize*2), Qt::AlignCenter, QString::number(fieldNum));
        }
        setPixmap(labelImage.scaled(xsize,ysize));
    }
}

void MineSweeperField::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::RightButton) {
        emit activated(x, y, false);
    } else if (event->buttons() == Qt::LeftButton) {
        emit activated(x, y, true);
    }
}
