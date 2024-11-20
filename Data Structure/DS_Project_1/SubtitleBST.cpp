#include "SubtitleBST.h"

SubtitleBST::SubtitleBST() : root(nullptr)
{

}
SubtitleBST::~SubtitleBST()
{

}

SubtitleBSTNode* SubtitleBST::getRoot()
{
	return this->root;
}

SubtitleBSTNode* SubtitleBST::recursiveSearch(SubtitleBSTNode* now, int timeToSecond) {
	if(!now) return nullptr;
	if(now->sub.toSeconds() == timeToSecond) return now; 
	if(now->sub.toSeconds() > timeToSecond) return this->recursiveSearch(now->getLeft(), timeToSecond);
	return this->recursiveSearch(now->getRight(), timeToSecond);
}

void SubtitleBST::recursivePrint(SubtitleBSTNode* now, ostream& os) {
	if(!now) return;
	//In-Order Print
	this->recursivePrint(now->getLeft(), os);
	os << setfill('0');
	os << setw(2) << now->sub.h << ':';
	os << setw(2) << now->sub.m << ':';
	os << setw(2) << now->sub.s << " - ";
	os << now->sub.str << endl;
	this->recursivePrint(now->getRight(), os);
}

SubtitleBSTNode* SubtitleBST::recursiveDelete(SubtitleBSTNode* now, SubtitleBSTNode* parent, int time) {
	if(!now) return nullptr;

	//find target
	SubtitleBSTNode* target = nullptr;
	if(now->sub.toSeconds() > time) {
		target = this->recursiveDelete(now->getLeft(), now, time);
	} else if(now->sub.toSeconds() < time) {
		target = this->recursiveDelete(now->getRight(), now, time);
	} else {
		target = now; //Return target to Delete after logic

		if(!now->getLeft() && !now->getRight()) { //Have no child
			if(parent->getLeft() == target) parent->setLeft(nullptr);
			else parent->setRight(nullptr);
		} else if(now->getLeft() && !now->getRight()) { //Have left child
			if(!parent) { //if target is root
			this->root = target->getLeft();
			} else {
				if(parent->getLeft() == target) parent->setLeft(nullptr);
				else parent->setRight(nullptr);
			}
		} else if(!now->getLeft() && now->getRight()) { //Have right child
			if(!parent) { //if target is root
				this->root = target->getRight();
			} else {
				if(parent->getLeft() == target) parent->setLeft(nullptr);
				else parent->setRight(nullptr);
			}
		} else { //Have all child
			SubtitleBSTNode* minInRight = target->getRight();
			while(minInRight->getLeft()) {
				minInRight = minInRight->getLeft();
			}
			minInRight = this->recursiveDelete(now->getRight(), now, minInRight->sub.toSeconds());
			now->sub = minInRight->sub;
			target = minInRight;
		}
	}

	return target;
}

// Insert
void SubtitleBST::insert(Subtitle sub) {
	if(!this->root) { //If no root
		this->root = new SubtitleBSTNode(sub);
		return;
	}
	SubtitleBSTNode* now = this->root;
	SubtitleBSTNode* parent;
	while(now) { //Find Insert Position
		parent = now;
		if(parent->sub.toSeconds() > sub.toSeconds()) {
			now = now->getLeft();
		} else {
			now = now->getRight();
		}
	}
	if(parent->sub.toSeconds() > sub.toSeconds()) {
		parent->setLeft(new SubtitleBSTNode(sub));
	} else {
		parent->setRight(new SubtitleBSTNode(sub));
	}
	return;
}
// Print
void SubtitleBST::print(ostream& os) {
	this->recursivePrint(this->root, os);
}
// Search
SubtitleBSTNode* SubtitleBST::search(int timeToSecond) {
	return this->recursiveSearch(this->root, timeToSecond);
}
// Delete Under
int SubtitleBST::delUnder(int timeToSecond) {
	SubtitleBSTNode* target = this->root;
	int count = 0;
	while(true) { //Delete Min Value while Min Value is lower than target
		SubtitleBSTNode* minNode = this->root;
		while(minNode->getLeft()) {
			minNode = minNode->getLeft();
		}
		if(minNode->sub.toSeconds() > timeToSecond) break;
		this->delOne(minNode->sub.toSeconds());
		count++;
	}
	if(count != 0) return 0;
	else return -1;
}
// Delete One Node
int SubtitleBST::delOne(int timeToSecond) {
	//cout << "DELONE" << endl;
	if(this->search(timeToSecond) == nullptr) {
		return -1;
	}
	SubtitleBSTNode* target = this->recursiveDelete(this->root, nullptr, timeToSecond);
	delete target;
	return 0;
}
