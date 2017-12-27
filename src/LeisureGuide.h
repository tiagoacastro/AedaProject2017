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
#include <queue>
#include <algorithm>

using namespace std;

struct set_comparator {
	bool operator() (const pair<string, Beach *> &p1, const pair<string, Beach *> &p2) {
		if(p1.first == p2.first) {
			if(p1.second->hasBlueFlag()) {
				return true;
			} else {
				if(p2.second->hasBlueFlag()) {
					return false;
				} else {
					return p1.second->getName() < p2.second->getName();
				}
			}
		}
		return p1.first < p2.first;
	}
};

struct pq_compare {
	bool operator() (const pair<Service*, string> &s1, const pair<Service*, string> &s2) {
		return s1.first->getInspectionDate() < s2.first->getInspectionDate();
	}

};


typedef set<pair<string, Beach *>, set_comparator> ConcelhoBeachBST;
typedef priority_queue<pair<Service*, string>, vector<pair<Service*, string>>,pq_compare> Inspection;

class LeisureGuide {
private:
	///Data members
	ConcelhoBeachBST beaches;
	vector<Restaurant> restaurants;
	vector<POI> POIs;
	vector<Lodging> lodging;
	vector<Inspection> dates;
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

	/**
	 * @brief Searches for a beach on the beaches vector and returns the iterator
	 * @param name		Name of the beach to search for
	 * @return Returns an iterator to the found beach, or beaches.end() if nothing was found
	 */
	ConcelhoBeachBST::iterator findBeachByName(string name);
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
	/**
	 * @brief Sorts Lodging, Restaurants and POIs by distance to a certain beach
	 * @param b The beach in order to sort to
	 */
	void sortEverythingByDistanceToBeach(Beach *b);
	/**
	 * @brief Sorts Restaurants by distance to a certain beach
	 * @param b The beach in order to sort to
	 */
	void sortRestaurantsByDistanceToBeach(Beach *b);
	/**
	 * @brief Sorts POIs by distance to a certain beach
	 * @param b The beach in order to sort to
	 */
	void sortPOIsByDistanceToBeach(Beach *b);
	/**
	 * @brief Sorts Lodging by distance to a certain beach
	 * @param b The beach in order to sort to
	 */
	void sortLodgingByDistanceToBeach(Beach *b);
	
	//TODO
	/**
	* @brief insert the date changed in the Dates
	* @param beachName Name of the beach that has the service to be inspectionated
	* @param serviceName Name of the service that is going to be inspectionated
 	*/
	void updateInspections(Service *s, string &beachName); 

	/**
	* @brief Check if the type passed as argument already exist in dates
	* @param type Type of the service
	* @return Return the index of the type or -1 if the type does not exist
	*/
	int checkType(const string &type);
	
	/**
	* @brief Create the inspection based in the current beaches
	*/
	
	void createInspections();
public:


	/**
	* @brief Get of the vector of inspections
	* @return Return the vectors of inspection  
	*/
	vector<Inspection> getDates();
	/**
	 * @brief Default constructor to allow creating an empty Leisure Guide that will receive the options afterwards
	 */
	LeisureGuide();
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
	/**
	 * @brief Displays the POIs, Restaurants and Lodging closest to a certain beach
	 */
	void displaySortedByDistance();
	/**
	 * @brief Displays the beaches for a certain concelho
	 */
	void displayBeachesByConcelho();
	/**
	 * @brief Displays detailed information for a certain beach, requested by its name
	 */
	void displayBeachInfo();
	/**
	 * @brief Displays detailed information for a certain POI, requested by its name
	 */
	void displayPOIInfo();
	/**
	 * @brief Displays detailed information for a certain Restaurant, requested by its name
	 */
	void displayRestaurantInfo();
	/**
	 * @brief Displays detailed information for a certain Lodging, requested by its name
	 */
	void displayLodgingInfo();
	/**
	* @brief Display the Inspections of the all services of a Beach entered by the user
	*/
	void displayInspectionofaBeach();
	/**
	* @brief Display the Inspections of the all services of a type entered by the user
	*/
	void displayInspectionTypeService();
	/**
	 * @brief Loads file contents into program memory
	 */
	void loadFile();
	/**
	 * @brief Removes and deletes a beach from the beaches vector based on a given name
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
	/**
	* @brief Adds an Inspection to a service entered by the user
	* @return true if the Inspection is valid and was added, false if else
	*/
	bool addInspection();
	/**
	 * @brief Modifies a Restaurant based on its name
	 * @return returns true if a Restaurant is found and modified, false if not found
	 */
	bool modifyRestaurant();
	/**
	 * @brief Modifies a POI based on its name
	 * @return returns true if a POI is found and modified, false if not found
	 */
	bool modifyPOI();
	/**
	 * @brief Modifies a Lodging based on its name
	 * @return returns true if a Lodging is found and modified, false if not found
	 */
	bool modifyLodging();
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
	/**
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
	 * @brief Saves the program runtime contents to a file, chosen based on user input
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
};
