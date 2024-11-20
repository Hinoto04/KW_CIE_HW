#ifndef GAMEOVERWINDOW_H
#define GAMEOVERWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QApplication>
#include <QVBoxLayout>

class GameOverWindow : public QWidget
{
    Q_OBJECT
public:
    GameOverWindow(int score, QWidget* parent = nullptr);
    ~GameOverWindow();
private slots:
    void onButtonClicked();
};

#endif // GAMEOVERWINDOW_H
