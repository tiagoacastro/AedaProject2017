#include "Beach.h"

using namespace std;

Beach::Beach(string name, Coordinates coords, unsigned int maxCapacity, bool blueFlag, const vector <Service> &services)
	:name(name), coords(coords), maxCapacity(maxCapacity), blueFlag(blueFlag), services(services){}


bool Beach::hasBlueFlag() const {
	return blueFlag;
}

void Beach::setBlueFlag(bool blueFlag) {
	this->blueFlag = blueFlag;
}

Coordinates Beach::getCoords() const {
	return coords;
}

unsigned int Beach::getMaxCapacity() const {
	return maxCapacity;
}

void Beach::setMaxCapacity(unsigned int maxCapacity) {
	this->maxCapacity = maxCapacity;
}

string Beach::getName() const {
	return name;
}

void Beach::setName(const string& name) {
	this->name = name;
}

vector<Service> Beach::getServices() const {
	return services;
}

void Beach::setServices(const vector<Service> &services) {
	this->services = services;
}
