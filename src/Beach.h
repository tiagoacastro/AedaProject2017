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
protected:
	/**
	 * @brief Modifies the Beach name based on user inputs. Is in protected access scope because it needs not be public but the derivate classes should be able to access it.
	 */
	void modifyName();
	/**
	 * @brief Modifies the Beach coordinates based on user inputs. Is in protected access scope because it needs not be public but the derivate classes should be able to access it.
	 */
	void modifyCoordinates();
	/**
	 * @brief Modifies the Beach maximum capacity based on user inputs. Is in protected access scope because it needs not be public but the derivate classes should be able to access it.
	 */
	void modifyMaxCapacity();
	/**
	 * @brief Modifies the Beach blue flag based on user inputs. Is in protected access scope because it needs not be public but the derivate classes should be able to access it.
	 */
	void modifyBlueFlag();
	/**
	 * @brief Modifies the Beach services based on user inputs. Is in protected access scope because it needs not be public but the derivate classes should be able to access it.
	 */
	void modifyServices();
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
	 * @brief Get function for the beach's blueFlag
	 * @return Returns true if the beach has blue flag, false if not
	 */
	bool hasBlueFlag() const;
	/**
	 * @brief Set function for the beach's blue flag
	 * @param blueFlag 		If the beach has blue flag
	 */
	void setBlueFlag(bool blueFlag);
	/**
	 * @brief Get function for the beach's coordinates
	 * @return Returns the beach's coordinates
	 */
	Coordinates getCoords() const;

	/**
	 * @brief Set function of the beach's Coordinates
	 * @param coords 	Coordinates of the Beach
	 */
	void setCoordinates(const Coordinates &coords);

	/**
	 * @brief Get function of the beach's max capacity
	 * @return Returns the beach's max capacity
	 */
	unsigned int getMaxCapacity() const;
	/**
	 * @brief Set function for the beach's max capacity
	 * @param maxCapacity 	Max capacity of the Beach
	 */
	void setMaxCapacity(unsigned int maxCapacity);
	/**
	 * @brief Get function for the beach's name
	 * @return Returns the beach's name
	 */
	string getName() const;
	/**
	 * @brief Set function for the beach's name
	 * @param name 			Name of the Beach
	 */
	void setName(const string &name);
	/**
	 * @brief Get function for the services of the beach
	 * @return Returns the beach's service vector
	 */
	vector<Service> getServices() const;
	/**
	 * @brief Set function for the services of the beach
	 * @param services		All the services in the Beach
	 */
	void setServices(const vector<Service> &services);
	/**
	 * @brief Print of the Beach information (virtual so BayouBeach and RiverBeach can have their versions of the print)
	 * @param o		The ostream to write to
	 */
	virtual void print(ostream &o);
	/**
	 * @brief Modifies the Beach based on user input. Is pure virtual due to each Beach having different fields that can be changed
	 */
	virtual void modifyBeach() = 0;
	/**
	 * @brief Beach virtual destructor (so that delete works for derivate classes)
	 */
	virtual ~Beach();
};

