#pragma once
#include <string>
#include <vector>
#include "Coordinates.h"
#include "Utilities.h"
#include <ostream>

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
	string description;
	string inspectionDate;
public:
	/**
	 * @brief Constructor for the Service class
	 * @param name 			Name of the Service
	 * @param type 			Type of the Service
	 * @param description 		Description of the Service, default value is "None"
	 * @param inspectionDate	Date of the latest inspection
	 */
	Service(string name, string type, string description, string inspectionDate);
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
	friend ostream & operator<<(ostream &os, const Service &s);
	/**
	 * @brief passes data members to a string
	 * @return Returns a string with all data members
	 */
	string toString() const;
	/**
	 * @brief Modifies the Service name based on user input
	 */
	void modifyName();
	/**
	 * @brief Modifies the Service type based on user input
	 */
	void modifyType();
	/**
	 * @brief Modifies the Service description based on user input
	 */
	void modifyDescription();
	/**
	 * @brief Set Inspection Date to the date of the last Inspection
	 * @param date  Date of the last Inspection
	 */
	void setInspectionDate(const string &date);

	/**
	 * @brief get function of the inspection date
	 * @return Returns the inspetion date
	 */
	string getInspectionDate();
	/**
	 * @brief Overload for the insertion operator for the Service class
	 * @param os		The ostream to write to
	 * @param s		The service that is being written to the ostream
	 * @return Returns the modified ostream
	 */
	friend ostream & operator<<(ostream &os, const Service &s);

	/**
	 * @brief Overload for the less operator for the Service class
	 * @param s		The service to compare
	 * @return Returns if a service is smaller than another (for sorting inside the priority queue, so by dates of inspection)
	 */
	bool operator<(Service &s) const;


};

typedef enum{poi, restaurant, lodging} classType;

class TouristicPoint {
private: 
	string closeDate;
	classType type;
public:
	/**
	* @brief Constructor for the touristicPoint class
	* @param closeDate 			close date of the touristic point
	* @param type	 			type of the touristic point
	*/
	TouristicPoint(string closeDate, classType type);
	/**
	* @brief Gets the close date of the touristic point
	* @return Returns the close date of the touristic point (empty string if it's not closed)
	*/
	string getCloseDate() const;
	/**
	* @brief Sets the close date of the touristic point
	* @param closeDate		The close date of the touristic point
	*/
	void setCloseDate(const string &closeDate);
	/**
	* @brief Gets the type of the touristic point
	* @return Returns the type of the touristic point (can be restaurant, poi or lodging)
	*/
	classType getType() const;
	/**
	* @brief Sets the type of the touristic point
	* @param type		The type of the touristic point (can be restaurant, poi or lodging)
	*/
	void setType(const classType type);
	/**
	* @brief Gets the name of the touristic point
	* @return Returns the name of the touristic point
	*/
	virtual string getName() const = 0;
	/**
	* @brief Overload for the insertion operator for the TouristicPoint class
	* @param o ostream to write to
	* @param t TouristicPoint to print
	* @return Returns the modified ostream
	*/
	friend ostream & operator<<(ostream &o, const TouristicPoint &t);
};

struct TouristicPointPointer {
	TouristicPoint *touristicPoint;
};

class Restaurant : public TouristicPoint {
private:
	string name;
	Schedule sch;
	Coordinates coords;
	string description;
	/**
	 * @brief Modifies the Restaurant name based on user inputs.
	 */
	void modifyName();
	/**
	 * @brief Modifies the Restaurant coordinates based on user inputs.
	 */
	void modifyCoordinates();
	/**
	 * @brief Modifies the Restaurant coordinates based on user inputs.
	 */
	void modifySchedule();
	/**
	 * @brief Modifies the Restaurant coordinates based on user inputs.
	 */
	void modifyDescription();
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
	* @brief Copy constructor for the Restaurant class
	* @param obj 			Object of class Restaurant to be copied
	*/
	Restaurant(const Restaurant &obj);
	/**
	 * @brief Gets the name of the Restaurant
	 * @return Returns the name of the Restaurant
	 */
	string getName() const;
	/**
	 * @brief Gets the coordinates of the Restaurant
	 * @return Returns the coordinates of the Restaurant
	 */
	Coordinates getCoordinates() const;
	/**
	 * @brief Gets the description of the Restaurant
	 * @return Returns the description of the Restaurant
	 */
	string getDescription() const;
	/**
	 * @brief Gets the schedule of the Restaurant
	 * @return Returns the schedule of the Restaurant
	 */
	Schedule getSchedule() const;
	/**
	 * @brief Sets the name of the Restaurant
	 * @param name The new name for the Restaurant
	 */
	void setName(const string &name);
	/**
	 * @brief Sets the schedule for the Restaurant
	 * @param sch The new schedule for the Restaurant
	 */
	void setSch(const Schedule &sch);
	/**
	 * @brief Sets the coordinates for the Restaurant
	 * @param coords The new coordinates for the Restaurant
	 */
	void setCoords(const Coordinates &coords);
	/**
	 * @brief Sets the description for the Restaurant
	 * @param description The new description for the Restaurant
	 */
	void setDescription(const string &description);
	/**
	 * @brief Overload for the insertion operator for the Restaurant class
	 * @param o ostream to write to
	 * @param r Restaurant to print
	 * @return Returns the modified ostream
	 */
	friend ostream & operator<<(ostream &o, const Restaurant &r);
	/**
	 * @brief passes data members to a string
	 * @return Returns a string with all data members
	 */
	string toString() const;
	/**
	 * @brief Modifies the Restaurant based on user input.
	 */
	void modifyRestaurant();
};

class POI : public TouristicPoint {
private:
	string name;
	Coordinates coords;
	string description;
	/**
	 * @brief Modifies the POI name based on user inputs.
	 */
	void modifyName();
	/**
	 * @brief Modifies the POI coordinates based on user inputs.
	 */
	void modifyCoordinates();
	/**
	 * @brief Modifies the POI coordinates based on user inputs.
	 */
	void modifyDescription();
public:
	/**
	 * @brief Constructor for the POI class
	 * @param name			The name of the POI
	 * @param coords		The coordinates of the POI
	 * @param description	The description of the POI, default value is "None"
	 */
	POI(string name, Coordinates coords, string description);
	/**
	* @brief Copy constructor for the POI class
	* @param obj 			Object of class POI to be copied
	*/
	POI(const POI &obj);
	/**
	 * @brief Gets the name of the POI
	 * @return Returns the name of the POI
	 */
	string getName() const;
	/**
	 * @brief Gets the coordinates of the POI
	 * @return Returns the coordinates of the POI
	 */
	Coordinates getCoordinates() const;
	/**
	 * @brief Gets the description of the POI
	 * @return Returns the description of the POI
	 */
	string getDescription() const;
	/**
	 * @brief Sets the name of the POI
	 * @param name The new name of the POI
	 */
	void setName(const string &name);
	/**
	 * @brief Sets the coordinates of the POI
	 * @param coords The new coordinates of the POI
	 */
	void setCoords(const Coordinates &coords);
	/**
	 * @brief Sets the description of the POI
	 * @param description The new description of the POI
	 */
	void setDescription(const string &description);
	/**
	 * @brief Overload for the insertion operator for the POI class
	 * @param o ostream to write to
	 * @param p POI to print
	 * @return Returns the modified ostream
	 */
	friend ostream & operator<<(ostream &o, const POI &p);
	/**
	 * @brief passes data members to a string
	 * @return Returns a string with all data members
	 */
	string toString() const;
	/**
	 * @brief Modifies the POI based on user input.
	 */
	void modifyPOI();
};

class Lodging : public TouristicPoint {
private:
	string name;
	Coordinates coords;
	bool full;
	string description;
	/**
	 * @brief Modifies the Lodging name based on user inputs.
	 */
	void modifyName();
	/**
	 * @brief Modifies the Loding coordinates based on user inputs.
	 */
	void modifyCoordinates();
	/**
	 * @brief Modifies the Loding full flag based on user inputs.
	 */
	void modifyFull();
	/**
	 * @brief Modifies the Lodging coordinates based on user inputs.
	 */
	void modifyDescription();
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
	* @brief Copy constructor for the Lodging class
	* @param obj 			Object of class Lodging to be copied
	*/
	Lodging(const Lodging &obj);
	/**
	 * @brief Sets the name of the Lodging
	 * @param name	New name of the lodging
	 */
	void setName(const string &name);
	/**
	 * @brief Sets the coordinates of the Lodging
	 * @param coords New coordinates of the Lodging
	 */
	void setCoords(const Coordinates &coords);
	/**
	 * @brief Sets if the Lodging is full or not
	 * @param full The new status of the Lodging
	 */
	void setFull(bool full);
	/**
	 * @brief Sets the description of the Lodging
	 * @param description The new description of the Lodging
	 */
	void setDescription(const string &description);
	/**
	 * @brief Gets the name of the Lodging
	 * @return Returns the name of the Lodging
	 */
	string getName() const;
	/**
	 * @brief Gets the coordinates of the Lodging
	 * @return Returns the coordinates of the Lodging
	 */
	Coordinates getCoordinates() const;
	/**
	 * @brief Gets if the Lodging is full or not
	 * @return Returns the "fullness" of the Lodging
	 */
	bool isFull() const;
	/**
	 * @brief Gets the description of the Lodging
	 * @return Returns the description of the Lodging
	 */
	string getDescription() const;
	/**
	 * @brief Overload for the insertion operator for the Lodging class
	 * @param o ostream to write to
	 * @param l Lodging to print
	 * @return Returns the modified ostream
	 */
	friend ostream & operator<<(ostream &o, const Lodging &l);
	/**
	 * @brief passes data members to a string
	 * @return Returns a string with all data members
	 */
	string toString() const;
	/**
	 * @brief Modifies the Lodging based on user input.
	 */
	void modifyLodging();
};
