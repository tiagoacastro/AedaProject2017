#include "Service.h"

//Service

Service::Service(string name, string type, string description = "None", string inspectionDate = "0") :
name(name), type(type), description(description), inspectionDate(inspectionDate) {
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
	os << "- Name: " << s.name << endl;
	os << "Type: " << s.type << endl;
	os << "Description: " << s.description << endl;
	os << "Last inspection: " << s.inspectionDate << endl;

	return os;
}

string Service::toString() const {
	return name + ", " + type + ", " + description + ", " + inspectionDate;
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
	this->setDescription(desc);
}

//Restaurant

Restaurant::Restaurant(string name, Schedule sch, Coordinates coords, string description = "None")
: name(name), sch(sch), coords(coords), description(description){
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

string Restaurant::toString() const {
	string format = name + " | " + coords.toString() + " | ";

	//Adding the first element outside of the loop because of adding the ", " more easily
	auto it = sch.weekSchedule.begin();

	format += *it;
	//Advancing to the next item since it was already written
	++it;

	for ( ; it != sch.weekSchedule.end() ; ++it)
		format += ", " + *it;

	format += " | " + description;
	return format;
}

void Restaurant::modifyRestaurant() {
	//Fields available to modify:
	//name, schedule, coordinates, description
	int input;
	cout << "What do you want to modify?" << endl;
	cout << "1 Name" << endl;
	cout << "2 Schedule" << endl;
	cout << "3 Coordinates" << endl;
	cout << "4 Description" << endl;
	cout << ">>> ";
	while (true) {
		cin >> input;
		if (cin.fail() && (input < 1 || input > 4)) {
			cout << "Invalid option value, please insert a valid option (positive integer between 1 and 4)." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
		}
		else {
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Calling respective modify function
	switch (input) {
	case 1:
		this->modifyName();
		break;
	case 2:
		this->modifySchedule();
		break;
	case 3:
		this->modifyCoordinates();
		break;
	case 4:
		this->modifyDescription();
		break;
	}
}

void Restaurant::modifyName() {
	string newName;
	cout << "What is the new name of the Restaurant? " << endl;
	getline(cin, newName);
	Utilities::trimString(newName);

	name = newName;
}

void Restaurant::modifyCoordinates() {
	double x, y;
	cout << "What are the new coordinates of the restaurant (X followed by Y)?" << endl;

	//Getting X
	while (true) {
		cin >> x;
		if (cin.fail()) {
			cout << "Invalid X value, please insert a valid X coordinate value (decimal number)." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
		}
		else {
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
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
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	Coordinates c(x, y);
	coords = c;
}

void Restaurant::modifySchedule() {
	Schedule schd;
	string iHour, fHour, day;
	for (unsigned int i = 0; i < 7; i++)
	{
		cout << "When does the restaurant open on " << Utilities::weekdays[i] << " (HH:MM)?" << endl;
		while (true) {
			getline(cin, iHour);
			Utilities::trimString(iHour);
			if (!Utilities::correctHourFormat(iHour)) {
				cout << "Wrong hour format, must be HH:MM" << endl;
			}
			else {
				break;
			}
		}
		cout << "When does the restaurant close on " << Utilities::weekdays[i] << " (HH:MM)?" << endl;
		while (true) {
			getline(cin, fHour);
			Utilities::trimString(fHour);
			if (!Utilities::correctHourFormat(fHour)) {
				cout << "Wrong hour format, must be HH:MM" << endl;
			}
			else {
				break;
			}
		}

		day.assign(iHour + " to " + fHour);
		//Day schedule format: "HH:MM to HH:MM"
		schd.weekSchedule.push_back(day);
	}

	sch = schd;
}

void Restaurant::modifyDescription() {
	string desc;
	cout << "Restaurant new description: ";
	getline(cin, desc);
	Utilities::trimString(desc);

	description = desc;
}

//POI

POI::POI(string name, Coordinates coords, string description = "None")
: name(name), coords(coords), description(description) {
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

string POI::toString() const {
	return name + " | " + coords.toString() + " | " +  description;
}

void POI::modifyPOI() {
	//Fields available to modify:
	//name, coordinates, description
	int input;
	cout << "What do you want to modify?" << endl;
	cout << "1 Name" << endl;
	cout << "2 Coordinates" << endl;
	cout << "3 Description" << endl;
	cout << ">>> ";
	while (true) {
		cin >> input;
		if (cin.fail() && (input < 1 || input > 3)) {
			cout << "Invalid option value, please insert a valid option (positive integer between 1 and 3)." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
		}
		else {
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Calling respective modify function
	switch (input) {
	case 1:
		this->modifyName();
		break;
	case 2:
		this->modifyCoordinates();
		break;
	case 3:
		this->modifyDescription();
		break;
	}
}

void POI::modifyName() {
	string newName;
	cout << "What is the new name of the POI? " << endl;
	getline(cin, newName);
	Utilities::trimString(newName);

	name = newName;
}

void POI::modifyCoordinates() {
	double x, y;
	cout << "What are the new coordinates of the POI (X followed by Y)?" << endl;

	//Getting X
	while (true) {
		cin >> x;
		if (cin.fail()) {
			cout << "Invalid X value, please insert a valid X coordinate value (decimal number)." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
		}
		else {
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
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
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	Coordinates c(x, y);
	coords = c;
}


void POI::modifyDescription() {
	string desc;
	cout << "POI new description: ";
	getline(cin, desc);
	Utilities::trimString(desc);

	description = desc;
}

//Lodging

Lodging::Lodging(string name, Coordinates coords, bool full, string description = "None")
: name(name), coords(coords), full(full), description(description) {
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

string Lodging::toString() const {
	string format = name + " | " + coords.toString() + " | ";

	if (full)
		format += "1 | ";
	else
		format += "0 | ";

	format += description;

	return format;
}

void Lodging::modifyName() {
	string newName;
	cout << "What is the new name of the Lodging? " << endl;
	getline(cin, newName);
	Utilities::trimString(newName);

	name = newName;
}

void Lodging::modifyCoordinates() {
	double x, y;
	cout << "What are the new coordinates of the Lodging (X followed by Y)?" << endl;

	//Getting X
	while (true) {
		cin >> x;
		if (cin.fail()) {
			cout << "Invalid X value, please insert a valid X coordinate value (decimal number)." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
		}
		else {
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
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
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	Coordinates c(x, y);
	coords = c;
}


void Lodging::modifyDescription() {
	string desc;
	cout << "Lodging new description: ";
	getline(cin, desc);
	Utilities::trimString(desc);

	description = desc;
}

void Lodging::modifyFull() {
	string response;
	cout << "Is the Lodging full (yes or no)? " << endl;

	while (true) {
		cin >> response;
		Utilities::trimString(response);
		if (cin.fail() || (response != "yes" && response != "no" && response != "Yes" && response != "No")) {
			cout << "Invalid input, please enter yes or no." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
		}
		else {
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	full = ((response == "yes") || (response == "Yes"));
}

void Lodging::modifyLodging() {
	//Fields available to modify:
	//name, coordinates, full, description
	int input;
	cout << "What do you want to modify?" << endl;
	cout << "1 Name" << endl;
	cout << "2 Coordinates" << endl;
	cout << "3 Full Flag" << endl;
	cout << "4 Description" << endl;
	cout << ">>> ";
	while (true) {
		cin >> input;
		if (cin.fail() && (input < 1 || input > 4)) {
			cout << "Invalid option value, please insert a valid option (positive integer between 1 and 4)." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
		}
		else {
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Calling respective modify function
	switch (input) {
	case 1:
		this->modifyName();
		break;
	case 2:
		this->modifyCoordinates();
		break;
	case 3:
		this->modifyFull();
		break;
	case 4:
		this->modifyDescription();
		break;
	}
}

string Service::getInspectionDate(){
	return this->inspectionDate;

}

void Service::setInspectionDate(string &date){

	inspectionDate = date;
}

bool Service::operator<(Service  &s) const {
	return  inspectionDate < s.getInspectionDate();
}
