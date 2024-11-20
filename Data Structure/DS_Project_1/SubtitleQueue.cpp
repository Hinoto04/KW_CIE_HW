#include "SubtitleQueue.h"
#include <string>
using namespace std;

SubtitleQueue::SubtitleQueue()
{
    
}
SubtitleQueue::~SubtitleQueue()
{

}

bool SubtitleQueue::IsEmpty() //front == rear -> Empty
{
	if(this->front == this->rear) return true; 
    return false;
}
bool SubtitleQueue::IsFull() //rear+1 == front -> Full (One NULL Element)
{
	if((this->rear + 1)%(MAX+1) == this->front) return true;
    return false;
}
void SubtitleQueue::Push(int h, int m, int s, string str)
{
	if(!this->IsFull()) { //Full Check (One NULL Element is needed)
        this->rear = (this->rear + 1)%(MAX+1); //move rear to next position;
        this->queue[this->rear].sub.set(h, m, s, str); //rear position subtitle set
        return;
    } else {
        exit(-1);
    }
    return;
}
SubtitleQueueNode SubtitleQueue::Pop()
{
	this->front = (this->front+1)%(MAX+1);
    return this->queue[this->front];
}
SubtitleQueueNode SubtitleQueue::Front()
{
	return this->queue[(this->front+1)%(MAX+1)];
}
