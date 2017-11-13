#include "Service.h"
#include "Utilities.h"
#include <ostream>

//Service

Service::Service(string name, string type, Schedule sch, string description = "None") :
	name(name), type(type), sch(sch), description(description) {
}

string Service::getDescription() const {
	return description;
}

void Service::setDescription(const string &description) {
	this->description = description;
}

string Service::getName() const {
	return name;
}

void Service::setName(const string &name) {
	this->name = name;
}

Schedule Service::getSchedule() const {
	return sch;
}

void Service::setSchedule(const Schedule &sch) {
	this->sch = sch;
}

string Service::getType() const {
	return type;
}

void Service::setType(const string &type) {
	this->type = type;
}

ostream & operator<<(ostream &os, const Service &s){
	// os << "SERVICE" << endl;
	os << "Name: " << name << endl;
	os << "Type: " << type << endl;
	os << "Description: " << description << endl;
	os << "Schedule:" << endl;
	os << sch << endl;

	return os;
}

//Restaurant

Restaurant::Restaurant(string name, Schedule sch, Coordinates coords, string description = "None") :
	name(name), sch(sch), coords(coords), description(description){
}

string Restaurant::getName() const {
	return name;
}

Coordinates Restaurant::getCoordinates() const {
	return coords;
}

string Restaurant::getDescription() const {
	return description;
}

Schedule Restaurant::getSchedule() const {
	return sch;
}

ostream & operator<<(ostream &os, const Restaurant &r) {
	// os << "RESTAURANT" << endl; //TBD
	os << "Name: " << name << endl;
	os << "Coordinates: " << coords << endl;
	os << "Description: " << description << endl;
	os << "Schedule:" << endl;
	os << sch;

	return os;
}

//POI

POI::POI(string name, Coordinates coords, string description = "None") :
	name(name), coords(coords), description(description) {
}

string POI::getName() const {
	return name;
}

Coordinates POI::getCoordinates() const {
	return coords;
}

string POI::getDescription() const {
	return description;
}

ostream & operator<<(ostream &os, const POI &p) {
	// os << "POI" << endl;
	os << "Name: " << name << endl;
	os << "Coordinates: " << coords << endl;
	os << "Description: " << description << endl;

	return os;
}

//Lodging

Lodging::Lodging(string name, Coordinates coords, bool full, string description = "None") :
	name(name), coords(coords), full(full), description(description) {
}

string Lodging::getName() const {
	return name;
}

Coordinates Lodging::getCoordinates() const {
	return coords;
}

string Lodging::getDescription() const {
	return description;
}

bool Lodging::isFull() const {
	return full;
}

ostream & operator<<(ostream &os, const Lodging &l) {
	// os << "Lodging" << endl;
	os << "Name: " << name << endl;
	os << "Coordinates: " << coords << endl;
	os << "Full? " << (full ? "Yes" : "No") << endl;
	os << "Description: " << description << endl;

	return os;
}

ostream &operator<<(ostream &os, const Schedule &sch){
	for (int i = 0; i < sch.weekSchedule.size(); i++) {
		os << Utilities::weekdays.at(i) << ": " << sch.weekSchedule.at(i) << endl;
	}

	return os;
}
