#include "Manager.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

//string split function
vector<string> split(string& str, const string& deli) {
    vector<string> cuts;
    size_t pos = 0;
    string cut;
    while((pos = str.find(deli)) != string::npos) {
        cut = str.substr(0, pos);
        cuts.push_back(cut);
        str.erase(0, pos + deli.length());
    }
    cuts.push_back(str);
    
    if(cuts[cuts.size()-1].length() == 0) {
        cuts.pop_back();
    }

    return cuts;
}

int timeInSeconds(int h, int m, int s) { //time to seconds
    return h*3600 + m*60 + s;
}

Manager::Manager()
{

}
Manager::~Manager()
{

}

void Manager::Run(const char* command)
{
    // Open command & log file
    fcmd.open(command);
    flog.open("log.txt");
    if (!fcmd)
    {
        flog << "Fail to open command file" << endl;
        exit(-1);
    }

    // Read and Run command
    string cmd; //temp commandline
    while(getline(fcmd, cmd)) {
        //cout << cmd << endl;
        int result = 0;

        vector<string> cuts; //ARG CUTS
        cuts = split(cmd, " ");
        
        if(cmd == "LOAD") {
            if(cuts.size() != 1) { //ARGS CHECK
                result = -1;
            } else {
                result = this->load();
            }
            if(result == 0) flog << "===============\n" << endl;
            else PrintErrorCode(100);

        } else if(cmd == "QPOP") { //QPOP COMMAND
            if(cuts.size() != 1) { //ARGS CHECK
                result = -1;
            } else {
                result = this->qpop();
            }
            if(result == 0) PrintSuccess("QPOP");
            else PrintErrorCode(200);

        } else if(cuts[0] == "PRINT") { //PRINT COMMAND
            if(cuts.size() > 2) { //ARGS CHECK
                result = -1;
            } else if(cuts.size() == 2) { //IF HAVE ARG
                result = this->print(stoi(cuts[1]));
            } else {
                result = this->print();
            }
            if(result == 0) flog << "===============\n" << endl;
            else PrintErrorCode(300);

        } else if(cuts[0] == "SECTION") {
            //cout << cuts.size() << endl;
            if(cuts.size() > 4 || cuts.size() < 4) { //ARGS CHECK
                result = -1;
            } else {
                int num = stoi(cuts[1]);
                vector<string> timecuts = split(cuts[2], ":");
                int start_time = stoi(timecuts[0])*3600 + stoi(timecuts[1])*60 + stoi(timecuts[2]);
                timecuts = split(cuts[3], ":");
                int end_time = stoi(timecuts[0])*3600 + stoi(timecuts[1])*60 + stoi(timecuts[2]);
                result = this->section(num, start_time, end_time);
            }

            if(result == 0) PrintSuccess("SECTION");
            else PrintErrorCode(400);

        } else if(cuts[0] == "DELETE") {
            if(cuts.size() > 3 || cuts.size() < 3) { //ARGS CHECK
                result = -1;
            } else {
                vector<string> timecuts = split(cuts[2], ":");
                int time = stoi(timecuts[0])*3600 + stoi(timecuts[1])*60 + stoi(timecuts[2]);
                if(cuts[1] == "UNDER") { //ARG CHECK TO CHANGE MODE
                    result = this->del(0, time);
                } else {
                    result = this->del(1, time);
                }
            }
            if(result == 0) PrintSuccess("DELETE");
            else PrintErrorCode(500);

        } else if(cmd == "EXIT") {
            PrintSuccess("EXIT");
            exit(0);
        }
    }

    fcmd.close();
    flog.close();
    return;
}

void Manager::PrintSuccess(const char* cmd)
{
    flog << "===== " << cmd << " =====" << endl;
    flog << "Success" << endl;
    flog << "===============\n" << endl;
}
void Manager::PrintErrorCode(int num)
{
    flog << "===== ERROR =====" << endl;
    flog << num << endl;
    flog << "===============\n" << endl;
}

// LOAD
int Manager::load() {
    ifstream fsub; //subtitle file stream
    fsub.open("subtitle.txt");

    if(!fsub) { //file not found
        return -1;
    }
    if(!(this->q.IsEmpty())) { //already loaded
        return -1;
    }
    flog << "===== LOAD =====" << endl;
    string str;
    while(getline(fsub, str)) {
        int h = stoi(str.substr(0, 2)); //00:
        int m = stoi(str.substr(3, 2)); //00:|00:
        int s = stoi(str.substr(6, 2)); //00:00:|00
        //int time = timeInSeconds(h, m, s);
        string content = str.substr(9); //00:00:00 |

        if(this->q.IsFull()) return -1;
        this->q.Push(h, m, s, content);

        flog << setfill('0');
        flog << setw(2) << h << ':';
        flog << setw(2) << m << ':';
        flog << setw(2) << s << " - " << content << endl;
    }

    return 0;
}
// QPOP
int Manager::qpop() {
    if(this->q.IsEmpty()) exit(-1);
    while(!this->q.IsEmpty()) {
        this->bst.insert(this->q.Pop().sub);
        //this->bst.print(cout);
    }
    return 0;
}
// PRINT
int Manager::print() {
    if(!this->bst.getRoot()) return -1;
    flog << "===== PRINT =====" << endl;
    this->bst.print(flog);
    return 0;
}
int Manager::print(int number) { //ARG PRINT
    SectionListNode* node = this->l.search(number);
    if(!node) return -1;
    flog << "===== PRINT =====" << endl;
    node->print(flog);
    return 0;
}
// SECTION
int Manager::section(int number, int start, int end) {
    
    SectionListNode* newNode = new SectionListNode(number);
    newNode->sets(this->bst.getRoot(), start, end);

    if(newNode->size() == 0) {
        return -1;
    } else {
        l.insert(newNode);
        return 0;
    }
    //newNode->print(cout);
    
}
// DELETE
int Manager::del(int mode, int time) {
    int result = 0;
    if(mode == 0) { //UNDER
        result = this->bst.delUnder(time);
    } else {
        result = this->bst.delOne(time);
    }
    return result;
}
