#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>
#include <QTimerEvent>
#include <QKeyEvent>
#include "game.h"

const int DEFAULT_DELAY = 1000;
const int MARGIN = 5;

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    GameWindow(int gamemode, QWidget *parent = nullptr); //게임 진행용 창 생성자
    ~GameWindow(); //소멸자

    void paintEvent(QPaintEvent* e); //화면 그리기
    void keyPressEvent(QKeyEvent* e); //키 입력 이벤트 -> 사용자 동작 연결용
    void timerEvent(QTimerEvent* e); //타이머 이벤트 -> 요소 자동 하강용

    bool down(); //아래로 내리는 움직임에 대한 함수
    //void drop(); //
    void draw(); //Board에 블록 데이터 저장용

    int timer; //타이머ID 저장용

private:
    Game* playing;
    int gamemode;
    QColor PlacedPuyoColor[6] = { //설치된 뿌요 색상
        QColor(156,0,0),
        QColor(156,156,0),
        QColor(0,156,0),
        QColor(0,0,156),
        QColor(156,0,156),
        QColor(0,0,0)
    };
    QColor PuyoColor[6] = { //낙하 중인 뿌요 색상
        QColor(255,0,0),
        QColor(255,255,0),
        QColor(0,255,0),
        QColor(0,0,255),
        QColor(255,0,255),
        QColor(0,0,0)
    };
    QColor BlockColor[8] = { //설치된 블록 색상
        QColor(255,127,0), //L
        QColor(0,0,255), //J
        QColor(0,255,0), //S
        QColor(255,0,0), //Z
        QColor(156,0,156), //T
        QColor(0,255,255), //I
        QColor(255,255,0), //O
        QColor(0,0,0)
    };
    QColor PlacedBlockColor[8] = { //낙하 중 블록 색상
        QColor(156,100,0),
        QColor(0,0,156),
        QColor(0,156,0),
        QColor(156,0,0),
        QColor(100,0,100),
        QColor(0,156,156),
        QColor(156,156,0),
        QColor(0,0,0)
    };

};

#endif // GAMEWINDOW_H
