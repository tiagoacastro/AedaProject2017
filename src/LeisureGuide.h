#pragma once
#include "Coordinates.h"
#include "Service.h"
#include "Beach.h"
#include "BayouBeach.h"
#include "RiverBeach.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

class LeisureGuide {
private:
	vector<pair<string, Beach*>> beaches;
	vector<Restaurant> restaurants;
	vector<POI> POIs;
	vector<Lodging> lodging;
	/**
	 * @brief Gets all the concelhos where there are beaches
	 * @return Returns a vector of all the Concelhos
	 */
	vector<string> getAllConcelhos() const;
	vector<Beach*> getBeachesByConcelho(const string &concelho) const;
	/**
	 * @brief Separate the string in all members of the class Beach
	 * @param beach		a line of the file opened with all informations about a beach
	 */
	void createBeach(string &beach);
	/**
	 * @brief for loop that chooses a line to add to member beachs
	 * @param beach		all lines of the file opened with all informations about the beaches
	 */
	void createBeach(vector<string> &beaches);
	/**
	 * @brief create and add to vector beaches a RiverBeach
	 * @param beach		vector with all RiverBeach private members separated
	 */
	void createRiverBeach(vector<string> &beach);
	/*
	 * @brief create and add to vector beaches a BayouBeach
	 * @param beach		vector with all BayourBeach private members separated
	 */
	void createBayouBeach(vector<string> &beach);
	/**
	 * @brief Separate the string in all members of the class Restaurant
	 * @param restaurant	a line of the file opened with all informations about a restaurant
	 */
	void createRestaurants(string &restaurant);
	/**
	 * @brief for loop that chooses a line to add to member restaurants
	 * @param restaurant	all lines of the file opened with all informations about the restaurants
	 */
	void createRestaurants(vector<string> &restaurant);
	/**
	 * @brief Separate the string in all members of the class POI
	 * @param poi	a line of the file opened with all informations about a point of interest
	 */
	void createPOI(string &poi);
	/**
	 * @brief for loop that chooses a line to add to member POIs
	 * @param poi		all lines of the file opened with all informations about the POI
	 */
	void createPOI(vector<string> &poi);
	/**
	 * @brief Separate the string in all members of the class Lodging
	 * @param lodging	a line of the file opened with all informations about a lodging
	 */
	void createLodging(string &lodging);
	/**
	 * @brief for loop that chooses a line to add to member lodging
	 * @param lodging		all lines of the file opened with all informations about the Lodging
	 */
	void createLodging(vector<string> &lodging);
	/**
	 * @brief allows the user to choose wich files he want to save
	 */
	void saveFile();
	/**
	 * @brief Write all Beaches to a file
	 * @param s		ofstream to write to
	 */
	void saveBeaches(ofstream &s);
	/**
		 * @brief Write all Restaurants to a file
		 * @param s		ofstream to write to
		 */
	void saveRestaurants(ofstream &s);
	/**
		 * @brief Write all POI to a file
		 * @param s		ofstream to write to
		 */
	void savePOI(ofstream &s);
	/**
		 * @brief Write all Lodging to a file
		 * @param s		ofstream to write to
		 */
	void saveLodging(ofstream &s);
	/**
	 * @brief searches a beach on the beaches vector and it returns the iterator
	 * @param name		name of the beach that will be searched
	 */
	vector<pair<string, Beach*>>::iterator findBeachByName(string name);
public:
	/**
	 * @brief Default constructor to allow creating an empty Leisure Guide that will receive the options afterwards
	 */
	LeisureGuide();
	/**
	 * @brief Constructs a Leisure Guide with a multimap containing all beaches and the respective county and no POIs, restaurants or lodging, they may be added later
	 * @param	 multimap containing all beaches and the respective county
	 */
	LeisureGuide(const vector<pair<string, Beach*>> &beaches);
	/**
	 * @brief Constructs a Leisure Guide with a multimap containing all beaches and the respective county as well as vectors, each containing the avaliable POIs, restaurants and lodging
	 * @param beaches		multimap containing all beaches and the respective county in the area
	 * @param restaurants	vector containing avaliable restaurants in the surrounding area
	 * @param POIs			vector containing avaliable points of interest (POIs) in the surrounding area
	 * @param lodging		vector containing avaliable lodging in the surrounding area
	 */
	LeisureGuide(const vector<pair<string, Beach*>> &beaches, const vector<Restaurant> &restaurants, const vector<POI> &POIs, const vector<Lodging> &lodging);
	/**
	 * @brief Displays all beaches by concelho
	 */
	void displayAllBeaches() const;
	/**
	 * @brief Displays all POIs
	 */
	void displayAllPOIs() const;
	/**
	 * @brief Displays all restaurants
	 */
	void displayAllRestaurants() const;
	/**
	 * @brief Displays all lodging
	 */
	void displayAllLodging() const;
	void loadFile();
	/**
	 * @brief Removes a beach from the beaches vector and deletes it
	 * @return true if beach is found and removed, false if else
	 */
	bool removeBeach();
	/**
	 * @brief Adds a beach to the beaches vector
	 * @return true if beach is valid and was added, false if else
	 */
	bool addBeach();
};
