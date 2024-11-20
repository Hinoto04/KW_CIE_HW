
#include <iostream>
#include <fstream>
#define LINE_MAX 1024
using namespace std;

int strcmp(char* a, const char* b) {
    int i = 0;
    while (true) {
        //cout << a[i] << " " << b[i] << endl;
        if (a[i] != b[i]) return false;
        if (a[i] == NULL) return true;
        i++;
    }
}

void search(ifstream &fs, int** searched) {

    char delimiter[99];
    cin >> delimiter;

    int dLength = 0;
    while (delimiter[dLength] != '\0') {
        dLength++;
    }
    //cout << dLength;

    int column = 0;
    int row = 0;

    int dStart = -1;

    int cnt = 0;
    searched[99][2];
    char now;
    while (fs.get(now)) {
        
        if (dStart == -1) {
            if (now == delimiter[0]) {
                dStart = column;
            }
        }
        else {
            if (column - dStart == dLength) {
                searched[cnt][0] = row;
                searched[cnt][1] = dStart;
                dStart = -1;
                cnt++;
            }
            if (now != delimiter[column - dStart]) {
                dStart = -1;
            }
        }
        column++;
        if (now == '\n') {
            row++;
            column = 0;
            dStart = -1;
        }
        //cout << dStart << " " << delimiter[column - dStart] << " " << now << endl;
    }
    cout << "==='" << delimiter << "' search(" << cnt << ")===" << endl;
    fs.clear();
    fs.seekg(0);
    return;
}

void change() {
    ifstream fs;
    fs.open("temp.txt");
    ofstream ofs;
    ofs.open("temp2.txt");
    char delimiter[99];
    cin >> delimiter;

    char changeTo[99];
    cin >> changeTo;

    cout << delimiter << " -> " << changeTo << endl;

    int dLength = 0;
    while (delimiter[dLength] != '\0') {
        dLength++;
    }

    int ctLength = 0;
    while (changeTo[ctLength] != '\0') {
        ctLength++;
    }

    char now[LINE_MAX];
    while (fs.getline(now, LINE_MAX)) {
        int start = 0;
        int dStart = -1;
        int i = 0;
        while (now[i] != '\0') {
            //cout << now[i] << " " << delimiter << endl;
            if (dStart == -1) {
                if (now[i] == delimiter[0]) {
                    //cout << "Delimiter Check" << endl;
                    dStart = i;
                }
            }
            else {
                if (i - dStart == dLength) {
                    //cout << "Delimiter Complete" << endl;
                    for (int j = start; j < dStart; j++) {
                        ofs << now[j];
                    }
                    for (int j = 0; j < ctLength; j++) {
                        ofs << changeTo[j];
                    }
                    start = i;
                    dStart = -1;
                }
                if (now[i] != delimiter[i - dStart]) {
                    dStart = -1;
                }
            }

            i++;
        }
        //cout << "EndLine";
        for (int j = start; j < i; j++) {
            //cout << now[j];
            ofs << (char)now[j];
        }
        ofs << endl;
    }
    ofs.close();
    //cout << "Comp";
    fs.close();
    ofs.open("temp.txt");
    fs.open("temp2.txt");
    char c;
    while (fs.get(c)) {
        ofs << c;
    }
    fs.close();
    return;
}

void insert() {
    ifstream ifs;
    ifs.open("temp.txt");
    ofstream ofs;
    ofs.open("temp2.txt");
    int wantedRow;
    cin >> wantedRow;
    int wantedCol;
    cin >> wantedCol;

    char temp[LINE_MAX];
    cin >> temp;

    int tempLen = 0;
    while (temp[tempLen] != '\0') tempLen++;
    //cout << tempLen;

    int row = 0;
    
    char c[LINE_MAX];
    while (ifs.getline(c, LINE_MAX)) {
        int col = 0;
        while (c[col] != '\0') {
            if (row == wantedRow && col == wantedCol) {
                ofs.write(temp, tempLen);
            }
            ofs << c[col];
            col++;
        }
        ofs << endl;
        row++;
    }
    ifs.close();
    ofs.close();
    ifs.open("temp2.txt");
    ofs.open("temp.txt");
    char cc;
    while (ifs.get(cc)) {
        ofs << cc;
    }
    ofs.close();
    ifs.close();
    cout << temp << " inserted into (" << wantedRow << ", " << wantedCol << ")" << endl;
    return;
}

void dlt() {
    ifstream fs;
    fs.open("temp.txt");
    ofstream ofs;
    ofs.open("temp2.txt");
    char delimiter[99];
    cin >> delimiter;

    int dLength = 0;
    while (delimiter[dLength] != '\0') {
        dLength++;
    }

    char now[LINE_MAX];
    while (fs.getline(now, LINE_MAX)) {
        int start = 0;
        int dStart = -1;
        int i = 0;
        while (now[i] != '\0') {
            //cout << now[i] << " " << delimiter << endl;
            if (dStart == -1) {
                if (now[i] == delimiter[0]) {
                    //cout << "Delimiter Check" << endl;
                    dStart = i;
                }
            }
            else {
                if (i - dStart == dLength) {
                    //cout << "Delimiter Complete" << endl;
                    for (int j = start; j < dStart; j++) {
                        ofs << now[j];
                    }
                    start = i;
                    dStart = -1;
                }
                if (now[i] != delimiter[i - dStart]) {
                    dStart = -1;
                }
            }

            i++;
        }
        //cout << "EndLine";
        for (int j = start; j < i; j++) {
            //cout << now[j];
            ofs << (char)now[j];
        }
        ofs << endl;
    }
    ofs.close();
    //cout << "Comp";
    fs.close();
    ofs.open("temp.txt", ios::out);
    fs.open("temp2.txt");
    char c;
    while (fs.get(c)) {
        ofs << c;
    }
    ofs.close();
    cout << "Delete " << delimiter << endl;
    return;
}

int main()
{
    ifstream fs;
    fstream temps;
    while (true) {
        char command[8];

        cin >> command;
        if (strcmp(command, "open")) { //Open
            //cout << "열기" << endl;
            char fileName[99];
            cin >> fileName;
            fs.open(fileName);
            temps.open("temp.txt", ios::out);
            //cout << temps.is_open();
            char c[LINE_MAX];
            while (fs.getline(c, LINE_MAX)) {
                temps << c << endl;
            }
            temps.close();
            temps.open("temp.txt", ios::in|ios::out);
            fs.clear();
            fs.seekg(0);
        }
        else if (strcmp(command, "exit")) { //Exit
            cout << "Exit the program" << endl;
            return 0;
        }
        else if (strcmp(command, "search")) { //Search
            if (fs.is_open() == false) {
                cout << "파일이 열려있지 않습니다." << endl;
                continue;
            }
            int** searched = new int*[99];
            for (int i = 0; i < 99; i++) {
                searched[i] = new int[2];
                searched[i][0] = -1;
                searched[i][1] = -1;
            }
            search(fs, searched);
            bool many = 0;
            for (int i = 0; i < 99; i++) {
                if (searched[i][0] == -1) break;
                if (many == 0) {
                    many++;
                }
                else {
                    cout << ", ";
                }
                cout << "(" << searched[i][0] << ", " << searched[i][1] << ")";
            }
            cout << endl;
            cout << "--------------------------" << endl;
        }
        else if (strcmp(command, "change")) { //Change
            if(fs.is_open() == false) {
                cout << "파일이 열려있지 않습니다." << endl;
                continue;
            }
            cout << "===change===" << endl;
            change();
            cout << "--------------------------" << endl;
        }
        else if (strcmp(command, "insert")) { //Insert
            if(fs.is_open() == false) {
                cout << "파일이 열려있지 않습니다." << endl;
                continue;
            }
            cout << "===insert===" << endl;
            insert();
            cout << "--------------------------" << endl;
            //cout << "삽입" << endl;
        }
        else if (strcmp(command, "delete")) { //Delete
            if (fs.is_open() == false) {
                cout << "파일이 열려있지 않습니다." << endl;
                continue;
            }
            cout << "===delete===" << endl;
            dlt();
            cout << "--------------------------" << endl;
            //cout << "삭제" << endl;
        }
        else if (strcmp(command, "save")) { //Save
            cout << "===save===" << endl;
            char outputFileName[101];
            cin >> outputFileName;
            ofstream ofs;
            ofs.open(outputFileName);
            ifstream ifs;
            ifs.open("temp.txt");
            char cc;
            while (ifs.get(cc)) {
                ofs << cc;
            }
            ofs.close();
            ifs.close();
            cout << "Save the file as \"" << outputFileName << "\"" << endl;
            cout << "--------------------------" << endl;
        }
        else {
            cout << "지정되지 않은 명령어입니다." << endl;
        }
        
    }
}
