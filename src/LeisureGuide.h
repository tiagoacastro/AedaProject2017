#pragma once
#include "Coordinates.h"
#include "Service.h"
#include "Beach.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>

class LeisureGuide {
private:
	multimap<string, Beach *> beaches;
	vector<Restaurant> restaurants;
	vector<POI> POIs;
	vector<Lodging> lodging;
public:
	LeisureGuide();
	LeisureGuide(multimap<string, Beach *> beaches);
	LeisureGuide(multimap<string, Beach *> beaches, vector<Restaurant> restaurants, vector<POI> POIs, vector<Lodging> lodging);
	void displayAllBeaches() const;
};
