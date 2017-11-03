#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <iostream>
#include <iomanip>

using namespace std;

//Utilities is a namespace created to contain useful functions for use throughout the program
namespace Utilities {
	//Reads a file and returns a vector in which each position is a string representing a line in the file
	vector<string> ReadFile(string path);
	//Overload for ReadFile this time using an open ifstream
	vector<string> ReadFile(ifstream &input);
	//Counts the number of occurrences of a char in a string, useful for Menu's option.depth_level
	int countCharInString(string input, char searchchar);
	//Compares two strings with different sizes by going through the smaller one until it ends,
	//if all the characters match until then, returns true
	bool compareDiffSizeStrings(string a, string b);
	//Remove whitespace surrounding text  - "   aa  " -> "aa"
	void trimString(string &s);
	//Print vector of any kind of element as long as it has << operator defined
	template<typename T>
	void printVector(const vector<T> &v) {
		for (int i = 0; i < v.size(); i++) {
			cout << i << ": " << v[i] << endl;
		}
	}

	//Split a string into a string vector on each ocurrence of another string
	vector<string> splitString(string input, string splitter);
	//Overload for a single char - calls the string version
	vector<string> splitString(string input, char splitter);
	//Clears the screen - originally inside Menu
	void clearScreen();
	//Pauses the program until enter is pressed - displays informative message to prompt the user to press enter. Warning: to pause successfully this function must clear the whole cin buffer, make sure there is no important data there
	void pause();

	//Removes duplicate elements in a vector - using templates so that it works for any kind of element
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
		 */
	}

	//Intersects two vectors, searching for common values - using templates so that it works for any kind of element
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

	//Converts minutes to a string in the HH:MM format
	string minutesToHHMM(unsigned int minutes);
	//Overload of the above for vectors, in order to better organize code
	vector<string> minutesToHHMM(const vector<int> &minutes);
	//Rounds double to nearest integer (works with negative values)
	int roundToInt(double input);

	//Converts minutes to a struct of an int (weekday) and a string in the HH:MM format
	struct time {
		int weekday;
		string hourAndMinutes;
	};
	time minutesToTime(int minutes);
	//Overload of the above for vectors
	vector<time> minutesToTime(const vector<int> &minutes);
	//Vector to give a string that represents the week day from the weekday variable in a shift
	const vector<string> weekdays = { "Segunda-feira", "Ter�a-feira", "Quarta-feira", "Quinta-feira", "Sexta-feira", "S�bado", "Domingo" };

	//Joins the elements of vectors of the same type (not deleting potential duplicates)
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

	//Converts string in HH:MM format to minutes
	unsigned int HHMMtoMinutes(string hhmm);

	//For use in exception throwing in file handling
	class FileNotFound{
	private:
		string path;
	public:
		explicit FileNotFound(const string &path) : path(path){};
		string getPath() const{return path;}
	};
}