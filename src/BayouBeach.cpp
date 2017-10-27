#include "BayouBeach.h"
using namespace std;

BayouBeach::BayouBeach(string name, Coordinates cords, unsigned int maxCapacity, bool BlueFlag, vector <Service> services, double usableAquaticArea)
	:Beach(name,cords,maxCapacity, BlueFlag,services), usableAquaticArea(usableAquaticArea){}

