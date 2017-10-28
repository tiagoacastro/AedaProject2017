#include "RiverBeach.h"
#include <iostream>
using namespace std;

RiverBeach::RiverBeach(string name, Coordinates cords, unsigned int maxCapacity, bool BlueFlag, vector <Service> services, double width, double riverFlow, double maxDepth)
	:Beach(name, cords, maxCapacity, BlueFlag, services), width(width), riverFlow(
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
	if (d.BlueFlag)
		o << "Yes\n";
	else
		o << "No\n";
	o << "Services in this River Beach: \n\t" << d.services
	return o;

}
*/
