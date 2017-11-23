#pragma once
#include <iostream>
#include <cmath>
using namespace std;

class Coordinates{
	private:
		double longitude;
		double latitude;
	public:
		/**
		* @brief Constructor for the Coordinates class
		* @param longitude 			longitude (x)
		* @param latitude 			latitude  (y)
		*/
		Coordinates(double longitude, double latitude);
		/**
		* @brief get function of the coordinates' longitude
		* @return Returns the coordinates' longitude
		*/
		double getLongitude() const;
		/**
		* @brief get function of the coordinates' latitude
		* @return Returns the coordinates' latitude
		*/
		double getLatitude() const;
		/**
		* @brief calculates the distance to another set of Coordinates
		* @param coords			set of coordinates to calculate the distance to
		* @return Returns the distance to the other set of coordinates
		*/
		double distanceTo(Coordinates coords);
		/**
		 * @brief Insertion operator overload for Coordinates class. Prints in the following format: "(latitude , longitude)"
		 * @param os ostream to write to
		 * @param c passed in Coordinates object
		 * @return Modified ostream, as is expected of this operator
		 */
		friend ostream & operator<<(ostream &os, const Coordinates &c);
		/**
		 * @brief Set function for the Coordinate's latitude
		 * @param lat The latitude for the Coordinate
		 */
		void setLatitude(double lat);
		/**
		 * @brief Set function for the Coordinate's longitude
		 * @param longit The longitude for the Coordinate
		 */
		void setLongitude(double longit);
		/**
		* @brief passes data member to a string
		 * @return Returns a string with all data members
		 */
		string toString() const;
};

