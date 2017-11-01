#pragma once
#include "Beach.h"
#include <string>
#include <vector>

class BayouBeach : public Beach {
	private:
		double usableAquaticArea;
	public:
		BayouBeach(string name, Coordinates coords, unsigned int maxCapacity, bool blueFlag, const vector<Service> &services, double usableAquaticArea);
		double getUsableAquaticArea() const;
		void setUsableAquaticArea(double usableAquaticArea);
		friend ostream & operator<<(ostream &o, const BayouBeach &bb);
};
