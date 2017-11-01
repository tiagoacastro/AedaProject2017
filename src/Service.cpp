#include "Service.h"
#include <ostream>

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
