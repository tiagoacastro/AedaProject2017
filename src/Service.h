#pragma once
#include <string>
#include <vector>
#include "Coordinates.h"

using namespace std;

struct Schedule {
	vector<string> weekSchedule;
};

class Service {
	private:
		string name;
		string type;
		Schedule sch;
		string description;
	public:
		Service(string name, string type, Schedule sch);
		Service(string name, string type, Schedule sch, string description);
		string getDescription() const;
		void setDescription(const string &description);
		string getName() const;
		void setName(const string &name);
		Schedule getSchedule() const;
		void setSchedule(const Schedule& sch);
		string getType() const;
		void setType(const string &type);

		friend ostream & operator<<(ostream &o, const Service &s);

};

class Restaurant {
private:
	string name;
	Schedule sch;
	Coordinates coords;
	string description;
public:
	Restaurant(string name, Schedule sch, Coordinates coords);
	Restaurant(string name, Schedule sch, Coordinates coords, string description);
};

class POI {
private:
	string name;
	Coordinates coords;
	string description;
public:
	POI(string name, Coordinates coords);
	POI(string name, Coordinates coords, string description);
};

class Lodging {
private:
	string name;
	Coordinates coords;
	bool full;
	string description;
public:
	Lodging(string name, Coordinates coords, bool full);
	Lodging(string name, Coordinates coords, bool full, string description);
};