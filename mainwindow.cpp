#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDateTime>
#include "minesweeperfield.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    qsrand(static_cast<uint>(QDateTime::currentMSecsSinceEpoch() / 1000));
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);
    ui->difficultyChooser->addItem("Könnyű");
    ui->difficultyChooser->addItem("Közepes");
    ui->difficultyChooser->addItem("Nehéz");
    ui->mineField->setSpacing(2);

    connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startGameButton_clicked()
{

    if(ui->nameLine->text() != "") {

        ui->nameLabel->setText("Játékos: " + ui->nameLine->text());
        ui->difficultyLabel->setText(ui->difficultyChooser->currentText());

        if (ui->difficultyChooser->currentIndex() == 0) {
            initGame(10,10,10);
        } else if (ui->difficultyChooser->currentIndex() == 1) {
            initGame(15,20,50);
        } else {
            initGame(20,30,100);
        }

        ui->stackedWidget->setCurrentIndex(1);

    } else {
        QMessageBox::warning(this, "Nincs név", "Adjon meg felhasználónevet!");
    }
}

void MainWindow::onFieldClicked(int x, int y, bool mouse)
{
    vector<State> modifications = game->clickOnTile(static_cast<unsigned>(x),static_cast<unsigned>(y),mouse);
    for (State mod: modifications) {
        alterField(mod.x, mod.y, mod.action);
    }

    if (game->isEndGame() && modifications.size() > 0) {
        timer->stop();
        if (game->isAlive()) {
            winMessage();
        } else {
            loseMessage();
        }
    }
}

void MainWindow::tick()
{
    time +=1;
    ui->timeLabel->setText(QString::number((time/60)) + ":" + (time%60 < 10 ? "0":"") + QString::number((time%60)));
}

void MainWindow::initGame(int x, int y, int mines)
{
    initField(x,y);
    timer->stop();
    time = 0;
    ui->timeLabel->setText("0:00");
    timer->start(1000);
    unsigned u_x = static_cast<unsigned>(x);
    unsigned u_y = static_cast<unsigned>(y);
    unsigned u_mines = static_cast<unsigned>(mines);
    game = new MineSweeperGameModel(u_x, u_y, u_mines);
}

void MainWindow::initField(int x, int y)
{
    qDeleteAll(ui->mineField->children());
    for (MineSweeperField *field: fieldVector) {
        delete field;
    }

    fieldVector.clear();

    actualX = static_cast<unsigned>(x);
    actualY = static_cast<unsigned>(y);

    for (int i=0; i<x; i++) {
        for (int j=0; j<y; j++) {
            MineSweeperField *newField = new MineSweeperField(i,j);
            connect(newField, &MineSweeperField::activated, this, &MainWindow::onFieldClicked);

            ui->mineField->addWidget(newField,i,j);
            fieldVector.push_back(newField);
        }
    }
}

void MainWindow::alterField(unsigned x, unsigned y, int command)
{
    unsigned index = x*actualY + y;

    MineSweeperField *field = fieldVector[index];
    if (command == Action::MARK) {
        field->mark(true);
    } else if (command == Action::UNMARK) {
        field->mark(false);
    } else {
        field->show(command);
    }
}

void MainWindow::loseMessage()
{
    QMessageBox::StandardButton answer
            = QMessageBox::warning(this, "Vereség!",
                "Sajnos ez nem sikerült.\nSzeretnél új játékot?",
                 QMessageBox::Yes | QMessageBox::No);

    if (answer == QMessageBox::Yes) {
        ui->stackedWidget->setCurrentIndex(0);
    }

}

void MainWindow::winMessage()
{
    QMessageBox::StandardButton answer
            = QMessageBox::information(this, "Győzelem!",
                "Gratulálunk " + ui->nameLine->text() +", nyertél."
                "\nAz időd: " + ui->timeLabel->text() +
                 "\nSzeretnél új játékot?",
                 QMessageBox::Yes | QMessageBox::No);
    if (answer == QMessageBox::Yes) {
        ui->stackedWidget->setCurrentIndex(0);
    }

}

void MainWindow::on_actionNewGame_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionHelp_triggered()
{
    QMessageBox::information(this, "Játékszabály", "Ez egy hagyományos aknakereső. Írj be egy nevet, válassz nehézséget, és indulhat a móka!");
}
