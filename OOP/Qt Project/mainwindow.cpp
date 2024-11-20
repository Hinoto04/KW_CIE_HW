#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "gamewindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::generateGame(int gamemode) {
    GameWindow* gamewindow = new GameWindow(gamemode);
    gamewindow->show();

    this->close();
}

void MainWindow::on_puyoStartBtn_clicked()
{
    qDebug("PUYOPUYO START!");
    generateGame(0);
}

void MainWindow::on_pushButton_clicked()
{
    qDebug("TETRIS START!");
    generateGame(1);
}


void MainWindow::on_pushButton_2_clicked()
{
    qDebug("PUYOPUYO TETRIS START!");
    generateGame(2);
}

