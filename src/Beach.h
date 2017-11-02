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
		Beach(string name, Coordinates coords, unsigned int maxCapacity, bool blueFlag, const vector <Service> &services);
		bool hasBlueFlag() const;
		void setBlueFlag(bool blueFlag);
		Coordinates getCoords() const;
		unsigned int getMaxCapacity() const;
		void setMaxCapacity(unsigned int maxCapacity);
		string getName() const;
		void setName(const string &name);
		vector<Service> getServices() const;
		void setServices(const vector<Service> &services);
};

