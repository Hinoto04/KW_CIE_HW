
#include <iostream>
#include <conio.h>
#include <random>
#include <ctime>
#include <Windows.h>
#define DISTANCE 20
using namespace std;

enum State
{
	back, front
};

class TaggerState {
public:
	virtual void toward() = 0;
	virtual State state() = 0;
	virtual void set(int* p) = 0;
};

class Back : public TaggerState {
private:
	int* progress;
public:
	void set(int* p) {
		this->progress = p;
	}
	State state() { return back; }
	void toward() override {
		*progress = *progress + 1;
	};
};

class Front : public TaggerState {
private:
	int* founded;
public:
	void set(int* p) {
		this->founded = p;
	}
	State state() { return front; }
	void toward() override {
		*founded = 1;
	}
};

class Player {
private:
	TaggerState* state;
	int progress;
	int founded;
public:
	Player() {
		this->founded = 0;
		this->progress = 0;
		this->state = new Back();
		this->state->set(&this->progress);
	}
	~Player() {
		delete state;
		return;
	}

	void SetState() {
		if (this->state->state() == back) {
			delete this->state;
			this->state = new Front();
			this->state->set(&founded);
		}
		else {
			delete this->state;
			this->state = new Back();
			this->state->set(&progress);
		}
	}
	void toward() {
		this->state->toward();
	}
	State getState() { return this->state->state(); }
	int GetProgress() { return progress; }
	int getFounded() { return founded; }
};

//현재 진행 상태 출력
void printProgress(Player& player, int cnt = 0, bool toward = false) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
	State state = player.getState();
	int progress = player.GetProgress();
	if (state == back) {
		string s = "Green Light!";
		for (int i = 0; i < cnt; i++) {
			cout << s[i];
		}
		for (int i = cnt; i < 12; i++) {
			cout << " ";
		}
	}
	else cout << "Red Light!   ";
	cout << "\n\n\n\n";
	if (toward) {
		if (state == back) cout << "Forward" << endl;
		else cout << "Tagger found out." << endl;
	}
	else {
		cout << "                       " << endl;
	}
	cout << "\n\n";
	cout << " start | ";
	for (int i = 0; i < progress; i++) {
		cout << "@@";
	}
	for (int i = progress; i < DISTANCE; i++) {
		cout << "--";
	}
	cout << " | end ( " << progress << "/" << DISTANCE << ")" << endl;
	cout << "\n\n\n\n\n\n";
}

int main()
{
	srand(time(NULL));
	Player player;

	printProgress(player);

	int c;
	int lastTime = time(NULL);
	int changeCount = 11;
	while (true) {
		if (_kbhit()) {
			
			c = _getch();
			if (c == 224) {
				c = _getch();
				if (c == 77) {
					player.toward();
					printProgress(player, 12 - changeCount, true);
				}
			}
		}
		if (player.getFounded() || player.GetProgress() == DISTANCE) {
			break;
		}
		//Green Light, 현재 상태 1초마다 출력
		if (lastTime != time(NULL)) {
			if(player.getState() == front) changeCount--;
			lastTime = time(NULL);
			if (player.getState() == back) {
				changeCount -= rand() % 5 + 2;;
				if (changeCount < 0) changeCount = 0;
				printProgress(player, 12-changeCount);
			}
		}
		if (!changeCount) {
			player.SetState();
			if (player.getState() == front) {
				printProgress(player);
				changeCount = rand() % 9 + 2;
			}
			else changeCount = 12;
		}
	}
	printProgress(player, 0, true);
	if (player.getFounded()) {
		cout << "Lose.." << endl << endl;
	}
	else {
		cout << "Win!!" << endl << endl;
	}
	cout << "exit the program" << endl;
	//while (true);
}