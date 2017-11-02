#include "Coordinates.h"

Coordinates::Coordinates(double longitude, double latitude):
	longitude(longitude), latitude(latitude){}

double Coordinates::getLongitude() const {
	return longitude;
}

double Coordinates::getLatitude() const {
	return latitude;
}

double Coordinates::distanceTo(Coordinates coords) {
	double x = coords.getLongitude() - longitude;
	double y = coords.getLatitude() - latitude;
	return sqrt(x*x + y*y);
}