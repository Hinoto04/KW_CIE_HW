#pragma once
#include "FlightData.h"
class BpTreeNode
{
private:
	BpTreeNode* pParent;
	BpTreeNode* pMostLeftChild;

public:
	BpTreeNode() {
		pParent = NULL;
		pMostLeftChild = NULL;
	}
	~BpTreeNode() {
	}

	void setMostLeftChild(BpTreeNode* pN) { pMostLeftChild = pN; }
	void setParent(BpTreeNode* pN) { pParent = pN; }

	BpTreeNode* getParent() { return pParent; }
	BpTreeNode* getMostLeftChild() { return pMostLeftChild; }

	virtual void setNext(BpTreeNode* pN) {}
	virtual void setPrev(BpTreeNode* pN) {}
	virtual BpTreeNode* getNext() { return NULL; }
	virtual BpTreeNode* getPrev() { return NULL; }

	virtual void insertDataMap(string n, FlightData* pN) {}
	virtual void insertIndexMap(string n, BpTreeNode* pN) {}
	virtual void deleteMap(string n) {}

	//OMG TOO MANY WARNINGS -> return local variable's address is equal to return nullptr;
	virtual map<string, BpTreeNode*>* getIndexMap() { return nullptr; }
	virtual map<string, FlightData*> *getDataMap() { return nullptr; }

};