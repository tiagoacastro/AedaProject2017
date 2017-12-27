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
	if (services.empty())
		o << "No services" << endl;
	else {
		o << "Services:" << endl;
		for (auto &service: services)
			o << service;

	}
}

Beach::~Beach() {

}

void Beach::setCoordinates(const Coordinates &coords){
	this->coords = coords;
}

void Beach::modifyName(){
	string name;
	cout << "What is the new name of the beach?" << endl;
	getline(cin, name);

	//Setting the new name for the beach
	this->setName(name);
}

void Beach::modifyCoordinates(){
	double x, y;
	cout << "What are the new coordinates of the beach (X followed by Y)?" << endl;

	//Getting X
	while (true) {
		cin >> x;
		if (cin.fail()) {
			cout << "Invalid X value, please insert a valid X coordinate value (decimal number)." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Getting Y
	while (true) {
		cin >> y;
		if (cin.fail()) {
			cout << "Invalid Y value, please insert a valid Y coordinate value (decimal number)." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Ensuring cin is clear after using it as a stream
	Utilities::clearCinBuffer();

	//Setting the new coordinates
	this->coords.setLatitude(x);
	this->coords.setLongitude(y);
}

void Beach::modifyMaxCapacity(){
	unsigned int maxCapacity;
	cout << "What is the beach's new maximum capacity?" << endl;

	while (true) {
		cin >> maxCapacity;
		if (cin.fail()) {
			cout << "Invalid max capacity value, please insert a valid maximum capacity value (positive integer)." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Ensuring cin is clear after using it as a stream
	Utilities::clearCinBuffer();

	//Sets the new max capacity
	this->setMaxCapacity(maxCapacity);
}

void Beach::modifyBlueFlag(){
	string response;
	cout << "Does the beach have a blue flag (yes or no)?" << endl;

	while (true) {
		cin >> response;
		if (cin.fail() || (response != "yes" && response != "no" && response != "Yes" && response != "No")) {
			cout << "Invalid input, please enter yes or no." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Ensuring cin is clear after using it as a stream
	Utilities::clearCinBuffer();

	//Setting the new blue flag
	//Since the previous loop ensures the input is "Yes", "yes", "No" or "no"
	this->setBlueFlag((response == "yes") || (response == "Yes"));
}

void Beach::modifyServices(){
	if(services.empty()){
		cout << "There are no services to modify in this beach!" << endl;
		return;
	}

	cout << "The services that exist in this beach are:" << endl;
	this->listAllServices();
	cout << "Which do you want to alter (insert service name)?" << endl;
	string tempservicename;
	getline(cin, tempservicename);

	auto it = findServiceByName(tempservicename);

	if(it == services.end()){
		cout << "Service not found! Exiting!" << endl;
		return;
	}

	//Altering the service
	cout << "Service found! Which field do you want to alter?" << endl;
	int input;
	cout << "1 Name" << endl;
	cout << "2 Type" << endl;
	cout << "3 Description" << endl;
	cout << ">>> ";

	while (true) {
		cin >> input;
		if (cin.fail() && (input < 1 || input > 3)) {
			cout << "Invalid option value, please insert a valid option (positive integer between 1 and 4)." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
		} else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Ensuring cin is clear after using it as a stream
	Utilities::clearCinBuffer();

	//Doing respective modification
	switch(input){
		case 1:
			it->modifyName();
			break;
		case 2:
			it->modifyType();
			break;
		case 3:
			it->modifyDescription();
			break;
	}
}

vector<Service>::iterator Beach::findServiceByName(const string &servicename) {
	return find_if(services.begin(), services.end(), [=](const Service &s){
		return s.getName() == servicename;
	});
}

void Beach::listAllServices() const{
	for(auto const &service : services){
		cout << service << endl;
	}
}
