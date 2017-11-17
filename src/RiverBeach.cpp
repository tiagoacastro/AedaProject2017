#include "RiverBeach.h"
#include <iostream>
using namespace std;

RiverBeach::RiverBeach(string name, Coordinates coords, unsigned int maxCapacity, bool blueFlag, const vector <Service> &services, double width, double riverFlow, double maxDepth)
	:Beach(name, coords, maxCapacity, blueFlag, services), width(width), riverFlow(
				riverFlow), maxDepth(maxDepth) {
}

double RiverBeach::getMaxDepth() const {
	return maxDepth;
}

void RiverBeach::setMaxDepth(double maxDepth) {
	this->maxDepth = maxDepth;
}

double RiverBeach::getRiverFlow() const {
	return riverFlow;
}

void RiverBeach::setRiverFlow(double riverFlow) {
	this->riverFlow = riverFlow;
}

double RiverBeach::getWidth() const {
	return width;
}

void RiverBeach::setWidth(double width) {
	this->width = width;
}

void RiverBeach::print(ostream &o) {
	Beach::print(o);
	o << "River width: " << width << endl;
	o << "River flow: " << riverFlow << endl;
	o << "River's max depth: " << maxDepth << endl;
}

string RiverBeach::toString(){
	string format;
	format = "r | " + this->getName() + " | " + this->getCoords().toString() + " | " + to_string(this->getMaxCapacity()) + " | ";

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

	format += " | " + to_string(width) + " | " + to_string(riverFlow) + " | " + to_string(maxDepth);

	return format;
}
