#pragma once
#include "Beach.h"

class RiverBeach : public Beach {
	private:
		double width;
		double riverFlow;
		double maxDepth;
	public:
		/**
		* @brief Constructor for the River Beach class
		* @param name 				Name of the River Beach
		* @param coords 			Coordinates of the River Beach
		* @param maxCapacity 		Max capacity of the River Beach
		* @param blueFlag 			If the River Beach has blue flag
		* @param services			All the services in the River Beach
		* @param width				Width of the river
		* @param riverFlow			Flow of the river
		* @param maxDepth			Max depth of the river
		*/
		RiverBeach(string name, Coordinates coords, unsigned int maxCapacity, bool blueFlag, const vector <Service> &services, double width, double riverFlow, double maxDepth);
		/**
		* @brief get function of the river's max depth
		* @return Returns the river's max depth
		*/
		double getMaxDepth() const;
		/**
		* @brief set function of the river's max depth
		* @param maxDepth			Max depth of the river
		*/
		void setMaxDepth(double maxDepth);
		/**
		* @brief get function of the river's flow
		* @return Returns the river's flow
		*/
		double getRiverFlow() const;
		/**
		* @brief set function of the river's flow
		* @param riverFlow			Flow of the river
		*/
		void setRiverFlow(double riverFlow);
		/**
		* @brief get function of the river's width
		* @return Returns the river's width
		*/
		double getWidth() const;
		/**
		* @brief set function of the river's width
		* @param width				Width of the river
		*/
		void setWidth(double width);
		/**
		* @brief print of the River Beach information (overload of the vitual print function that belongs to the Beach class)
		* @param o		The ostream to write to
		*/
		void print(ostream &o);
};
