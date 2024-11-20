#include "gamewindow.h"
#include "gameoverwindow.h"

GameWindow::GameWindow(int gamemode, QWidget* parent) : QWidget(parent) {
    timer = startTimer(DEFAULT_DELAY);

    QPalette pal = QPalette();
    pal.setColor(QPalette::Window, Qt::lightGray);

    if(gamemode == 0) {
        playing = new Puyopuyo();
        resize(400, 610);
        setWindowTitle("PUYOPUYO");
    }
    else if(gamemode == 1) {
        playing = new Tetris();
        resize(500, 610);
        setWindowTitle("TETRIS");
    }
    else {
        playing = new PuyopuyoTetris();
        resize(450, 650);
        setWindowTitle("PUYOPUYOTETRIS");
    }

    this->setAutoFillBackground(true); //자동 회색 배경 세팅
    this->setPalette(pal);

    this->gamemode = gamemode;

    draw();
}

GameWindow::~GameWindow() {
    delete playing;
}

void GameWindow::paintEvent(QPaintEvent* e) {
    int ROW = playing->ROW;
    int COL = playing->COL;
    int LENGTH = playing->LENGTH;
    int BLOCK_SIZE = playing->BLOCK_SIZE;
    int** board = playing->board;
    int** next = playing->next;

    int* nowPos = playing->nowPos;
    int score = playing->score;
    int subData = playing->subData;

    QPainter painter(this);
    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
    painter.drawRect(MARGIN, MARGIN, COL*BLOCK_SIZE, ROW*BLOCK_SIZE);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Nanum Gothic", 16));
    painter.drawText(QRect(MARGIN*3+COL*BLOCK_SIZE,MARGIN,70,50),Qt::AlignCenter, "NEXT");

    painter.drawText(QRect(MARGIN*3+COL*BLOCK_SIZE,MARGIN,70,800),
                     Qt::AlignCenter,"SCORE");
    painter.drawText(QRect(MARGIN*3+COL*BLOCK_SIZE,MARGIN,70,850),
                     Qt::AlignCenter,QString::number(score));
    if(gamemode == 0) {
        painter.drawText(QRect(MARGIN*3+COL*BLOCK_SIZE,MARGIN,70,950),
                         Qt::AlignCenter,"CHAIN");
    } else {
        painter.drawText(QRect(MARGIN*3+COL*BLOCK_SIZE,MARGIN,70,950),
                         Qt::AlignCenter,"COMBO");
    }

    painter.drawText(QRect(MARGIN*3+COL*BLOCK_SIZE,MARGIN,70,1000),
                     Qt::AlignCenter,QString::number(subData>0?subData:(subData*-1)));
    //UI 그리기

    // for(int i=0;i<7;i++) {
    //     qDebug("%p", playing->blockShape[i]);
    // }

    for(int i=0;i<LENGTH;i++) { //NEXT 표시
        int current_col = MARGIN*3+COL*BLOCK_SIZE;
        int current_row = MARGIN*10+BLOCK_SIZE*1.5*i;
        int mid = BLOCK_SIZE / 2;

        if(next[i][0]<6) { //PUYO
            for(int j=0;j<2;j++) {
                if(next[i][j] == 1) { //RED
                    painter.setBrush(QBrush(QColor(255,0,0), Qt::SolidPattern));
                    painter.drawEllipse(current_col+20, current_row + j * mid, mid, mid);
                }
                if(next[i][j] == 2) { //YELLOW
                    painter.setBrush(QBrush(QColor(255,255,0), Qt::SolidPattern));
                    painter.drawEllipse(current_col+20, current_row + j * mid, mid, mid);
                }
                if(next[i][j] == 3) { //GREEN
                    painter.setBrush(QBrush(QColor(0,255,0), Qt::SolidPattern));
                    painter.drawEllipse(current_col+20, current_row + j * mid, mid, mid);
                }
                if(next[i][j] == 4) { //BLUE
                    painter.setBrush(QBrush(QColor(0,0,255), Qt::SolidPattern));
                    painter.drawEllipse(current_col+20, current_row + j * mid, mid, mid);
                }
                if(next[i][j] == 5) { //PURPLE
                    painter.setBrush(QBrush(QColor(255,0,255), Qt::SolidPattern));
                    painter.drawEllipse(current_col+20, current_row + j * mid, mid, mid);
                }
            }
        }

        else if(next[i][0]>9) { //TETRIS
            painter.setBrush(QBrush(BlockColor[next[i][0]-10], Qt::SolidPattern));
            for(int j=0;j<next[i][1];j++) {
                for(int k=0;k<next[i][1];k++) {
                    //qDebug("%d %d %d %d", j, k, next[i][0], next[i][1]);
                    if(playing->blockShape[next[i][0]-10][j][k] > 0) {
                        painter.drawRect(current_col + k * mid + 10, current_row + mid * j, mid, mid);
                    }
                }
            }
        }
    }

    for(int i=0;i<ROW;i++) {
        for(int j=0;j<COL;j++) {
            if(board[i][j] > 9) {
                painter.setBrush(QBrush(BlockColor[board[i][j]-10], Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN, (ROW-i-1)*BLOCK_SIZE+MARGIN, BLOCK_SIZE, BLOCK_SIZE);
            }
            else if(board[i][j] < -9) {
                painter.setBrush(QBrush(PlacedBlockColor[(-1)*board[i][j]-10], Qt::SolidPattern));
                painter.drawRect(j*BLOCK_SIZE+MARGIN, (ROW-i-1)*BLOCK_SIZE+MARGIN, BLOCK_SIZE, BLOCK_SIZE);
            }
            else if(board[i][j] > 0) {
                painter.setBrush(QBrush(PuyoColor[board[i][j]-1], Qt::SolidPattern));
                painter.drawEllipse(j*BLOCK_SIZE+MARGIN, (ROW-i-1)*BLOCK_SIZE+MARGIN, BLOCK_SIZE, BLOCK_SIZE);
            }
            else if(board[i][j] < 0) {
                painter.setBrush(QBrush(PlacedPuyoColor[(-1)*board[i][j]-1], Qt::SolidPattern));
                painter.drawEllipse(j*BLOCK_SIZE+MARGIN, (ROW-i-1)*BLOCK_SIZE+MARGIN, BLOCK_SIZE, BLOCK_SIZE);
            }
        }
    }

    qDebug("%d, %d", nowPos[0], nowPos[1]);
    painter.setBrush(QBrush(QColor(0,0,0), Qt::SolidPattern));
    painter.drawRect(nowPos[1]*BLOCK_SIZE+MARGIN+BLOCK_SIZE*0.2,
                     (ROW-1-nowPos[0])*BLOCK_SIZE+MARGIN+BLOCK_SIZE*0.2,
                     BLOCK_SIZE*0.6,
                     BLOCK_SIZE*0.6);

}

void GameWindow::keyPressEvent(QKeyEvent* e) { //키보드 입력 이벤트
    if(playing->isOver) return;
    switch(e->key()) {
    case Qt::Key_Down: //아래 이동
        down();
        draw();
        break;
    case Qt::Key_Left: //좌측 이동
        playing->nowPos[1]-=1;
        if(!playing->isValid(false)) playing->nowPos[1]++;
        draw();
        break;
    case Qt::Key_Right: //우측 이동
        playing->nowPos[1]+=1;
        if(!playing->isValid(false)) playing->nowPos[1]--;
        draw();
        break;
    case Qt::Key_Z: //반시계 회전
        playing->rotation(false);
        if(!playing->isValid(false)) playing->rotation(true);
        draw();
        break;
    case Qt::Key_X: //시계 회전
        playing->rotation(true);
        if(!playing->isValid(false)) playing->rotation(false);
        draw();
        break;
    case Qt::Key_Space: //하드 드롭
        while(down()) draw(); //가능한 한 아래로
        break;
    }
}

void GameWindow::timerEvent(QTimerEvent* e) { //시간에 따른 자동으로 아래 입력
    down();
    if(e->timerId()==timer) {
        draw();
    }
}

bool GameWindow::down() { //아래로 이동 시 적용되는 함수
    if(playing->isOver) return false;
    if(playing->nowPos[0] < -4) { //현재 이동 및 생성이 제한된 상태
        if(playing->gravity()) {
            playing->loadNext();
            killTimer(timer);
            timer = startTimer(1000);
            if(playing->endCheck()) {
                GameOverWindow* overwindow = new GameOverWindow(playing->score);
                overwindow->show();
            }
        }
    } else {
        playing->nowPos[0]-=1;
        if(!playing->isValid(true)) {
            playing->nowPos[0]+=1;
            if(gamemode == 2) playing->subData *= -1;
            if(gamemode == 0) playing->subData = 0;
            killTimer(timer);
            timer = startTimer(200);
            if(playing->gravity()) {
                playing->loadNext();
                killTimer(timer);
                timer = startTimer(1000);
                if(playing->endCheck()) {
                    GameOverWindow* overwindow = new GameOverWindow(playing->score);
                    overwindow->show();
                }
            }
            return false;
        }
        return true;
    }
    return false;
}


void GameWindow::draw() { //board상태 지정용 함수
    if(playing->isOver) return;

    int ROW = playing->ROW+2;
    int COL = playing->COL;

    //int LENGTH = playing->LENGTH;

    int** board = playing->board;
    //int** next = playing->next;

    int** now = playing->now;
    int nowpos[2] = {playing->nowPos[0], playing->nowPos[1]};

    //기존의 활성화되어 있던 모든 양수 (조작 중 요소) 제거
    for(int i=0;i<ROW;i++) {
        for(int j=0;j<COL;j++) {
            if(board[i][j] > 0) board[i][j] = 0;
        }
    }

    //현재 위치에 따라 board에 현재 요소 위치 기록
    if(nowpos[0] >= 0) {
        for(int i=0;i<playing->axis_size;i++) {
            for(int j=0;j<playing->axis_size;j++) {
                if(now[i][j]>0) {
                    board[(int)(nowpos[0])+1-i][(int)(nowpos[1]+j-1)] = now[i][j];
                }
            }
        }
    }

    update();
}
