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
	o << "Usable aquatic area: " << usableAquaticArea << endl << endl;
}

void BayouBeach::modifyUsableAquaticArea() {
	double uaa;
	cout << "What is the bayou's new usable aquatic area? " << endl;
	while (true) {
		cin >> uaa;
		if (cin.fail() || uaa <= 0) {
			cout << "Invalid usable aquatic area, please insert a valid usable aquatic area (positive decimal)." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Ensuring cin is clear after using it as a stream
	Utilities::clearCinBuffer();

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
		if (cin.fail() && (input < 1 || input > 6)) {
			cout << "Invalid option value, please insert a valid option (positive integer between 1 and 6)." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Ensuring cin is clear after using it as a stream
	Utilities::clearCinBuffer();

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


string BayouBeach::toString(){
	string format = "b | " + this->getName() + " | " + this->getCoords().toString();
	format += " | " + to_string(this->getMaxCapacity()) + " | ";

	if (this->hasBlueFlag())
		format += "1 | ";
	else
		format += "0 | ";

	//If there are any services, adding the first service first and then iterating through and adding the others because of inserting the " ; "
	if(!this->getServices().empty()) {
		auto it = this->getServices().begin();
		format += it->toString();
		//Moving to the next element
		++it;

		for( ; it != this->getServices().end() ; ++it)
			format += " ; " + it->toString();
	}

	format += " | " + to_string(usableAquaticArea);

	return format;
}
