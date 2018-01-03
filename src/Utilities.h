#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <iostream>
#include <iomanip>
#include <queue>

using namespace std;

/**
 * @brief Utilities is a namespace created to contain useful functions for use throughout the program
 * @addtogroup Utilities
 * @{
 */
namespace Utilities {
	/**
	 * @brief Reads a file and returns its contents
	 * @param path The path of the file to read
	 * @return Returns a vector in which each position is a string representing a line in the file
	 */
	vector<string> ReadFile(string path);
	/**
	 * @brief Overload for ReadFile this time using an open ifstream
	 * @param input The open ifstream from which to read to
	 * @return Returns a vector in which each position is a string representing a line in the read file
	 */
	vector<string> ReadFile(ifstream &input);
	/**
	 * @brief Counts the number of occurrences of a char in a string, useful for Menu's option.depth_level
	 * @param input The string where the counting will ocurr
	 * @param searchchar The character to search for
	 * @return The number of occurrences of searchchar in input
	 */
	int countCharInString(string input, char searchchar);
	/**
	 * @brief Compares two strings with different sizes by going through the smaller one until it ends, if all the characters match until then, returns true
	 * @param a First string to compare
	 * @param b Second string to compare
	 * @return True if characters match until the smaller string ends
	 */
	bool compareDiffSizeStrings(string a, string b);
	/**
	 * @brief Remove whitespace surrounding text  - "   aa  " -> "aa"
	 * @param s The string in which to remove the whitespace
	 */
	void trimString(string &s);
	/**
	 * @brief Prints vector of any kind of element as long as it has the << operator defined
	 * @tparam T Generic type of element to print
	 * @param v Vector of elements to print
	 */
	template<typename T>
	void printVector(const vector<T> &v) {
		for (int i = 0; i < v.size(); i++) {
			cout << i << ": " << v[i] << endl;
		}
	}

	/**
	 * @brief Prints priority queue of any kind of element as long as it has the << operator defined NOTE: Copies the priority queue because it has no direct access to members otherwise
	 * @tparam T Generic type of element to print
	 * @param pq Priority queue of elements to print
	 */
	template<typename T>
	void printPriorityQueue(const priority_queue<T> &pq) {
		priority_queue<T> aux(pq);
		unsigned int i = 0;
		while(!aux.empty()) {
			cout << "i: " << i << "\t" << pq.top() << endl;
			i++;
			pq.pop();
		}
	}

	/**
	 * @brief Splits a string into a string vector on each ocurrence of another string
	 * @param input String to split
	 * @param splitter String for which to search
	 * @return Returns a vector of 'input', split at every ocurrence of 'splitter'
	 */
	vector<string> splitString(string input, string splitter);
	/**
	 * @brief splitString overload for a single char - calls the string version. Splits a string into a string vector on each ocurrence of another char
	 * @param input String to split
	 * @param splitter Character for which to search
	 * @return Returns a vector of 'input', split at every ocurrence of 'splitter'
	 */
	vector<string> splitString(const string &input, char splitter);
	/**
	 * @brief Clears the screen
	 */
	void clearScreen();
	/**
	 * @brief Pauses the program until enter is pressed - displays informative message to prompt the user to press enter. Warning: to pause successfully this function must clear the whole cin buffer, make sure there is no important data there
	 */
	void pause();

	/**
	 * @brief Removes duplicate elements in a vector
	 * @tparam T Generic type of vector element
	 * @param v The vector in which to remove duplicates
	 */
	template<typename T>
	void removeDuplicates(vector<T> &v) {
		for (int i = 0; i < v.size(); i++) {
			//Searching for a duplicate element
			for (int j = i + 1; j < v.size(); j++) {
				//If found deletes the occurrence at j
				if (v[i] == v[j]) {
					v.erase(v.begin() + j);
					//j-- because the element at j was deleted so j+1 is now j, if we increment directly then we are skipping an element
					j--;
				}
			}
		}

		/*
		//Another idea:
		set<T> output;

		for (int i = 0; i < v.size(); i++) {
			output.insert(v[i]);
		}

		v.clear();

		for(auto const &uniqueelem : output){
			v.push_back(uniqueelem);
		}
		//Or better yet, use copy constructor with begin and end iterators
		 */
	}

	/**
	 * @brief Intersects two vectors, searching for common values
	 * @tparam T Generic type of vector
	 * @param v1 First vector
	 * @param v2 Second vector
	 * @return Returns the intersection of all the elements of v1 and v2
	 */
	template<typename T>
	vector<T> intersectVectors(const vector<T> &v1, const vector<T> &v2) {
		//Initializing empty output vector
		vector<T> output;

		//Intersecting
		for (int i = 0; i < v1.size(); i++) {
			for (int j = 0; j < v2.size(); j++) {
				if (v1[i] == v2[j])
					output.push_back(v1[i]);
			}
		}

		//Removing duplicate elements
		Utilities::removeDuplicates<T>(output);

		return output;
	}

	/**
	 * @brief Converts minutes to a string in the HH:MM format
	 * @param minutes Number of minutes to convert
	 * @return Returns a string in the HH:MM based on the number of minutes given
	 */
	string minutesToHHMM(unsigned int minutes);
	/**
	 * @brief Rounds double to nearest integer (works with negative values)
	 * @param input Double to round
	 * @return Returns the rounded value
	 */
	int roundToInt(double input);


	struct time {
		int weekday;
		string hourAndMinutes;
	};

	/**
	 * @brief Converts minutes to a struct of an int (weekday) and a string in the HH:MM format
	 * @param minutes Number of total minutes to convert to time struct
	 * @return Returns the resulting time struct
	 */
	time minutesToTime(int minutes);
	/**
	 * @brief Vector to represent the days of the week
	 */
	const static vector<string> weekdays = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

	/**
	 * @brief Joins the elements of vectors of the same type (not deleting potential duplicates)
	 * @tparam T Generic vector item type
	 * @param v1 First vector
	 * @param v2 Second vector
	 * @return Returns a vector of all the elements of v1 and v2, without deleting duplicates
	 */
	template<typename T>
	vector<T> joinVectors(const vector<T> &v1, const vector<T> &v2) {
		//Creating output vector and preallocating memory
		vector<T> output;
		output.reserve(v1.size() + v2.size());

		//Inserting the elements
		output.insert(output.end(), v1.begin(), v1.end());
		output.insert(output.end(), v2.begin(), v2.end());

		//Returning the result
		return output;
	}

	/**
	 * @brief Converts string in HH:MM format to minutes
	 * @param hhmm String in the HH:MM format
	 * @return Returns the number of minutes that the HH:MM string corresponds to
	 */
	unsigned int HHMMtoMinutes(string hhmm);
	/**
	* @brief Checks if string is in HH:MM format
	* @param hour		String to analyze
	* @return Returns true if it's in the desired format, false if else
	*/
	bool correctHourFormat(const string &hour);
	/**
	* @brief Checks if string is in YYYY/MM/DD format
	* @param la		String to analyze
	* @return Returns true if it's in the desired format, false if else
	*/
	bool correctDateFormat(const string &la);
	/**
	* @brief Checks if arguments are in YYYY/MM/DD format and if the l is younger than r
	* @param l Date in the format YYYY/MM/DD
	* @param r Date in the format YYYY/MM/DD
	* @return Returns true if l is younger than r, false if else 
	*/
	bool DatesCompare(const string &l, const string &r);
	/**
	* @brief Checks if character is a number
	* @param c			Character to analyze
	* @return Returns true if it's a number, false if else
	*/
	bool isNumber(char c);
	/**
	 * @brief Clears cin buffer and error flags, for use after each cin use as a stream, to make sure the following getlines work
	 */
	void clearCinBuffer();
	/**
	 * @brief FileNotFound exception (For use in exception throwing in file handling)
	 */
	class FileNotFound{
	private:
		string path;
	public:
		explicit FileNotFound(const string &path) : path(path){};
		string getPath() const{return path;}
	};
	/**
	 * @brief WrongFileFormat exception (For use in exception throwing in file reading, when it has an invalid format
	 */
	class WrongFileFormat{
	private:
		string filetype;
	public:
		explicit WrongFileFormat(const string &filetype) : filetype(filetype){};
		string getType() const {return filetype;}
	};
}
/*! @} End of Doxygen Utilities group*/