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

void Beach::print(ostream &o){
	o << "Name: " << name << endl;
	o << "Coordinates: " << coords << endl;
	o << "Max capacity: " << maxCapacity << endl;
	if (blueFlag)
		o << "Has Blue Flag" << endl;
	else
		o << "Doesn't have Blue Flag" << endl;
	if (services.size() == 0)
		o << "No services" << endl;
	else {
		o << "Services:" << endl;
		for (size_t i = 0; i < services.size(); i++)
			o << services.at(i) << endl;
	}
}