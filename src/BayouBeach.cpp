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

