#include "Beach.h"

using namespace std;

Beach::Beach(string name, Coordinates cords, unsigned int maxCapacity, bool BlueFlag, vector <Service> services)
	:name(name), cords(cords), maxCapacity(maxCapacity), BlueFlag(BlueFlag), services(services){}
