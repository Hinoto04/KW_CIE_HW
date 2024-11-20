#ifndef GAME_H
#define GAME_H

#include <random>
#include <ctime>
#include <set>

class POS { //int 배열은 비교연산자 오버로딩이 불가능하므로, 정의한 새로운 좌표 표현용 클래스
public:
    int x;
    int y;
    POS(int x, int y) {
        this->x = x;
        this->y = y;
    }
    bool operator<(const POS &target) const { //연산자 오버로딩 <
        return this->x!=target.x?this->x<target.x:this->y<target.y;
    }
    bool operator==(const POS &target) const { //연산자 오버로딩 ==
        return this->x==target.x&&this->y==target.y;
    }
    //연산자 오버로딩을 통해 STL::set에서 요소 찾기 및 중복 제거가 가능
};

class Game
{
public:
    int ROW; //행 크기
    int COL; //열 크기
    int LENGTH; //NEXT의 길이
    int BLOCK_SIZE; //블럭 크기

    int axis_size; //현재 블록의 한 축의 길이

    int subData; //체인 수 등 점수 계산용
    int score; //점수 기록

    bool isOver; //게임 종료 확인용

    int** board; //게임 판
    int** next; //다음 요소 목록
    int** now; //현재 요소 생김새
    int nowPos[2]; //현재 요소의 중심위치

    int*** blockShape; //테트리스 블록 형태 기록용

    Game(int row, int col, int length, int block_size);
    ~Game();

    virtual bool isValid(bool isDown); //유효한 움직임인가?
    virtual bool gravity(); //블럭을 내려놓은 뒤 처리
    void rotation(bool clockwise); //현재 블록 회전
    void fix();
    virtual void loadNext(); //다음 블록 now에 로딩
    virtual bool endCheck(); //종료조건 확인
};

class Puyopuyo : public Game {
public:
    Puyopuyo();
    ~Puyopuyo() {;}
    bool gravity();
    void connected(std::set<POS>* l, POS last);
    void loadNext();
    bool endCheck();
};

class Tetris : public Game {
public:
    Tetris();
    ~Tetris() {;}
    bool gravity();
    void loadNext();
    bool endCheck();
};

class PuyopuyoTetris : public Game {
public:

    bool nowPuyo;
    int** savePuyo;
    int savedLevel = 0;

    PuyopuyoTetris();
    ~PuyopuyoTetris() {;}
    bool gravity();
    bool isValid(bool isDown);
    void connected(std::set<POS>* l, POS last);
    void loadNext();
    bool endCheck();
};

#endif // GAME_H
