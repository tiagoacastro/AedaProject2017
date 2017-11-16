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
	string format = "r | " + name + " | " + coords.toString();
		format += " | " + to_string(maxCapacity) + " | ";

		if (blueFlag)
			format += "1" + " | ";
		else
			format += "0" + " | ";
		for(auto &serv : services)
			format += services[serv];

		format.substr(0 , format.size() - 2);

		format += to_string(width) + " | " + to_string(riverFlow) + " | " + to_string(maxDepth);

		return format;
}
