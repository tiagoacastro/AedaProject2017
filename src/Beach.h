#pragma once
#include "Coordinates.h"
#include "Service.h"
#include <iostream>

class Beach {
	private:
		string name;
		Coordinates cords;
		unsigned int maxCapacity;
		bool BlueFlag;
		vector <Service> services;

	public:
	Beach(string name, Coordinates cords, unsigned int maxCapacity, bool BlueFlag, vector <Service> services);
	bool isBlueFlag() const;
	void setBlueFlag(bool blueFlag);
	const Coordinates& getCords() const;
	unsigned int getMaxCapacity() const;
	void setMaxCapacity(unsigned int maxCapacity);
	const string& getName() const;
	void setName(const string& name);
	const vector<Service>& getServices() const;
	void setServices(const vector<Service>& services);

};

