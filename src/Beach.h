#pragma once
#include "Coordinates.h"
#include "Service.h"

class Beach {
	private:
		string name;
		Coordinates cords;
		unsigned int maxCapacity;
		bool BlueFlag;
		vector <Service> services;
	public:
		Beach(string name, Coordinates cords, unsigned int maxCapacity, bool BlueFlag, vector <Service> services);
};