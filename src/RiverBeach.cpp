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

/*ostream & operator<<(ostream & o, const RiverBeach & d){

	o << "River beach name: " << d.name << "\nCoordinates " << d.Coordinates.print() << "\nMaximum Capacity: " << d.maxCapacity << "Blue Flag: ";
	o << (d.blueFlag ? "Yes" : "No") << endl;
	o << "Services in this River Beach: \n\t" << d.services; //Suggestion: Use Utilities::printVector
	return o;

}
*/
