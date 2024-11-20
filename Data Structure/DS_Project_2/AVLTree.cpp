#include "AVLTree.h"

bool AVLTree::Insert(FlightData* pFlightData){
	AVLNode* pLast = nullptr; //parent of Last
	AVLNode* last = this->root; //Last +-1 Node
	AVLNode* p = nullptr; //parent of cur
	AVLNode* cur = this->root; //cursor, current
	AVLNode* rootSub = nullptr;
	AVLNode* newNode = new AVLNode(); //
	newNode->setFlightData(pFlightData);
	if (cur == nullptr) {
		this->root = newNode;
		return true;
	}
	while (cur != nullptr) {
		if (cur->getBF() != 0) {
			last = cur;
			pLast = p;
		}
		p = cur;
		if (cur->getFlightData()->GetFlightNumber() < pFlightData->GetFlightNumber()) cur = cur->getRight();
		else cur = cur->getLeft();
	}
	if (p->getFlightData()->GetFlightNumber() < pFlightData->GetFlightNumber()) p->setRight(newNode);
	else p->setLeft(newNode);
	
	cout << "Balance Check" << endl;
	//Tree Balance Check
	int d;
	AVLNode* y, *z; //ToRotation
	if (last->getFlightData()->GetFlightNumber() < pFlightData->GetFlightNumber()) {
		y = cur = last->getRight();
		d = -1;
	}
	else {
		y = cur = last->getLeft();
		d = 1;
	}

	while (cur != newNode) {
		if (cur->getFlightData()->GetFlightNumber() < pFlightData->GetFlightNumber()) {
			cur->setBF(-1);
			cur = cur->getRight();
		}
		else {
			cur->setBF(1);
			cur = cur->getLeft();
		}
	}

	if (last->getBF() == 0 || last->getBF() + d == 0) { //Need to Rotation?
		last->setBF(last->getBF() + d);
		return true;
	}
	cout << "Need to Rotate" << endl;
	//Rotation
	cout << y->getBF() << endl;
	if (d == 1) { //L
		if (y->getBF() == 1) { //LL
			cout << "LL" << endl;
			last->setLeft(y->getRight());
			y->setRight(last);
			last->setBF(0);
			y->setBF(0);
			rootSub = y;
		}
		else { //LR
			cout << "LR" << endl;
			z = y->getRight();
			y->setRight(z->getLeft());
			last->setLeft(z->getRight());
			z->setLeft(y);
			z->setRight(last);
			if (z->getBF() == 0) { y->setBF(0); last->setBF(0); }
			else if (z->getBF() == 1) { last->setBF(-1); y->setBF(0); }
			else { y->setBF(1); last->setBF(0); }
			z->setBF(0);
			rootSub = z;
		}
	}
	else { //R
		if (y->getBF() == -1) { //RR
			cout << "RR" << endl;
			last->setRight(y->getLeft());
			y->setLeft(last); 
			last->setBF(0); 
			y->setBF(0);
			rootSub = y;
		}
		else { //RL
			cout << "RL" << endl;
			z = y->getLeft();
			y->setLeft(z->getRight());
			last->setRight(z->getLeft());
			z->setRight(y);
			z->setLeft(last);
			if (z->getBF() == 0) { y->setBF(0); last->setBF(0); }
			else if (z->getBF() == 1) { y->setBF(-1); last->setBF(0); }
			else { last->setBF(1); y->setBF(0); }
			z->setBF(0); rootSub = z;
		}
	}

	if (pLast == nullptr) this->root = rootSub;
	else if (last == pLast->getLeft()) pLast->setLeft(rootSub);
	else pLast->setRight(rootSub);
	return true;
}

void AVLTree::GetVector(vector<FlightData*>& v){
	if (v.size() > 0) v.clear(); //if element in vector -> clear
	queue<AVLNode*> q;
	AVLNode* cur = this->root;
	cout << cur << endl;
	q.push(cur);
	while (!q.empty()) {
		cur = q.front();
		if (cur->getLeft() != nullptr) q.push(cur->getLeft());
		if (cur->getRight() != nullptr) q.push(cur->getRight());
		v.push_back(cur->getFlightData());
		q.pop();
	}
}

FlightData* AVLTree::Search(string name){
	AVLNode* cur = this->root;
	while (cur != nullptr) {
		if (cur->getFlightData()->GetFlightNumber() == name) break;
		if (cur->getFlightData()->GetFlightNumber() < name) cur = cur->getRight();
		else cur = cur->getLeft();
	}
	if (cur == nullptr) return nullptr;
	return cur->getFlightData();
}

