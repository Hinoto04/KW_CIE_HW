#pragma once
#include "Subtitle.h"

class SubtitleListNode
{
private:

	SubtitleListNode*	next; //Next Content Node

public:
	Subtitle sub;
	SubtitleListNode(Subtitle s) : next(nullptr) {
		this->sub = s;
	}
	~SubtitleListNode() {}

	SubtitleListNode*	getNext()			{ return next; }

	void setNext(SubtitleListNode* next)	 	{ this->next = next; }
};
