#include "game.h"
#include <QDebug>

Game::Game(int row, int col, int length, int block_size) {
    ROW = row;
    COL = col;
    LENGTH = length;
    BLOCK_SIZE = block_size;

    board = new int*[ROW+3];
    for(int i=0;i<ROW+3;i++) {
        board[i] = new int[COL];
        for(int j=0;j<COL;j++) board[i][j] = 0;
    }

    next = new int*[length];
    for(int i=0;i<LENGTH;i++) next[i] = new int[2];
    isOver = false;
}

Game::~Game() {
    delete[] next;
    for(int i=0;i<ROW+3;i++) {
        delete[] board[i];
    }
    delete[] board;
}

//유효한 움직임 확인
bool Game::isValid(bool isDown) {
    for(int i=0;i<axis_size;i++) {
        for(int j=0;j<axis_size;j++) {
            //qDebug("isValid : %d %d %d %d", i, j, (int)(nowPos[0]), (int)(nowPos[1]));
            if(now[i][j]>0) { //현재 요소의 유효한 영역인가?
                if(nowPos[0]+1-i<0) return false; //게임판 바깥
                if((int)(nowPos[1])+j-1<0 || (int)(nowPos[1])+j-1>=COL) return false; //게임판 바깥
                if(board[(int)(nowPos[0])+1-i][(int)(nowPos[1]+j-1)] < 0) return false; //다른 요소와 겹치는 경우
            }
        }
    }
    return true;
}

//가상함수들 -> 각 클래스에서 구현
bool Game::gravity() {
    return true;
}

void Game::loadNext() {
    return;
}

bool Game::endCheck() {
    return true;
}

void Game::fix() { //현재 위치에 고정
    for(int i=0;i<ROW+2;i++) {
        for(int j=0;j<COL;j++) {
            if(board[i][j] > 0) { //모든 양수를 음수로
                board[i][j] *= -1;
            }
        }
    }
    return;
}

void Game::rotation(bool clockwise) { //회전
    if(nowPos[0] < 0) return;
    if(axis_size==2) return;
    if(clockwise) { //시계방향
        int temp[axis_size][axis_size];
        for(int i=0;i<axis_size;i++) {
            for(int j=0;j<axis_size;j++) {
                temp[j][i] = now[axis_size-i-1][j];
            }
        }
        for(int i=0;i<axis_size;i++) {
            for(int j=0;j<axis_size;j++) {
                now[i][j] = temp[i][j];
            }
        }
    } else { //반시계 방향
        int temp[axis_size][axis_size];
        for(int i=0;i<axis_size;i++) {
            for(int j=0;j<axis_size;j++) {
                temp[j][i] = now[i][axis_size-j-1];
            }
        }
        for(int i=0;i<axis_size;i++) {
            for(int j=0;j<axis_size;j++) {
                now[i][j] = temp[i][j];
            }
        }
    }
}

Puyopuyo::Puyopuyo() : Game(12, 6, 2, 50) { //PuyoPuyo Option
    srand(time(NULL));
    next[0][0] = 1 + rand()%5; //NEXT 랜덤 설정
    next[0][1] = 1 + rand()%5;
    next[1][0] = 1 + rand()%5;
    next[1][1] = 1 + rand()%5;

    now = new int*[3];
    for(int i=0;i<3;i++) {
        now[i] = new int[3];
        for(int j=0;j<3;j++) {
            now[i][j] = 0;
        }
    }
    now[0][1] = 1+rand()%5;
    now[1][1] = 1+rand()%5;

    nowPos[0] = 12; //스폰 지점
    nowPos[1] = 2;

    axis_size = 3; //항상 3x3 크기의 현재 블록을 가짐

    score = 0;
    subData = 0;
}

void Puyopuyo::connected(std::set<POS>* l, POS last) {
    const int checklist[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    //qDebug("Connect Check at %d %d", last.x, last.y);
    for(int i=0;i<4;i++) {
        if((last.x+checklist[i][0]>=0&&last.x+checklist[i][0]<ROW&&
             last.y+checklist[i][1]>=0&&last.y+checklist[i][1]<COL)&&
            board[last.x+checklist[i][0]][last.y+checklist[i][1]] == board[last.x][last.y]) {
            POS now = POS(last.x+checklist[i][0],last.y+checklist[i][1]);
            //qDebug("Checking %d %d", now.x, now.y);
            if(l->find(now)==l->end()) {
                //qDebug("Found Same Color at %d %d", now.x, now.y);
                l->insert(now);
                connected(l, now);
            }
        }
    }
    return;
}

bool Puyopuyo::gravity() { //뿌요뿌요 중력 처리
    fix();
    nowPos[0] = -5;
    bool end = true;
    bool dropped = false;
    do { //공중에 떠있는 모든 요소 바닥으로
        dropped = false;
        for(int i=ROW-1;i>0;i--) {
            for(int j=0;j<COL;j++) {
                if((board[i][j] < 0) && (board[i-1][j] == 0)) {
                    board[i-1][j] = board[i][j];
                    board[i][j] = 0;
                    //qDebug("%d %d need gravity", i, j);
                    end = false;
                    dropped = true;
                }
            }
        }
    } while(dropped);
    if(end) { //공중 요소 처리를 했다면 한틱 기다려주기 위해 조건 삽입
        for(int i=0;i<ROW;i++) {
            for(int j=0;j<COL;j++) {
                if(board[i][j]<0) {
                    std::set<POS> puyos; //집합 STL을 통한 쉬운 중복요소 확인 및 제거
                    POS now = POS(i, j);
                    puyos.insert(now);
                    connected(&puyos, now); //재귀적 연결 확인
                    if(puyos.size()>=4) {
                        std::set<POS>::iterator iter;
                        for(iter = puyos.begin(); iter!=puyos.end(); iter++) {
                            board[iter->x][iter->y] = 0;
                        }
                        score+=subData+1;
                        end = false;
                    }
                }
            }
        }
        if(!end) {
            subData++; //연쇄 수치의 증가
        }
    }
    return end;
}

void Puyopuyo::loadNext() { //다음 요소 불러오기
    nowPos[0] = 12;
    nowPos[1] = 1;
    for(int i=0;i<axis_size;i++) {
        for(int j=0;j<axis_size;j++) {
            now[i][j] = 0;
        }
    }
    now[0][1] = next[0][0];
    now[1][1] = next[0][1];
    for(int i=0;i<LENGTH-1;i++) {
        next[i][0] = next[i+1][0];
        next[i][1] = next[i+1][1];
    }
    next[LENGTH-1][0] = 1+rand()%5; //next에는 0과 1에 쌍을 이루는 뿌요의 종류를 기록한다.
    next[LENGTH-1][1] = 1+rand()%5;
}

bool Puyopuyo::endCheck() { //종료 조건 확인
    if(board[11][2]!=0) { // (11,2)에 요소가 있다면 종료
        isOver = true;
        return true;
    }
    return false;
}


Tetris::Tetris() : Game(20, 10, 5, 30) { //Tetris Option

    //모든 테트리스 블록의 형태 사전 기록
    blockShape = new int**[7];
    for(int i=0;i<7;i++) {
        int** result;
        if(i < 5) { // L, J, S, Z, T
            result = new int*[3];
            for(int i=0;i<3;i++) {
                result[i] = new int[3];
                for(int j=0;j<3;j++) {
                    result[i][j] = 0;
                }
            }
        }
        else if(i < 6) { // I
            result = new int*[4];
            for(int i=0;i<4;i++) {
                result[i] = new int[4];
                for(int j=0;j<4;j++) {
                    result[i][j] = 0;
                }
            }
        } else if(i < 7) { //O
            result = new int*[2];
            for(int i=0;i<2;i++) {
                result[i] = new int[2];
                for(int j=0;j<2;j++) {
                    result[i][j] = 0;
                }
            }
        }
        if(i == 0) { //L
            result[0][2] = result[1][0] = result[1][1] = result[1][2] = i+10;
        } else if(i==1) { //J
            result[1][0] = result[1][1] = result[1][2] = result[0][0] = i+10;
        } else if(i==2) { //S
            result[1][0] = result[1][1] = result[0][1] = result[0][2] = i+10;
        } else if(i==3) { //Z
            result[0][0] = result[0][1] = result[1][1] = result[1][2] = i+10;
        } else if(i==4) { //T
            result[1][0] = result[0][1] = result[1][1] = result[1][2] = i+10;
        } else if(i==5) { //I
            result[1][0] = result[1][1] = result[1][2] = result[1][3] = i+10;
        } else if(i==6) { //O
            result[0][0] = result[0][1] = result[1][0] = result[1][1] = i+10;
        }

        blockShape[i] = result;
    }

    // for(int i=0;i<7;i++) {
    //     qDebug("%p", blockShape[i]);
    // }

    for(int i=0;i<5;i++) {
        next[i][0] = 10+rand()%7;
        if(next[i][0] < 15) next[i][1] = 3;
        else if(next[i][0] < 16) next[i][1] = 4;
        else if(next[i][0] < 17) next[i][1] = 2;
    }

    score = -1;
    loadNext();
    score = 0;
    subData = 0;
}

void Tetris::loadNext() { //다음 요소 불러오기

    //now 삭제하기 << 이전 요소와 크기가 다를 수 있기 때문에
    if(score != -1) {
        for(int i=0;i<axis_size;i++) {
            delete[] now[i];
        }
        delete[] now;
    }

    //요소 크기 설정
    if(next[0][0] < 15) { // L, J, S, Z, T
        axis_size = 3;
        nowPos[0] = 20;
        nowPos[1] = 4;
        now = new int*[axis_size];
        for(int i=0;i<axis_size;i++) {
            now[i] = new int[axis_size];
            for(int j=0;j<axis_size;j++) {
                now[i][j] = 0;
            }
        }
    }
    else if(next[0][0] < 16) { // I
        axis_size = 4;
        nowPos[0] = 20;
        nowPos[1] = 4;
        now = new int*[axis_size];
        for(int i=0;i<axis_size;i++) {
            now[i] = new int[axis_size];
            for(int j=0;j<axis_size;j++) {
                now[i][j] = 0;
            }
        }
    } else if(next[0][0] < 17) { //O
        axis_size = 2;
        nowPos[0] = 20;
        nowPos[1] = 4;
        now = new int*[axis_size];
        for(int i=0;i<axis_size;i++) {
            now[i] = new int[axis_size];
            for(int j=0;j<axis_size;j++) {
                now[i][j] = 0;
            }
        }
    }
    for(int i=0;i<axis_size;i++) {
        for(int j=0;j<axis_size;j++) {
            now[i][j] = blockShape[next[0][0]-10][i][j]; //저장된 블럭 모양 복사
        }
    }
    axis_size = next[0][1];
    if(next[0][0] < 15) {
        nowPos[0] = 20;
        nowPos[1] = 4;
    } else if(next[0][0] < 17) {
        nowPos[0] = 20;
        nowPos[1] = 4;
    }

    //next에는 블록의 종류와 해당 블록의 크기를 기록한다.
    for(int i=0;i<LENGTH-1;i++) {
        next[i][0] = next[i+1][0];
        next[i][1] = next[i+1][1];
    }
    next[LENGTH-1][0] = 10+rand()%7;
    if(next[LENGTH-1][0] < 15) next[LENGTH-1][1] = 3;
    else if(next[LENGTH-1][0] < 16) next[LENGTH-1][1] = 4;
    else if(next[LENGTH-1][0] < 17) next[LENGTH-1][1] = 2;
}

bool Tetris::gravity() {
    fix();
    nowPos[0] = -5;
    int fillcnt = 0; //한 행 이상 채웠나 확인하는 용도
    int i=0;
    while(i<ROW) { //for문 사용 시, 제거 후 다음 줄로 넘어가면서 조건이 맞아도 제거되지 않는 문제가 있었음
        bool filled = true;
        for(int j=0;j<COL;j++) {
            if(board[i][j]==0) {
                filled = false;
            }
        }
        if(filled) {
            for(int j=i;j<ROW-1;j++) {
                for(int k=0;k<COL;k++) {
                    board[j][k] = board[j+1][k];
                }
            }
            for(int j=0;j<COL;j++) {
                board[19][j] = 0; //맨 윗줄은 그냥 비운다.
            }
            fillcnt++;
        } else i++; //제거하지 못했을 때만 다음 줄을 처리하도록 하였다.
    }
    if(fillcnt > 0) subData++; //한줄이라도 제거했다면 콤보 증가
    else subData = 0; //한줄도 제거하지 못했다면 콤보 초기화
    for(int i=0;i<fillcnt;i++) {
        score += subData*(i+1);
    }
    qDebug("%d", subData);
    return true;
}

bool Tetris::endCheck() { //종료 조건 확인
    for(int i=0;i<10;i++) { //표시되는 맨 윗 행보다 하나 더 위에 있는 행(화면에는 표시되지 않음)
        if(board[20][i]!=0) {
            isOver = true;
            return true;
        }
    }
    return false;
}

PuyopuyoTetris::PuyopuyoTetris() : Game(16, 8, 6, 40) { //PuyopuyoTetris Option

    //테트로미노에 의해 위로 올라가게 되는 뿌요의 저장 공간(극단적인 상황 케어를 위해 판 크기와 같다.)
    savePuyo = new int*[ROW];
    for(int i=0;i<ROW;i++) {
        savePuyo[i] = new int[COL];
        for(int j=0;j<COL;j++) {
            savePuyo[i][j] = 0;
        }
    }

    //테트로미노의 모든 형태를 기록해두는 공간
    blockShape = new int**[7];
    for(int i=0;i<7;i++) {
        int** result;
        if(i < 5) { // L, J, S, Z, T
            result = new int*[3];
            for(int i=0;i<3;i++) {
                result[i] = new int[3];
                for(int j=0;j<3;j++) {
                    result[i][j] = 0;
                }
            }
        }
        else if(i < 6) { // I
            result = new int*[4];
            for(int i=0;i<4;i++) {
                result[i] = new int[4];
                for(int j=0;j<4;j++) {
                    result[i][j] = 0;
                }
            }
        } else if(i < 7) { //O
            result = new int*[2];
            for(int i=0;i<2;i++) {
                result[i] = new int[2];
                for(int j=0;j<2;j++) {
                    result[i][j] = 0;
                }
            }
        }
        if(i == 0) { //L
            result[0][2] = result[1][0] = result[1][1] = result[1][2] = i+10;
        } else if(i==1) { //J
            result[1][0] = result[1][1] = result[1][2] = result[0][0] = i+10;
        } else if(i==2) { //S
            result[1][0] = result[1][1] = result[0][1] = result[0][2] = i+10;
        } else if(i==3) { //Z
            result[0][0] = result[0][1] = result[1][1] = result[1][2] = i+10;
        } else if(i==4) { //T
            result[1][0] = result[0][1] = result[1][1] = result[1][2] = i+10;
        } else if(i==5) { //I
            result[1][0] = result[1][1] = result[1][2] = result[1][3] = i+10;
        } else if(i==6) { //O
            result[0][0] = result[0][1] = result[1][0] = result[1][1] = i+10;
        }

        blockShape[i] = result;
    }

    // for(int i=0;i<7;i++) {
    //     qDebug("%p", blockShape[i]);
    // }

    //뿌요와 테트리스의 next 저장 방식이 다르므로, 먼저 25 : 7로 확률을 나눈 뒤 안에서 무작위로 정한다.
    for(int i=0;i<6;i++) {
        int puyotet = rand()%32;
        if(puyotet>24) {
            next[i][0] = 10+rand()%7;
            if(next[i][0] < 15) next[i][1] = 3;
            else if(next[i][0] < 16) next[i][1] = 4;
            else if(next[i][0] < 17) next[i][1] = 2;
        }
        else {
            next[i][0] = 1+rand()%5;
            next[i][1] = 1+rand()%5;
        }
    }

    score = -1;
    loadNext();
    score = 0;
    subData = 0;
    savedLevel = 0;
}

bool PuyopuyoTetris::isValid(bool isDown) { //뿌요뿌요 테트리스 전용의 유효 확인 함수
    qDebug("%d %d", nowPuyo, isDown);
    //아래 움직임일 경우, 특수하게 적용되는 뿌요 저장 기능이 있는 조건
    if(!nowPuyo && isDown) {
        for(int i=0;i<axis_size;i++) {
            for(int j=0;j<axis_size;j++) {
                //qDebug("isValid : %d %d %d %d", i, j, (int)(nowPos[0]), (int)(nowPos[1]));
                if(now[i][j]>0) {
                    if(nowPos[0]+1-i<0) return false; //게임판 바깥
                    if((int)(nowPos[1])+j-1<0 || (int)(nowPos[1])+j-1>=COL) return false; //게임판 바깥
                    if(board[(int)(nowPos[0])+1-i][(int)(nowPos[1]+j-1)] < -9) return false; //테트로미노일 경우 저장하지 않음
                }
            }
        }
        for(int i=0;i<axis_size;i++) {
            bool saved = false;
            for(int j=0;j<axis_size;j++) {
                //qDebug("isValid : %d %d %d %d", i, j, (int)(nowPos[0]), (int)(nowPos[1]));
                if(now[i][j]>0) {
                    if(board[(int)(nowPos[0])+1-i][(int)(nowPos[1]+j-1)] < 0) { //뿌요인 경우, 저장
                        qDebug("Want to Save Puyo at : %d %d", savedLevel, (int)(nowPos[1]+j-1));
                        savePuyo[savedLevel][(int)(nowPos[1]+j-1)] =
                            board[(int)(nowPos[0])+1-i][(int)(nowPos[1]+j-1)];
                        saved = true;
                    }
                }
            }
            if(saved) savedLevel++; //행에서 하나라도 저장하면 저장 행을 넘김
        }
    } else { //기존의 isValid
        for(int i=0;i<axis_size;i++) {
            for(int j=0;j<axis_size;j++) {
                //qDebug("isValid : %d %d %d %d", i, j, (int)(nowPos[0]), (int)(nowPos[1]));
                if(now[i][j]>0) {
                    if(nowPos[0]+1-i<0) return false;
                    if((int)(nowPos[1])+j-1<0 || (int)(nowPos[1])+j-1>=COL) return false;
                    if(board[(int)(nowPos[0])+1-i][(int)(nowPos[1]+j-1)] < 0) return false;
                }
            }
        }
    }
    return true;
}

bool PuyopuyoTetris::gravity() { //뿌요뿌요 테트리스 중력
    fix();
    nowPos[0] = -5;
    if(nowPuyo) { //뿌요뿌요 상태일 경우, 뿌요뿌요와 거의 동일함
        bool end = true;
        bool dropped = false;
        do {
            dropped = false;
            for(int i=ROW-1;i>0;i--) {
                for(int j=0;j<COL;j++) {
                    if((board[i][j] < 0) && (board[i-1][j] == 0) && board[i][j] > -9) {
                        board[i-1][j] = board[i][j];
                        board[i][j] = 0;
                        //qDebug("%d %d need gravity", i, j);
                        end = false;
                        dropped = true;
                    }
                }
            }
        } while(dropped);
        if(end) {
            for(int i=0;i<ROW;i++) {
                for(int j=0;j<COL;j++) {
                    if(board[i][j]<0 && board[i][j]>-9) { //테트로미노는 연결되어도 처리하지 않도록 설정
                        std::set<POS> puyos;
                        POS now = POS(i, j);
                        puyos.insert(now);
                        connected(&puyos, now);
                        if(puyos.size()>=4) {
                            std::set<POS>::iterator iter;
                            for(iter = puyos.begin(); iter!=puyos.end(); iter++) {
                                board[iter->x][iter->y] = 0;
                            }
                            score+=subData+1;
                            end = false;
                        }
                    }
                }
            }
            if(!end) { //뿌요 처리의 연속 콤보 처리를 위한 subData 음수 처리
                if(subData < 0) {
                    subData *= -1;
                }
                subData++;
            } else {
                if(subData < 0) {
                    subData = 0;
                }
            }
        }
        return end;
    }
    //테트리스 일 경우의 처리, 마찬가지로 거의 동일함
    int fillcnt = 0;
    int i=0;
    while(i<ROW) {
        bool filled = true;
        for(int j=0;j<COL;j++) {
            if(board[i][j]>-9) {
                filled = false;
            }
        }
        if(filled) {
            for(int j=i;j<ROW+1;j++) {
                for(int k=0;k<COL;k++) {
                    board[j][k] = board[j+1][k];
                }
            }
            for(int j=0;j<COL;j++) {
                board[ROW+2][j] = 0;
            }
            fillcnt++;
        } else i++;
    }
    if(fillcnt > 0) {
        if(subData < 0) subData *= -1; //음수 subData 처리
        subData++;
    }
    else subData = 0;
    for(int i=0;i<fillcnt;i++) {
        score += subData*(i+1);
    }

    //저장된 뿌요 행 출력하기
    if(savedLevel > 0) {
        for(int i=savedLevel-1;i>=0;i--) {
            nowPuyo = true;
            for(int j=0;j<COL;j++) {
                board[18][j] = savePuyo[i][j];
                savePuyo[i][j] = 0;
            }
            for(int i=ROW+2;i>0;i--) {
                for(int j=0;j<COL;j++) {
                    if((board[i][j] < 0) && (board[i-1][j] == 0) && board[i][j] > -9) {
                        board[i-1][j] = board[i][j];
                        board[i][j] = 0;
                    }
                }
            }
        }
        savedLevel = 0;
        nowPuyo = true; //위로 올라가고 연속된 뿌요가 있을 수도 있기 때문에
        //뿌요 상태로 바꾸고, 중력 처리의 종료 신호를 보내지 않음.
        return false;
    }
    qDebug("%d", subData);
    return true;

}

void PuyopuyoTetris::connected(std::set<POS>* l, POS last) { //연결 확인 재귀함수
    const int checklist[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    //qDebug("Connect Check at %d %d", last.x, last.y);
    for(int i=0;i<4;i++) {
        if((last.x+checklist[i][0]>=0&&last.x+checklist[i][0]<ROW&&
             last.y+checklist[i][1]>=0&&last.y+checklist[i][1]<COL)&&
            board[last.x+checklist[i][0]][last.y+checklist[i][1]] == board[last.x][last.y]) {
            POS now = POS(last.x+checklist[i][0],last.y+checklist[i][1]); //다음 요소 위치 저장
            //qDebug("Checking %d %d", now.x, now.y);
            if(l->find(now)==l->end()) { //집합 자체 메써드 사용
                //qDebug("Found Same Color at %d %d", now.x, now.y);
                l->insert(now);
                connected(l, now);
            }
        }
    }
    return;
}

void PuyopuyoTetris::loadNext() { //다음 요소 불러오기
    //다음 요소가 뿌요일 경우
    if(next[0][0] < 10) {
        nowPuyo = true;
        if(score != -1) {
            for(int i=0;i<axis_size;i++) {
                delete[] now[i];
            }
            delete[] now;
        }
        axis_size = 3;
        now = new int*[3];
        for(int i=0;i<3;i++) {
            now[i] = new int[3];
        }
        for(int i=0;i<axis_size;i++) {
            for(int j=0;j<axis_size;j++) {
                now[i][j] = 0;
            }
        }
        now[0][1] = next[0][0];
        now[1][1] = next[0][1];
        for(int i=0;i<LENGTH-1;i++) {
            next[i][0] = next[i+1][0];
            next[i][1] = next[i+1][1];
        }
    }
    //다음 요소가 테트로미노일 경우
    else {
        nowPuyo = false;
        if(score != -1) {
            for(int i=0;i<axis_size;i++) {
                delete[] now[i];
            }
            delete[] now;
        }
        if(next[0][0] < 15) { // L, J, S, Z, T
            axis_size = 3;
            nowPos[0] = 20;
            nowPos[1] = 4;
            now = new int*[axis_size];
            for(int i=0;i<axis_size;i++) {
                now[i] = new int[axis_size];
                for(int j=0;j<axis_size;j++) {
                    now[i][j] = 0;
                }
            }
        }
        else if(next[0][0] < 16) { // I
            axis_size = 4;
            nowPos[0] = 20;
            nowPos[1] = 4;
            now = new int*[axis_size];
            for(int i=0;i<axis_size;i++) {
                now[i] = new int[axis_size];
                for(int j=0;j<axis_size;j++) {
                    now[i][j] = 0;
                }
            }
        } else if(next[0][0] < 17) { //O
            axis_size = 2;
            nowPos[0] = 20;
            nowPos[1] = 4;
            now = new int*[axis_size];
            for(int i=0;i<axis_size;i++) {
                now[i] = new int[axis_size];
                for(int j=0;j<axis_size;j++) {
                    now[i][j] = 0;
                }
            }
        }
        for(int i=0;i<axis_size;i++) {
            for(int j=0;j<axis_size;j++) {
                now[i][j] = blockShape[next[0][0]-10][i][j];
            }
        }
        axis_size = next[0][1];

        for(int i=0;i<LENGTH-1;i++) {
            next[i][0] = next[i+1][0];
            next[i][1] = next[i+1][1];
        }
    }

    //게임 처음 시작 시 설정하던 것과 같은 과정
    int puyotet = rand()%32;
    if(puyotet>24) {
        next[LENGTH-1][0] = 10+rand()%7;
        if(next[LENGTH-1][0] < 15) next[LENGTH-1][1] = 3;
        else if(next[LENGTH-1][0] < 16) next[LENGTH-1][1] = 4;
        else if(next[LENGTH-1][0] < 17) next[LENGTH-1][1] = 2;
    }
    else {
        next[LENGTH-1][0] = 1+rand()%5;
        next[LENGTH-1][1] = 1+rand()%5;
    }

    qDebug("%d %d", next[0][0], next[0][1]);
    nowPos[0] = 16;
    nowPos[1] = 3;
}

bool PuyopuyoTetris::endCheck() { //종료 조건 확인
    for(int i=0;i<4;i++) {
        if(board[15][2+i] != 0) {
            isOver = true;
            return true;
        }
    }
    return false;
}
