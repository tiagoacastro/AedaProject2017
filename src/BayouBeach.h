#pragma once
#include "Beach.h"

class BayouBeach : public Beach {
	private:
		double usableAquaticArea;
    public:
		BayouBeach(string name, Coordinates cords, unsigned int maxCapacity, bool BlueFlag, vector <Service> services, double usableAquaticArea);
};