#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "minesweepergamemodel.h"
#include "minesweeperfield.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startGameButton_clicked();
    void onFieldClicked(int x, int y, bool mouse);
    void tick();
    void on_actionNewGame_triggered();

    void on_actionExit_triggered();

    void on_actionHelp_triggered();

private:

    void initGame(int x, int y, int mines);
    void initField(int x, int y);
    void alterField(unsigned x, unsigned y, int command);
    void loseMessage();
    void winMessage();

    Ui::MainWindow *ui;
    int difficulty;
    unsigned actualX;
    unsigned actualY;
    int time;
    vector<MineSweeperField*> fieldVector;

    QTimer *timer = new QTimer(this);

    MineSweeperGameModel *game;

};
#endif // MAINWINDOW_H
