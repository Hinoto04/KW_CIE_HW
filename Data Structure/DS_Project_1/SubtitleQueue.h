#pragma once
#include "SubtitleQueueNode.h"
#define MAX 100

#include <string>
using namespace std;

class SubtitleQueue
{
private:
	SubtitleQueueNode queue[MAX+1]; //Circular Queue
	int front = 0;
	int rear = 0;

public:
	SubtitleQueue();
	~SubtitleQueue();

	bool IsEmpty();
	bool IsFull();
	void Push(int h, int m, int s, string str);
	SubtitleQueueNode Pop();
	SubtitleQueueNode Front();
};
