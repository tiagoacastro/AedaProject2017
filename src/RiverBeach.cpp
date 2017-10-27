#include "RiverBeach.h"

using namespace std;

RiverBeach::RiverBeach(string name, Coordinates cords, unsigned int maxCapacity, bool BlueFlag, vector <Service> services, double width, double riverFlow, double maxDepth)
	: Beach(name, cords, maxCapacity, BlueFlag, services), width(width), riverFlow(riverFlow), maxDepth(maxDepth){}
