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
