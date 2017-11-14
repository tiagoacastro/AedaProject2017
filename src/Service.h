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
		/**
		* @brief get function of the description of the service
		* @return Returns the service's description
		*/
		string getDescription() const;
		/**
		* @brief set function of the description of the service
		* @param description 	Description of the Service, default value is "None"
		*/
		void setDescription(const string &description);
		/**
		* @brief get function of the name of the service
		* @return Returns the service's name
		*/
		string getName() const;
		/**
		* @brief set function of the name of the service
		* @param name 			Name of the Service
		*/
		void setName(const string &name);
		/**
		* @brief get function of the schedule of the service
		* @return Returns the service's schedule
		*/
		Schedule getSchedule() const;
		/**
		* @brief set function of the schedule of the service
		* @param sch 			Schedule of the Service
		*/
		void setSchedule(const Schedule& sch);
		/**
		* @brief get function of the service's type
		* @return Returns the service's type
		*/
		string getType() const;
		/**
		* @brief set function of the type of the service
		* @param type 			Type of the Service
		*/
		void setType(const string &type);
		/**
		* @brief Overload for the insertion operator for the Service class
		* @param os		The ostream to write to
		* @param s		The service that is being written to the ostream
		* @return Returns the modified ostream
		*/
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
	/**
	* @brief get function of the restaurant's name
	* @return Returns the restaurant's name
	*/
	string getName() const;
	/**
	* @brief get function of the restaurant's coordinates
	* @return Returns the restaurant's coordinates
	*/
	Coordinates getCoordinates() const;
	/**
	* @brief get function of the restaurant's description
	* @return Returns the restaurant's description
	*/
	string getDescription() const;
	/**
	* @brief get function of the restaurant's schedule
	* @return Returns the restaurant's schedule
	*/
	Schedule getSchedule() const;
	/**
	* @brief Overload for the insertion operator for the Restaurant class
	* @param os		The ostream to write to
	* @param r		The restaurant that is being written to the ostream
	* @return Returns the modified ostream
	*/
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
	/**
	* @brief get function of the POI's name
	* @return Returns the POI's name
	*/
	string getName() const;
	/**
	* @brief get function of the POI's coordinates
	* @return Returns the POI's coordinates
	*/
	Coordinates getCoordinates() const;
	/**
	* @brief get function of the POI's description
	* @return Returns the POI's description
	*/
	string getDescription() const;
	/**
	* @brief Overload for the insertion operator for the POI class
	* @param os		The ostream to write to
	* @param p		The POI that is being written to the ostream
	* @return Returns the modified ostream
	*/
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
	/**
	* @brief get function of the lodging's name
	* @return Returns the lodging's name
	*/
	string getName() const;
	/**
	* @brief get function of the lodging's coordinates
	* @return Returns the lodging's coordinates
	*/
	Coordinates getCoordinates() const;
	/**
	* @brief get function of the full lodging class bool member to know if the lodging is full
	* @return Returns true if the lodging is full, false if not
	*/
	bool isFull() const;
	/**
	* @brief get function of the lodging's descritpion
	* @return Returns the lodging's description
	*/
	string getDescription() const;
	/**
	* @brief Overload for the insertion operator for the Lodging class
	* @param os		The ostream to write to
	* @param l		The lodging that is being written to the ostream
	* @return Returns the modified ostream
	*/
	friend ostream & operator<<(ostream &o, const Service &l);
};