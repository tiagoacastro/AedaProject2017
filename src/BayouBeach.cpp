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
	string format = "b | " + name + " | " + coords.toString();
	format += " | " + to_string(maxCapacity) + " | ";

	if (blueFlag)
		format += "1" + " | ";
	else
		format += "0" + " | ";

	for(auto &serv : services)
		format += services[serv];

	format.substr(0 , format.size() - 2);

	format += " | " + to_string(usableAquaticArea);

return format;

}
