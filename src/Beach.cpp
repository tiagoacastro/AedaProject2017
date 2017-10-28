#include "Beach.h"

using namespace std;

Beach::Beach(string name, Coordinates cords, unsigned int maxCapacity, bool BlueFlag, vector <Service> services)
	:name(name), cords(cords), maxCapacity(maxCapacity), BlueFlag(BlueFlag), services(services){}


bool Beach::isBlueFlag() const {
	return BlueFlag;
}

void Beach::setBlueFlag(bool blueFlag) {
	BlueFlag = blueFlag;
}

const Coordinates& Beach::getCords() const {
	return cords;
}

unsigned int Beach::getMaxCapacity() const {
	return maxCapacity;
}

void Beach::setMaxCapacity(unsigned int maxCapacity) {
	this->maxCapacity = maxCapacity;
}

const string& Beach::getName() const {
	return name;
}

void Beach::setName(const string& name) {
	this->name = name;
}

const vector<Service>& Beach::getServices() const {
	return services;
}

void Beach::setServices(const vector<Service>& services) {
	this->services = services;
}
