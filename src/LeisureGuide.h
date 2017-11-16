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
	void createBeach(string &beach);
	void createBeach(vector<string> &beaches);
	void createRiverBeach(vector<string> &beach);
	void createBayouBeach(vector<string> &beach);
	void addRestaurants(vector<string> &infos);
	void createRestaurants(string &restaurant);
	void createRestaurants(vector<string> &restaurant);
	void addPOI(vector <string> &infos);
	void createPOI(string &poi);
	void createPOI(vector<string> &poi);
	void addLodging(vector <string> &infos);
	void createLodging(string &lodging);
	void createLodging(vector<string> &lodging);
	void saveFile();
	void saveBeaches(ofstream &s);
	void saveRestaurants(ofstream &s);
	void savePOI(ofstream &s);
	void saveLodging(ofstream &s);
	void saveFormatb(pair<string, Beach*> &s, string &format);
	void saveFormatRestaurants(int &i , string &format);
	void saveFormatPOIs(int &i, string &format);
	void saveFormatLodging(int &i, string &format);


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
