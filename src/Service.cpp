#include "Service.h"
#include "Utilities.h"
#include <ostream>

//Service

Service::Service(string name, string type, string description = "None") :
	name(name), type(type), description(description) {
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

string Service::getType() const {
	return type;
}

void Service::setType(const string &type) {
	this->type = type;
}

ostream & operator<<(ostream &os, const Service &s){
	os << "Name: " << s.name << endl;
	os << "Type: " << s.type << endl;
	os << "Description: " << s.description << endl;
	return os;
}

void Service::modifyName(){
	string name;
	cout << "What is the new name of the service?" << endl;
	getline(cin, name);

	//Setting the new name for the service
	this->setName(name);
}

void Service::modifyType(){
	string type;
	cout << "What is the new type of the service?" << endl;
	getline(cin, type);

	//Setting the new type for the service
	this->setType(type);
}

void Service::modifyDescription(){
	string desc;
	cout << "What is the new description of the service?" << endl;
	getline(cin, desc);

	//Setting the new type for the service
	this->setType(desc);
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
	os << "Name: " << r.name << endl;
	os << "Coordinates: " << r.coords << endl;
	os << "Description: " << r.description << endl;
	os << "Schedule:" << endl;
	os << r.sch;

	return os;
}

void Restaurant::setName(const string &name){
	this->name = name;
}

void Restaurant::setSch(const Schedule &sch){
	this->sch = sch;
}

void Restaurant::setCoords(const Coordinates &coords){
	this->coords = coords;
}

void Restaurant::setDescription(const string &description){
	this->description = description;
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
	os << "Name: " << p.name << endl;
	os << "Coordinates: " << p.coords << endl;
	os << "Description: " << p.description << endl;

	return os;
}

void POI::setName(const string &name){
	this->name = name;
}

void POI::setCoords(const Coordinates &coords){
	this->coords = coords;
}

void POI::setDescription(const string &description){
	this->description = description;
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
	os << "Name: " << l.name << endl;
	os << "Coordinates: " << l.coords << endl;
	os << "Full? " << (l.full ? "Yes" : "No") << endl;
	os << "Description: " << l.description << endl;

	return os;
}

void Lodging::setName(const string &name){
	this->name = name;
}

void Lodging::setCoords(const Coordinates &coords){
	this->coords = coords;
}

void Lodging::setFull(bool full){
	this->full = full;
}

void Lodging::setDescription(const string &description){
	this->description = description;
}

ostream &operator<<(ostream &os, const Schedule &sch){
	for (int i = 0; i < sch.weekSchedule.size(); i++) {
		os << Utilities::weekdays.at(i) << ": " << sch.weekSchedule.at(i) << endl;
	}

	return os;
}
