#ifndef MINESWEEPERFIELD_H
#define MINESWEEPERFIELD_H
#include <QLabel>
#include <QPixmap>


class MineSweeperField: public QLabel
{
Q_OBJECT
public:
    MineSweeperField(int x, int y);
    virtual ~MineSweeperField();

    void mark(bool isMarked);
    void show(int fieldNum);

public:
signals:
    void activated(int x, int y, bool mouse);

protected:
    void mousePressEvent(QMouseEvent* event);

private:
    int x;
    int y;
    int xsize = 25;
    int ysize = 25;
    QPixmap hiddenImage;
    QPixmap markedImage;
    QPixmap mineImage;
    QPixmap labelImage;

};

#endif // MINESWEEPERFIELD_H
