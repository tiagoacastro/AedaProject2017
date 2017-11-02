#include "Service.h"
#include <ostream>

//Service

Service::Service(string name, string type, Schedule sch) :
	name(name), type(type), sch(sch){
	description = "none";
}

Service::Service(string name, string type, Schedule sch, string description) :
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

ostream & operator<<(ostream &o, const Service &s) {
	o << "SERVICE" << endl << "name: " << s.getName() << endl << "type: " << s.getType() << endl << "description: " << s.getDescription() << endl << "schedule: " << endl;
	for (int i = 0; i < s.getSchedule().weekSchedule.size(); i++)
	{
		switch (i) {
			case 0:
				o << "Monday: ";
			case 1:
				o << "Tuesday: ";
			case 2:
				o << "Wednesday: ";
			case 3:
				o << "Thursday: ";
			case 4:
				o << "Friday: ";
			case 5:
				o << "Saturday: ";
			case 6:
				o << "Sunday: ";
		}
		o << s.getSchedule().weekSchedule.at(i) << endl;
	}
	return o;
}

//Restaurant

Restaurant::Restaurant(string name, Schedule sch, Coordinates coords) :
	name(name), sch(sch), coords(coords){
	description = "none";
}

Restaurant::Restaurant(string name, Schedule sch, Coordinates coords, string description) :
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

ostream & operator<<(ostream &o, const Restaurant &r) {
	o << "RESTAURANT" << endl << "name: " << r.getName() << endl << "coordinates: " << r.getCoordinates().getLongitude() << " " << r.getCoordinates().getLatitude() << endl << "description: " << r.getDescription() << endl << "schedule: " << endl;
	for (int i = 0; i < r.getSchedule().weekSchedule.size(); i++)
	{
		switch (i) {
		case 0:
			o << "Monday: ";
		case 1:
			o << "Tuesday: ";
		case 2:
			o << "Wednesday: ";
		case 3:
			o << "Thursday: ";
		case 4:
			o << "Friday: ";
		case 5:
			o << "Saturday: ";
		case 6:
			o << "Sunday: ";
		}
		o << r.getSchedule().weekSchedule.at(i) << endl;
	}
	return o;
}

//POI

POI::POI(string name, Coordinates coords) :
	name(name), coords(coords) {
	description = "none";
}

POI::POI(string name, Coordinates coords, string description) :
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

ostream & operator<<(ostream &o, const POI &p) {
	o << "POI" << endl << "name: " << p.getName() << endl << "coordinates: " << p.getCoordinates().getLongitude() << " " << p.getCoordinates().getLatitude() << endl << "description: " << p.getDescription() << endl;
	return o;
}

//Lodging

Lodging::Lodging(string name, Coordinates coords, bool full) :
	name(name), coords(coords), full(full) {
	description = "none";
}

Lodging::Lodging(string name, Coordinates coords, bool full, string description) :
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

ostream & operator<<(ostream &o, const Lodging &l) {
	o << "Lodging" << endl << "name: " << l.getName() << endl << "coordinates: " << l.getCoordinates().getLongitude() << " " << l.getCoordinates().getLatitude() << endl << "Full? ";
	if (l.isFull())
		o << "Yes" << endl;
	else
		o << "No" << endl;
	o << "description: " << l.getDescription() << endl;
	return o;
}