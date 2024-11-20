#include "BpTree.h"

bool BpTree::Insert(FlightData* newData){
	//Empty to Root
	cout << "Insert Start" << endl;
	cout << newData->GetFlightNumber() << endl;
	if (this->root == nullptr) {
		this->root = new BpTreeDataNode();
		this->root->insertDataMap(newData->GetFlightNumber(), newData);
		return true;
	}
	cout << "NOT ROOT" << endl;
	// Position Search
	BpTreeNode* p = nullptr;
	BpTreeNode* cur = this->root;
	while(true) {
		cout << "Check" << endl;
		map<string, BpTreeNode*>* m = cur->getIndexMap();
		if(m == nullptr) break; //is DataNode
		p = cur;
		cur = cur->getMostLeftChild(); //from MostLeft
		for (auto iter = m->begin(); iter != m->end(); ++iter) {
			if(newData->GetFlightNumber() > iter->first) {
				cur = iter->second;
			}
		}
	}
	cout << "Position Founded" << endl;
	if (cur == nullptr) { //is MostLeftChild that nullptr
		BpTreeDataNode* newNode = new BpTreeDataNode();
		newNode->insertDataMap(newData->GetFlightNumber(), newData);
		p->setMostLeftChild(newNode);
		newNode->setParent(p);
		return true;
	}
	cur->insertDataMap(newData->GetFlightNumber(), newData);
	cout << "Map Inserted" << endl;
	if(this->excessDataNode(cur)) {
		this->splitDataNode(cur);
	}
	cout << "Successfully Inserted!" << endl;
	return true;
}

bool BpTree::excessDataNode(BpTreeNode* pDataNode) {
	if (pDataNode->getDataMap()->size() > order - 1) return true;//order is equal to the number of elements 
	else return false;
}

bool BpTree::excessIndexNode(BpTreeNode* pIndexNode) {
	if (pIndexNode->getIndexMap()->size() > order - 1)return true;//order is equal to the number of elements 
	else return false;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode) {
	cout << "Split Data Node" << endl;
	map<string, FlightData*>* m = pDataNode->getDataMap();
	BpTreeDataNode* newRight = new BpTreeDataNode(); //Second and Third Value
	newRight->setPrev(pDataNode);
	newRight->setNext(pDataNode->getNext());
	pDataNode->setNext(newRight);
	for (auto iter = m->begin(); iter != m->end(); ++iter) { //copy all things
		newRight->insertDataMap(iter->first, iter->second);
	}
	m->clear(); //clear original
	pDataNode->insertDataMap(newRight->getDataMap()->begin()->first, 
		newRight->getDataMap()->begin()->second); //add first map to original
	newRight->getDataMap()->erase(newRight->getDataMap()->begin()->first); //erase first from new map

	cout << "Splitted" << endl;
	BpTreeNode* p = pDataNode->getParent();
	if (p == nullptr) {
		cout << "New Root Making" << endl;
		p = new BpTreeIndexNode();
		p->setMostLeftChild(pDataNode);
		p->insertIndexMap(m->begin()->first, newRight);
		pDataNode->setParent(p);
		newRight->setParent(p);
		this->root = p;
	}
	else {
		p->insertIndexMap(newRight->getDataMap()->begin()->first, newRight);
		newRight->setParent(p);
		if (this->excessIndexNode(p)) {
			splitIndexNode(p);
		}
	}
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode) { //Same to SplitDataNode
	cout << "SplitIndexNode" << endl;
	map<string, BpTreeNode*>* m = pIndexNode->getIndexMap();
	auto iter = m->begin(); //First Node
	string temp = iter->first;
	BpTreeNode* tempNode = iter->second; 
	iter++; //Second Node
	BpTreeNode* mlc = iter->second;
	iter++; //Third Node
	BpTreeIndexNode* right = new BpTreeIndexNode();
	right->setMostLeftChild(mlc);
	right->insertIndexMap(iter->first, iter->second);
	iter = m->begin(); iter++; //Second Node;
	BpTreeNode* p = pIndexNode->getParent();
	if (p == nullptr) {
		cout << "New Root Making idx" << endl;
		p = new BpTreeIndexNode();
		p->setMostLeftChild(pIndexNode);
		p->insertIndexMap(iter->first, right);
		m->clear();
		pIndexNode->insertIndexMap(temp, tempNode);
		pIndexNode->setParent(p);
		right->setParent(p);
		this->root = p;
	}
	else {
		p->insertIndexMap(iter->first, right);
		right->setParent(p);
		if (this->excessIndexNode(p)) {
			splitIndexNode(p);
		}
	}
}

BpTreeNode* BpTree::searchDataNode(string name) {
	cout << "SearchDataNode" << endl;
	cout << name << endl;
	BpTreeNode* cur = this->root;
	while (true) {
		map<string, BpTreeNode*>* m = cur->getIndexMap();
		if (m == nullptr) break; //is DataNode
		cur = cur->getMostLeftChild(); //from MostLeft
		map<string, FlightData*>* mm = cur->getDataMap();
		if (mm == nullptr || mm->begin()->first != name) {
			for (auto iter = m->begin(); iter != m->end(); ++iter) {
				cout << name << " " << iter->first << endl;
				if (name >= iter->first) {
					cur = iter->second;
				}
			}
		}
		
	}
	if (cur != nullptr) {
		cout << cur->getDataMap()->begin()->first << endl;
	}
	return cur;
}

bool BpTree::SearchModel(string model_name) {
	FlightData* fd = nullptr;
	BpTreeNode* cur = searchDataNode(model_name);
	map<string, FlightData*>* m = cur->getDataMap();
	for (auto iter = m->begin(); iter != m->end(); ++iter) {
		if (iter->first == model_name) fd = iter->second;
	}
	if (fd == nullptr) return false;
	*fout << "========SEARCH_BP========" << endl;
	*fout << fd->GetFlightNumber() << " | " << fd->GetAirlineName() << " | " << fd->GetDestination() << " | ";
	*fout << fd->GetNumberofSeats() << " | " << fd->GetStatus() << endl;
	*fout << "====================" << endl;
	return true;
}

bool BpTree::SearchRange(string start, string end) {
	BpTreeNode* cur = searchDataNode(start);
	int count = 0;
	while (cur != nullptr) {
		if (cur->getDataMap()->begin()->first > end) break;
		map<string, FlightData*>* m = cur->getDataMap();
		for (auto iter = m->begin(); iter != m->end(); ++iter) {
			if (iter->first > end) break;
			if (iter->first > start)
			count++;
		}
		cur = cur->getNext();
	}
	if (count < 0) return false;
	*fout << "========SEARCH_BP========" << endl;
	cur = searchDataNode(start);
	while (cur != nullptr) {
		if (cur->getDataMap()->begin()->first > end) break;
		map<string, FlightData*>* m = cur->getDataMap();
		for (auto iter = m->begin(); iter != m->end(); ++iter) {
			if (iter->first > end) break;
			if (iter->first > start) {
				FlightData* fd = iter->second;
				*fout << fd->GetFlightNumber() << " | " << fd->GetAirlineName() << " | " << fd->GetDestination() << " | ";
				*fout << fd->GetNumberofSeats() << " | " << fd->GetStatus() << endl;
			}
		}
		cur = cur->getNext();
	}
	*fout << "====================" << endl;
	return true;
}

void BpTree::Print() {
	BpTreeNode* cur = this->root;
	if (cur == nullptr) {
		cout << "Nothing in B+Tree" << endl;
	}
	*fout << "========PRINT_BP========" << endl;
	while (true) {
		if (cur->getIndexMap() == nullptr) break;
		if (cur->getMostLeftChild() != nullptr) {
			cur = cur->getMostLeftChild();
		}
		else {
			cur = cur->getIndexMap()->begin()->second;
		}
	}
	while (cur != nullptr) {
		//*fout << "curNext" << endl;
		map<string, FlightData*>* m = cur->getDataMap();
		for (auto iter = m->begin(); iter != m->end(); ++iter) {
			cout << iter->first << endl;
			FlightData* fd = iter->second;
			*fout << fd->GetFlightNumber() << " | " << fd->GetAirlineName() << " | " << fd->GetDestination() << " | ";
			*fout << fd->GetNumberofSeats() << " | " << fd->GetStatus() << endl;
		}
		cur = cur->getNext();
	}
	*fout << "====================" << endl;
}
