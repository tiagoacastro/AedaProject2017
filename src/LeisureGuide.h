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
	///Data members
	vector<pair<string, Beach*>> beaches;
	vector<Restaurant> restaurants;
	vector<POI> POIs;
	vector<Lodging> lodging;
	/**
	 * @brief Gets all the concelhos where there are beaches
	 * @return Returns a vector of all the Concelhos
	 */
	vector<string> getAllConcelhos() const;
	/**
	 * @brief Gets all the beaches for a given Concelho
	 * @param concelho Concelho to list beaches for
	 * @return Returns a vector of Beach* (as found in the beaches vector)
	 */
	vector<Beach*> getBeachesByConcelho(const string &concelho) const;
	void createBeach(string &beach);
	void createBeach(vector<string> &beaches);
	void createRiverBeach(vector<string> &beach);
	void createBayouBeach(vector<string> &beach);
	/**
	 * @brief Searches for a beach on the beaches vector and returns the iterator
	 * @param name		Name of the beach to search for
	 * @return Returns an iterator to the found beach, or beaches.end() if nothing was found
	 */
	vector<pair<string, Beach*>>::iterator findBeachByName(string name);
	/**
	 * @brief Searches for a POI on the POI vector and returns the iterator
	 * @param name		Name of the POI to search for
	 * @return Returns an iterator to the found POI, or POIs.end() if the POI was not found
	 */
	vector<POI>::iterator findPOIByName(const string &name);
	/**
	 * @brief Searches for a Restaurant on the Restaurants vector and returns the iterator
	 * @param name 		Name of the Restaurant to search for
	 * @return Returns an iterator to the found Restaurant, or restaurants.end() if the Restaurant was not found
	 */
	vector<Restaurant>::iterator findRestaurantByName(const string &name);
	/**
	 * @brief Searches for Lodging on the lodging vector and returns the iterator
	 * @param name 		Name of the Lodging to search for
	 * @return Returns an iterator to the found Lodging, or lodging.end() if the Lodging was not found
	 */
	vector<Lodging>::iterator findLodgingByName(const string &name);
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
	* @brief Removes a Beach from the Beaches vector and deletes it
	* @return true if beach is found and removed, false if else
	*/
	bool removeBeach();
	/**
	 * @brief Modifies a Beach based on its name
	 * @return returns true if a beach is found and modified, false if not found
	 */
	bool modifyBeach();
	/**
	* @brief Adds a beach to the beaches vector
	* @return true if beach is valid and was added, false if else
	*/
	bool addBeach();
	/**
	 * @brief Removes a POI from the POIs vector
	 * @return true if a POI is found and removed, false if otherwise
	 */
	bool removePOI();
	/**
	 * @brief Removes a Restaurant from the Restaurants vector
	 * @return true if a Restaurant is found and removed, false if otherwise
	 */
	bool removeRestaurant();
	/**
	 * @brief Removes a Lodging from the lodging vector
	 * @return true if a Lodging is found and removed, false if otherwise
	 */
	bool removeLodging();
	/**
	* @brief Adds a restaurant to the restaurants vector
	* @return true if restaurant is valid and was added, false if else
	*/
	bool addRestaurant();
	/**
	* @brief Adds a POI to the POIs vector
	* @return true if POI is valid and was added, false if else
	*/
	bool addPOI();
	/**
	* @brief Adds Lodging to the lodging vector
	* @return true if the Lodging is valid and was added, false if else
	*/
	bool addLodging();
};
