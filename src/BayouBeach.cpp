#include "BayouBeach.h"
using namespace std;

BayouBeach::BayouBeach(string name, Coordinates coords, unsigned int maxCapacity, bool blueFlag, const vector <Service> &services, double usableAquaticArea)
	:Beach(name, coords, maxCapacity, blueFlag, services), usableAquaticArea(usableAquaticArea){}

double BayouBeach::getUsableAquaticArea() const {
	return usableAquaticArea;
}

void BayouBeach::setUsableAquaticArea(double usableAquaticArea) {
	this->usableAquaticArea = usableAquaticArea;
}

void BayouBeach::print(ostream &o) {
	Beach::print(o);
	o << "Usable aquatic area: " << usableAquaticArea << endl;
}

void BayouBeach::modifyUsableAquaticArea() {
	double uaa;
	cout << "What is the bayou's usable aquatic area? " << endl;
	while (true) {
		cin >> uaa;
		if (cin.fail() || uaa <= 0) {
			cout << "Invalid usable aquatic area, please insert a valid usable aquatic area (positive decimal)." << endl;
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Setting the new max depth
	usableAquaticArea = uaa;
}

void BayouBeach::modifyBeach(){
	//Fields available to modify:
	//From Beach:
	//name, coordinates, max capacity, blue flag and services
	//From BayouBeach:
	//usable aquatic area
	int input;
	cout << "What do you want to modify?" << endl;
	cout << "1 Name" << endl;
	cout << "2 Coordinates" << endl;
	cout << "3 Maximum Capacity" << endl;
	cout << "4 Blue Flag" << endl;
	cout << "5 Services" << endl;
	cout << "6 Usable aquatic area" << endl;
	cout << ">>> ";
	while (true) {
		cin >> input;
		if (cin.fail() && (input < 1 || input > 8)) {
			cout << "Invalid option value, please insert a valid option (positive integer between 1 and 6)." << endl;
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Calling respective modify function
	switch (input) {
	case 1:
		this->modifyName();
		break;
	case 2:
		this->modifyCoordinates();
		break;
	case 3:
		this->modifyMaxCapacity();
		break;
	case 4:
		this->modifyBlueFlag();
		break;
	case 5:
		this->modifyServices();
		break;
	case 6:
		this->modifyUsableAquaticArea();
		break;
	}
}
