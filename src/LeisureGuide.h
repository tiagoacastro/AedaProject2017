#pragma once

#include <map>
#include "Beach.h"

class PointOfInterest;
class Restaurant;
class Lodging;


class LeisureGuide{
private:
	/**
	 * Holds the beaches that exist in the Leisure Guide.
	 * The string is representative of the name of the 'Concelho'
	 */
	multimap<string, Beach*> beaches;
	vector<PointOfInterest> pointsOfInterest;
	vector<Restaurant> restaurants;
	vector<Lodging> lodging;
public:
	LeisureGuide();
};

//TODO: Further develop these 3 classes

class PointOfInterest{
private:
	string name;
public:
	PointOfInterest(const string &name);
	friend ostream& operator <<(ostream &os, const PointOfInterest &poi);
};

class Restaurant{
private:
	string name;
public:
	Restaurant(const string &name);
	friend ostream& operator <<(ostream &os, const Restaurant &r);
};

class Lodging{
private:
	string name;
public:
	Lodging(const string &name);
	friend ostream& operator <<(ostream &os, const Lodging &l);
};