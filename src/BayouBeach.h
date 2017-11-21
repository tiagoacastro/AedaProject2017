#pragma once
#include "Beach.h"
#include <string>
#include <vector>

class BayouBeach : public Beach {
	private:
		double usableAquaticArea;
	public:
		/**
		* @brief Constructor for the Bayou Beach class
		* @param name 				Name of the Bayou Beach
		* @param coords 			Coordinates of the Bayou Beach
		* @param maxCapacity 		Max capacity of the Bayou Beach
		* @param blueFlag 			If the Bayou Beach has blue flag
		* @param services			All the services in the Bayou Beach
		* @param usableAquaticArea	Usable aquatic area of the Bayou
		*/
		BayouBeach(string name, Coordinates coords, unsigned int maxCapacity, bool blueFlag, const vector<Service> &services, double usableAquaticArea);
		/**
		* @brief get function of the bayou's usable aquatic area
		* @return Returns the bayou's usable aquatic area
		*/
		double getUsableAquaticArea() const;
		/**
		* @brief set function of the bayou's usable aquatic area
		* @param usableAquaticArea	Usable aquatic area of the bayou
		*/
		void setUsableAquaticArea(double usableAquaticArea);
		/**
		* @brief print of the Bayou Beach information (overload of the vitual print function that belongs to the Beach class)
		* @param o		The ostream to write to
		*/
		void print(ostream &o);
		void modifyUsableAquaticArea();
		void modifyBeach();
};
