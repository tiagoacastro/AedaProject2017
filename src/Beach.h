#pragma once
#include "Coordinates.h"
#include "Service.h"
#include <iostream>
#include <string>
#include <vector>

class Beach {
private:
	string name;
	Coordinates coords;
	unsigned int maxCapacity;
	bool blueFlag;
	vector <Service> services;
public:
	/**
	 * @brief Constructor for the Beach class
	 * @param name 			Name of the Beach
	 * @param coords 		Coordinates of the Beach
	 * @param maxCapacity 	Max capacity of the Beach
	 * @param blueFlag 		If the Beach has blue flag
	 * @param services		All the services in the Beach
	 */
	Beach(string name, Coordinates coords, unsigned int maxCapacity, bool blueFlag, const vector <Service> &services);
	/**
	 * @brief get function of the beach's blueFlag private member to know if the beach has flue flag
	 * @return Returns true if the beach has blue flag, false if not
	 */
	bool hasBlueFlag() const;
	/**
	 * @brief set function of the beach's blue flag
	 * @param blueFlag 		If the beach has blue flag
	 */
	void setBlueFlag(bool blueFlag);
	/**
	 * @brief get function of the beach's coordinates
	 * @return Returns the beach's coordinates
	 */
	Coordinates getCoords() const;

	/**
	 * @brief set function of the beach's Coordinates
	 * @param coordinates 	Coordinates of the Beach
	 */
	void setCoordinates(Coordinates coordinates);

	/**
	 * @brief get function of the beach's max capacity
	 * @return Returns the beach's max capacity
	 */
	unsigned int getMaxCapacity() const;
	/**
	 * @brief set function of the beach's max capacity
	 * @param maxCapacity 	Max capacity of the Beach
	 */
	void setMaxCapacity(unsigned int maxCapacity);
	/**
	 * @brief get function of the beach's name
	 * @return Returns the beach's name
	 */
	string getName() const;
	/**
	 * @brief set function of the beach's name
	 * @param name 			Name of the Beach
	 */
	void setName(const string &name);
	/**
	 * @brief get function of the services of the beach
	 * @return Returns the beach's service vector
	 */
	vector<Service> getServices() const;
	/**
	 * @brief set function of the services of the beach
	 * @param services		All the services in the Beach
	 */
	void setServices(const vector<Service> &services);
	/**
	 * @brief print of the Beach information (virtual so BayouBeach and RiverBeach can have their version of the print)
	 * @param o		The ostream to write to
	 */
	virtual void print(ostream &o);

	virtual void modifyBeach() = 0;
	/**
	´* @brief beach destructor
	 */
	virtual ~Beach();
};

