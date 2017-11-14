#pragma once
#include <string>
#include <vector>
#include "Coordinates.h"
#include "Utilities.h"

using namespace std;

struct Schedule {
	vector<string> weekSchedule;
	/**
	 * @brief Overload for the insertion operator for the Schedule struct
	 * @param os	The ostream to write to
	 * @param sch	The schedule that is being written to the ostream
	 * @return	Returns the modified ostream
	 */
	friend ostream & operator<<(ostream &os, const Schedule &sch);
};

class Service {
	private:
		string name;
		string type;
		Schedule sch;
		string description;
	public:
		/**
		 * @brief Constructor for the Service class
		 * @param name 			Name of the Service
		 * @param type 			Type of the Service
		 * @param sch 			Schedule of the Service
		 * @param description 	Description of the Service, default value is "None"
		 */
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
	/**
	 * @brief Constructor for the Restaurant class
	 * @param name 			Name of the restaurant
	 * @param sch 			Schedule for the restaurant
	 * @param coords 		Coordinates of the restaurant
	 * @param description 	Description of the restaurant, has a default value of "None"
	 */
	Restaurant(string name, Schedule sch, Coordinates coords, string description);
	string getName() const;
	Coordinates getCoordinates() const;
	string getDescription() const;
	Schedule getSchedule() const;

	friend ostream & operator<<(ostream &o, const Restaurant &r);
};

class POI {
private:
	string name;
	Coordinates coords;
	string description;
public:
	/**
	 * @brief Constructor for the POI class
	 * @param name			The name of the POI
	 * @param coords		The coordinates of the POI
	 * @param description	The description of the POI, default value is "None"
	 */
	POI(string name, Coordinates coords, string description);
	string getName() const;
	Coordinates getCoordinates() const;
	string getDescription() const;

	friend ostream & operator<<(ostream &o, const POI &p);
};

class Lodging {
private:
	string name;
	Coordinates coords;
	bool full;
	string description;
public:
	/**
	 * @brief Constructor for the Lodging class
	 * @param name 			The name of the Lodging
	 * @param coords 		The coordinates of the Lodging
	 * @param full 			If the Lodging is full or not
	 * @param description 	The description of the Lodging, default value is "None"
	 */
	Lodging(string name, Coordinates coords, bool full, string description);
	string getName() const;
	Coordinates getCoordinates() const;
	bool isFull() const;
	string getDescription() const;

	friend ostream & operator<<(ostream &o, const Lodging &l);
};