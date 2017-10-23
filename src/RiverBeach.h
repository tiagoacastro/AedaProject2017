#pragma once
#include "Beach.h"

class RiverBeach : public Beach {
	private:
		double width;
		double riverFlow;
		double maxDepth;
	public:
		RiverBeach(string name, Coordinates cords, unsigned int maxCapacity, bool BlueFlag, vector <Service> services, double width, double riverFlow, double maxDepth);
};