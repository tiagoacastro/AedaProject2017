#pragma once
#include "LeisureGuide.h"

LeisureGuide::LeisureGuide() {
}

LeisureGuide::LeisureGuide(multimap<string, Beach *> beaches):
	beaches(beaches) {
}

LeisureGuide::LeisureGuide(multimap<string, Beach *> beaches, vector<Restaurant> restaurants, vector<POI> POIs, vector<Lodging> lodging):
	beaches(beaches), restaurants(restaurants), POIs(POIs), lodging(lodging) {
}

