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

void RiverBeach::modifyBeach(){
	//Fields available to modify:
	//From Beach:
	//name, coordinates, max capacity, blue flag and services
	//From RiverBeach:
	//width, river flow, max depth
	int input;
	cout << "What do you want to modify?" << endl;
	cout << "1 Name" << endl;
	cout << "2 Coordinates" << endl;
	cout << "3 Maximum Capacity" << endl;
	cout << "4 Blue Flag" << endl;
	cout << "5 Services" << endl;
	cout << "6 River Width" << endl;
	cout << "7 River Flow" << endl;
	cout << "8 River Maximum Depth" << endl;
	while (true) {
			cin >> input;
			if (cin.fail() && (input < 1 || input > 8)) {
				cout << "Invalid option value, please insert a valid option (positive integer between 1 and 8)." << endl;
				//Clearing error flag and cin buffer
				cin.clear();
				cin.ignore(100000, '\n');
			}
			else {
				//if cin didn't fail we have a good input so we break the loop
				break;
			}
		}

	//Calling respective modify function
	switch(input){
		case 1:
			this->modifyName();
		case 2:
			this->modifyCoordinates();
		case 3:
			this->modifyMaxCapacity();
		case 4:
			this->modifyBlueFlag();
		case 5:
			this->modifyServices();
		case 6:
			this->modifyRiverWidth();
		case 7:
			this->modifyRiverFlow();
		case 8:
			this->modifyRiverMaximumDepth();
	}
}

void RiverBeach::modifyRiverWidth(){
	double width;
	cout << "What is the river's width? " << endl;
	while (true) {
		cin >> width;
		if (cin.fail() || width <= 0) {
			cout << "Invalid river width value, please insert a valid river width value (positive decimal)." << endl;
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Setting the new river width
	this->setWidth(width);
}

void RiverBeach::modifyRiverFlow(){
	double riverFlow;
	cout << "What is the river's new flow? " << endl;
	while (true) {
		cin >> riverFlow;
		if (cin.fail() || riverFlow <= 0) {
			cout << "Invalid river flow value, please insert a valid river flow value (positive decimal)." << endl;
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Setting the new river flow
	this->setRiverFlow(riverFlow);
}

void RiverBeach::modifyRiverMaximumDepth(){
	double maxDepth;
	cout << "What is the river's new max depth? " << endl;
	while (true) {
		cin >> maxDepth;
		if (cin.fail() || maxDepth <= 0) {
			cout << "Invalid river max depth, please insert a valid river maximum depth (positive decimal)." << endl;
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Setting the new max depth
	this->setMaxDepth(maxDepth);
}
