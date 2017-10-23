#pragma once
#include <iostream>
using namespace std;

class Coordinates{
	private:
		double longitude;
		double latitude;
	public:
		Coordinates(double longitude, double latitude);
		double distanceTo();
};