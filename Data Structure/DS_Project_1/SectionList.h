#pragma once
#include "SectionListNode.h"

class SectionList
{
private:
	SectionListNode* head; //Section List Head

public:
	SectionList();
	~SectionList();

	SectionListNode* getHead();

	// Insert
	void insert(SectionListNode* node);
	// Search
	SectionListNode* search(int number);
};
