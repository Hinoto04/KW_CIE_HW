#include "SectionList.h"
#include "SubtitleListNode.h"
#include "SubtitleBST.h"

SectionList::SectionList()
{
	this->head = nullptr;
}
SectionList::~SectionList()
{
	return;
}

SectionListNode* SectionList::getHead()
{
	return head;
}

// Insert
void SectionList::insert(SectionListNode* newNode) {
	if(!this->head) {
		this->head = newNode;
		return;
	}
	SectionListNode* now = this->head;
	while(now->getNext() != nullptr) { //To Last Node
		now = now->getNext();
	}
	now->setNext(newNode);
	return;
}
// Search
SectionListNode* SectionList::search(int number) {
	SectionListNode* now = this->head;
	while(true) {
		if(now == nullptr) {
			return nullptr;
		}
		if(now->getNumber() == number) {
			return now;
		}
		now = now->getNext();
	}
	
}