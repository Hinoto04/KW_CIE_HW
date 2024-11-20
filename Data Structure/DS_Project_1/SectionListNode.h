#pragma once
#include "SubtitleListNode.h"
#include "SubtitleBSTNode.h"
#include "Subtitle.h"
#include <iostream>

class SectionListNode
{
private:
	int number; //Section Number
	SectionListNode* next; //Next Section Node
	SubtitleListNode* head; //Content List Head

public:
	SectionListNode(int number) : next(nullptr) {
		this->number = number;
		this->head = nullptr;
	}
	~SectionListNode() {}

	SubtitleListNode* getHead() {
		return this->head;
	}

	void sets(SubtitleBSTNode* now, int start, int end) {
		if(!now) return;
		if(now->sub.toSeconds() > start) this->sets(now->getLeft(), start, end);
		if(now->sub.toSeconds() >= start && now->sub.toSeconds() <= end) insert(now->sub);
		if(now->sub.toSeconds() < end) this->sets(now->getRight(), start, end);
		return;
	}

	void insert(Subtitle s) {
		if(!this->head) {
			this->head = new SubtitleListNode(s);
			return;
		}
		SubtitleListNode* now = this->head;
		while(now->getNext()) {
			now = now->getNext();
		}
		now->setNext(new SubtitleListNode(s));
	}

	int size() {
		SubtitleListNode* now = this->head;
		int count = 0;
		while(now) {
			now = now->getNext();
			count++;
		}
		return count;
	}

	void print(ostream& os) {
		SubtitleListNode* now = this->head;
		while(now) {
			os << setfill('0');
			os << setw(2) << now->sub.h << ':';
			os << setw(2) << now->sub.m << ':';
			os << setw(2) << now->sub.s << " - ";
			os << now->sub.str << endl;
			now = now->getNext();
		}
		return;
	}

	SectionListNode*	getNext()		 	{ return next; }
	void setNext(SectionListNode* next)	 					{ this->next = next; }

	int getNumber() { return this->number; }
};
