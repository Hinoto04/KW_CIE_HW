#include "gameoverwindow.h"

GameOverWindow::GameOverWindow(int score, QWidget* parent) : QWidget(parent) {
    setWindowTitle("GameOver");
    resize(600, 400);

    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel("GAME OVER...", this);
    label->setAlignment(Qt::AlignCenter);
    label->setFont(QFont("Nanum Gothic", 48));
    layout->addWidget(label);

    QLabel* scoreLabel = new QLabel("Final Score : "+QString::number(score), this);
    scoreLabel->setAlignment(Qt::AlignCenter);
    scoreLabel->setFont(QFont("Nanum Gothic", 24));
    layout->addWidget(scoreLabel);

    QPushButton* button = new QPushButton("OK", this);
    layout->addWidget(button);

    connect(button, &QPushButton::clicked, this, &GameOverWindow::onButtonClicked);
}

GameOverWindow::~GameOverWindow() {;}

void GameOverWindow::onButtonClicked() {
    QApplication::quit();
}
