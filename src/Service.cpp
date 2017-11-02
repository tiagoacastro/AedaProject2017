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

//POI

POI::POI(string name, Coordinates coords) :
	name(name), coords(coords) {
	description = "none";
}

POI::POI(string name, Coordinates coords, string description) :
	name(name), coords(coords), description(description) {
}

Lodging::Lodging(string name, Coordinates coords, bool full) :
	name(name), coords(coords), full(full) {
	description = "none";
}

Lodging::Lodging(string name, Coordinates coords, bool full, string description) :
	name(name), coords(coords), full(full), description(description) {
}