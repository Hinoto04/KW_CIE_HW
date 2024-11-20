#pragma once
#include <string>
using namespace std;

class Subtitle {
    public:
        int h = 0; //hour
        int m = 0; //minute
        int s = 0; //second
        string str; //subtitle content

        Subtitle() {
            return;
        }
        ~Subtitle() {
            return;
        }

        int toSeconds() { //time to seconds -> to Compare
            return h*3600 + m*60 + s;
        }

        void set(int h, int m, int s, string str) { //Subtitle information Setting
            this->h = h;
            this->m = m;
            this->s = s;
            this->str = str;
        }
};
