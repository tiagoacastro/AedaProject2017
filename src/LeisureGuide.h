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
	/**
	* @brief Default constructor to allow creating an empty Leisure Guide that will receive the options afterwards
	*/
	LeisureGuide();
	/**
	* @brief Constructs a Leisure Guide with a multimap containing all beaches and the respective county and no POIs, restaurants or lodging, they may be added later
	* @param	 multimap containing all beaches and the respective county
	*/
	LeisureGuide(multimap<string, Beach *> beaches);
	/**
	* @brief Constructs a Leisure Guide with a multimap containing all beaches and the respective county as well as vectors, each containing the avaliable POIs, restaurants and lodging
	* @param beaches		multimap containing all beaches and the respective county in the area
	* @param restaurants	vector containing avaliable restaurants in the surrounding area
	* @param POIs			vector containing avaliable points of interest (POIs) in the surrounding area
	* @param lodging		vector containing avaliable lodging in the surrounding area
	*/
	LeisureGuide(multimap<string, Beach *> beaches, vector<Restaurant> restaurants, vector<POI> POIs, vector<Lodging> lodging);
};
