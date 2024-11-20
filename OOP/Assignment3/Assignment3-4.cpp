
#include <iostream>
#include <ctime>
using namespace std;

class Time {
private:
    int hour;
    int minute;
    int second;
public:
    Time(int hour, int min, int sec) {
        this->hour = hour;
        this->minute = min;
        this->second = sec;
    }
    ~Time() { return; }
    void setTime(int hour, int min, int sec) {
        this->hour = hour;
        this->minute = min;
        this->second = sec;
    }
    void addTime(int sec) {
        this->second += sec;
        if (this->second / 60) {
            this->minute += this->second / 60;
            this->second %= 60;
        }
        if (this->minute / 60) {
            this->hour += this->minute / 60;
            this->minute %= 60;
        }
        if (this->hour / 24) {
            this->hour %= 24;
        }
    }
    void printTime() {
        cout << this->hour << ":" << this->minute << ":" << this->second << endl;
    }
};

//한국 (GMT+9)
class Korea : public Time {
public:
    Korea(int hour, int min, int sec) : Time(hour, min, sec) {
        this->addTime(9 * 60 * 60);
    }
    ~Korea() { return; }
};

//워싱턴 DC (서머타임 미적용 시, GMT-5)
class WashingtonDC : public Time {
public:
    WashingtonDC(int hour, int min, int sec) : Time(hour, min, sec) {
        this->addTime(-5 * 60 * 60);
    }
    ~WashingtonDC() { return; }
};

//파리 (서머타임 미적용 시, GMT+1)
class Paris : public Time {
public:
    Paris(int hour, int min, int sec) : Time(hour, min, sec) {
        this->addTime(1 * 60 * 60);
    }
    ~Paris() { return; }
};

//그리치니 시간 (서머타임 미적용 시, GMT);
class GreenwichObservatory : public Time {
public:
    GreenwichObservatory(int hour, int min, int sec) : Time(hour, min, sec) {
        this->addTime(0 * 60 * 60);
    }
    ~GreenwichObservatory() { return; }
};

bool strCmp(const char* a, const char* b) {
    int i = 0;
    while (true) {
        if (a[i] != b[i]) return 1;
        if (a[i] == NULL) return 0;
        i++;
    }
    return 0;
}

int main()
{
    Korea k = Korea(0, 0, 0);
    WashingtonDC w = WashingtonDC(0, 0, 0);
    Paris p = Paris(0, 0, 0);
    GreenwichObservatory g = GreenwichObservatory(0, 0, 0);

    char temp[100];
    while (true) {
        cin >> temp;
        if (strCmp(temp, "setting") == 0) {
            k.setTime(0, 0, 0);
            k.addTime(9 * 60 * 60);
            w.setTime(0, 0, 0);
            w.addTime(-5 * 60 * 60);
            p.setTime(0, 0, 0);
            p.addTime(1 * 60 * 60);
            g.setTime(0, 0, 0);
            k.addTime(time(NULL));
            w.addTime(time(NULL));
            p.addTime(time(NULL));
            g.addTime(time(NULL));
        }
        else if (strCmp(temp, "print") == 0) {
            cout.width(20);
            cout << left << "Korea" << " = ";
            k.printTime();
            cout.width(20);
            cout << left << "WashingtonDC" << " = ";
            w.printTime();
            cout.width(20);
            cout << left << "Paris" << " = ";
            p.printTime();
            cout.width(20);
            cout << left << "GreenwichObservatory" << " = ";
            g.printTime();
            cout << endl;
        }
        else if (strCmp(temp, "add") == 0) {
            int add;
            cin >> add;
            k.addTime(add);
            w.addTime(add);
            p.addTime(add);
            g.addTime(add);
        }
        else if (strCmp(temp, "exit") == 0) {
            cout << "Exit The Program." << endl;
            break;
        }
        else {
            cout << "Invalid Command." << endl;
        }
    }
}