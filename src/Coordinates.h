#pragma once
#include <iostream>
#include <cmath>
using namespace std;

class Coordinates{
	private:
		double longitude;
		double latitude;
	public:
		Coordinates(double longitude, double latitude);
		double getLongitude() const;
		double getLatitude() const;
		double distanceTo(Coordinates coords);
		/**
		 * @brief Insertion operator overload for Coordinates class. Prints in the following format: "(latitude , longitude)"
		 * @param os ostream to write to
		 * @param c passed in Coordinates object
		 * @return Modified ostream, as is expected of this operator
		 */
		friend ostream & operator<<(ostream &os, const Coordinates &c);
};
