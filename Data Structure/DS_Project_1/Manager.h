#pragma once
#include "SubtitleQueue.h"
#include "SubtitleBST.h"
#include "SectionList.h"
#include "Subtitle.h"
#include <fstream>
#include <string>
using namespace std;

class Manager
{
private:

	ifstream		fcmd;
	ofstream		flog;

	SubtitleQueue q;
	SubtitleBST bst;
	SectionList l;

public:
	Manager();
	~Manager();

	void Run(const char* command);

	void PrintSuccess(const char* cmd);
	void PrintErrorCode(int num);

	// LOAD
	int load();
	// QPOP
	int qpop();
	// PRINT
	int print();
	int print(int number);
	// SECTION
	int section(int number, int start, int end); //start, end is time in seconds
	// DELETE
	int del(int mode, int time); //time is time in seconds
	//mode EQUAL -> 0
	//mode UNDER -> -1
};
