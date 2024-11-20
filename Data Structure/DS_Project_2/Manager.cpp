#include "Manager.h"

vector<string> split(string& str, const string& deli) { //String Split Function to Recognition of Commmand
	vector<string> cuts;
	size_t pos = 0;
	string cut;
	while ((pos = str.find(deli)) != string::npos) {
		cut = str.substr(0, pos);
		cuts.push_back(cut);
		str.erase(0, pos + deli.length());
	}
	cuts.push_back(str);

	if (cuts[cuts.size() - 1].length() == 0) {
		cuts.pop_back();
	}

	return cuts;
}

Manager::Manager(int bpOrder) {
	ofs.open("log.txt", ios::app); //Log ofs Setting
	bp = new BpTree(&ofs, bpOrder);
	avl = new AVLTree();
}

Manager::~Manager() {

}

void Manager::run(const char* command_txt) {
	ifstream cmd;
	string tmp;
	int result = 0;
	cmd.open(command_txt);
	if (cmd.fail()) return; //File DoesNotExist
	else if (cmd.eof()) return; //File Empty
	while (getline(cmd, tmp)) {
		vector<string> cuts;
		cuts = split(tmp, "\t");
		if (tmp == "LOAD") { //LOAD
			result = this->LOAD();
			if (result) {
				ofs << "========LOAD========" << endl;
				ofs << "Success" << endl;
				ofs << "====================" << endl;
			}
			else printErrorCode(100);
		}
		else if (tmp == "VLOAD") { //VLOAD
			result = this->VLOAD();
			if (result) {
				ofs << "========VLOAD========" << endl;
				ofs << "Success" << endl;
				ofs << "====================" << endl;
			}
			else printErrorCode(200);
		}
		else if (cuts[0] == "ADD") { //ADD
			if (cuts.size() != 5) result = 0;
			else {
				result = this->ADD(cuts[1], cuts[2], cuts[3], cuts[4]);
			}
			if (!result) printErrorCode(300);
		}
		else if (cuts[0] == "SEARCH_BP") { //SEARCH B+ Tree
			if (cuts.size() == 2) {
				result = this->SEARCH_BP(cuts[1]);
			}
			else if(cuts.size() == 3) {
				result = this->SEARCH_BP(cuts[1], cuts[2]);
			}
			else result = 0;
			if (!result) printErrorCode(400);
		}
		else if (cuts[0] == "SEARCH_AVL") { //SEARCH AVL Tree
			if (cuts.size() != 2) result = 0;
			else if (this->avl->IsEmpty()) result = 0;
			else {
				result = this->SEARCH_AVL(cuts[1]);
			}
			if (!result) printErrorCode(500);
		}
		else if (cuts[0] == "VPRINT") { //VPRINT
			result = this->VPRINT(cuts[1]);
			if (!result) printErrorCode(600);
		}
		else if (tmp == "PRINT_BP") { //PRINT B+ Tree
			if (this->bp->getRoot() == nullptr) result = 0;
			else result = this->PRINT_BP();
			if (!result) printErrorCode(700);
		}
		else if(tmp == "EXIT") {
			ofs << "========EXIT========" << endl;
			ofs << "Success" << endl;
			ofs.close();
			exit(0);
		}
	}
	cin >> tmp;
	return;
}

bool Manager::LOAD() {

	ifstream ifs;
	ifs.open("input_data.txt");
	if (ifs.fail()) return false; //File DoesNotExist
	else if(ifs.eof()) return false; //File Empty
	else if (bp->getRoot() != nullptr) return false; //B+ Already Loaded
	while(!ifs.eof()) {
		string AName, FNum, Dest, Status;
		int Seats;
		ifs >> AName;
		ifs >> FNum;
		ifs >> Dest;
		ifs >> Seats;
		ifs >> Status;
		FlightData* fd = new FlightData();
		fd->SetAirlineName(AName);
		fd->SetFlightNumber(FNum);
		fd->SetDestination(Dest);
		fd->SetNumberofSeats(Seats);
		fd->SetStatus(Status);
		cout << "Insert Try" << endl;
		this->bp->Insert(fd);
		cout << "Insert Success" << endl;
	}
	return true;
}

bool Manager::VLOAD() {
	if (avl->IsEmpty()) return false;
	avl->GetVector(Print_vector);
	return true;
}

bool Manager::ADD(string AName, string FName, string Dest, string Status) {
	FlightData* afd = avl->Search(FName); //Alread AVL Table
	if (afd != nullptr) return false;

	BpTreeNode* n = bp->searchDataNode(FName);
	FlightData* fd = nullptr;
	map<string, FlightData*>* m = n->getDataMap();
	for (auto iter = m->begin(); iter != m->end(); ++iter) {
		if (FName == iter->first) {
			fd = iter->second;
		}
	}
	if (fd == nullptr) {//B+ Tree Haven't This Data
		fd = new FlightData();
		int seats = 0;

		if (AName == "KoreanAir" || AName == "ASIANA") seats = 7;
		else if (AName == "JEJU" || AName == "JeanAir") seats = 5;
		else seats = 6;
		fd->SetAirlineName(AName);
		fd->SetFlightNumber(FName);
		fd->SetDestination(Dest);
		fd->SetNumberofSeats(seats);
		fd->SetStatus(Status);
		bp->Insert(fd);
		return true;
	} 
	cout << "Not New FlightData" << endl;
	
	cout << "Status Check" << endl;
	cout << fd->GetFlightNumber() << endl;
	cout << fd->GetStatus() << endl;
	//B+ Tree Have This Data
	cout << (fd->GetStatus() == string("Cancelled")) << endl;
	if (fd->GetStatus() == "Cancelled" && Status == "Boarding") {
		if (fd->GetNumberofSeats() > 0) {
			fd->SetSeatsDec();
			fd->SetStatus(Status);
		}
		else return false;
	}
	else if ((fd->GetStatus() == "Delayed") && (Status == "Delayed")) {
		fd->SetSeatsDec(); //Delayed Can Dec
	}
	else if (fd->GetStatus() == "Boarding") {
		if (Status == "Boarding") { //Boarding Can Dec
			fd->SetSeatsDec();
		}
		else if (Status == "Cancelled") {
			fd->SetStatus(Status);
		}
		else return false;
	}
	else return false;

	cout << "Success" << endl;

	if (fd->GetNumberofSeats() == 0) {
		cout << "Insert to AVL" << endl;
		avl->Insert(fd);
		return true;
	}
	return false;
}

bool Manager::PRINT_BP() {
	bp->Print();
	return true;
}

bool Manager::SEARCH_BP(string name) {
	return bp->SearchModel(name);
}

bool Manager::SEARCH_BP(string start, string end) {
	return bp->SearchRange(start, end);
}

bool Manager::SEARCH_AVL(string name) {
	FlightData* fd = avl->Search(name);
	if (fd == nullptr) return false;
	ofs << "========== SEARCH_AVL ==========" << endl;
	ofs << fd->GetFlightNumber() << " | " << fd->GetAirlineName() << " | " << fd->GetDestination() << " | ";
	ofs << fd->GetNumberofSeats() << " | " << fd->GetStatus() << endl;
	ofs << "===========================" << endl << endl;
	return true;
}

bool CompareA(FlightData* f1, FlightData* f2) {
	if (f1->GetAirlineName() > f2->GetAirlineName()) return false;
	else if (f1->GetAirlineName() < f2->GetAirlineName()) return true;
	else {
		if (f1->GetDestination() > f2->GetDestination()) return false;
		else if (f1->GetDestination() < f2->GetDestination()) return true;
		else {
			if (f1->GetStatus() > f2->GetStatus()) return true;
			else return true;
		}
	}
}

bool CompareB(FlightData* f1, FlightData* f2) {
	if (f1->GetDestination() > f2->GetDestination()) return false;
	else if (f1->GetDestination() < f2->GetDestination()) return true;
	else {
		if (f1->GetStatus() > f2->GetStatus()) return false;
		else if (f1->GetStatus() < f2->GetStatus()) return true;
		else {
			if (f1->GetAirlineName() > f2->GetAirlineName()) return true;
			else return false;
		}
	}
}

bool Manager::VPRINT(string type_) {
	if (avl->IsEmpty()) return false;
	if (type_ == "A") {
		sort(Print_vector.begin(), Print_vector.end(), CompareA);
		ofs << "========== VPRINT A ==========" << endl;
	}
	else {
		sort(Print_vector.begin(), Print_vector.end(), CompareB);
		ofs << "========== VPRINT B ==========" << endl;
	}
	for (int i = 0; i < Print_vector.size();i++) {
		FlightData* fd = Print_vector[i];
		ofs << fd->GetFlightNumber() << " | " << fd->GetAirlineName() << " | " << fd->GetDestination() << " | ";
		ofs << fd->GetNumberofSeats() << " | " << fd->GetStatus() << endl;
	}
	ofs << "===========================" << endl << endl;
	return true;
}

void Manager::printErrorCode(int n) {
	ofs << "========== ERROR ==========" <<endl;
	ofs << n << endl;
	ofs << "===========================" << endl << endl;
}

