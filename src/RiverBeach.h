#pragma once
#include "Beach.h"

class RiverBeach : public Beach {
	private:
		double width;
		double riverFlow;
		double maxDepth;
	public:
	RiverBeach(string name, Coordinates cords, unsigned int maxCapacity, bool BlueFlag, vector <Service> services, double width, double riverFlow, double maxDepth);
	double getMaxDepth() const;
	void setMaxDepth(double maxDepth);
	double getRiverFlow() const;
	void setRiverFlow(double riverFlow);
	double getWidth() const;
	void setWidth(double width);

	friend ostream & operator<<(ostream &o, const RiverBeach & d);

};
