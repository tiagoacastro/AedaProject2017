#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Menu {
public:
	//NOTE: Menu.txt file location, change here if it doesn't work for you
	static string menutxt_defaultlocation;
	//TODO: Change the constructors to use exceptions because there is file I/O
	/**
	 * @brief Constructs a Menu object based on a text file and populates the options from it.
	 * @param path Path to the text file
	 */
	explicit Menu(string path);
	//Overload for the constructor to enable inputting the menu text directly
	/**
	 * @brief Constructs a Menu object based on direct input of string vector
	 * @param rawlines String vector, with each string representing a menu option
	 */
	explicit Menu(vector<string> rawlines);
	/**
	 * @brief Displays the whole Menu
	 */
	void DisplayWholeMenu();
	/**
	 * @brief Displays options based on given ID, printing all adjacent depths downards (1 returns 1, 1.1, 1.2, etc)
	 * @param id ID based on which to print adjacently downards
	 */
	void DisplayByID(string &id);
	/**
	 * @brief Default destructor
	 */
	~Menu();
private:
	/**
	 *	option is a struct to hold the data for each menu option
	 */
	struct option {
		string id; //id such as 1.1, 2.5, 1
		int depth_level; //how deep the option is nested: 1 is at the 0 level, 1.1 is at level 1 and so on
		string option_text; //the text to display alongside the option id: 1.1 <option_text>
	};

	/**
	 * vector containing all the options in the menu
	 */
	vector<option> menuOptions;

	/**
	 * @brief Interprets the line in format "<id> <text>"
	 * @param rawline The raw line to interpret
	 * @return Returns a valid 'option'
	 */
	option createOptionFromString(string rawline);

	/**
	 * @brief Finds a set of options based on the given ID,
	 * for example '1.' matches 1.1, 1.2, 1.3, etc.
	 * If the id is empty ("") it finds all the options with depth_level = 0
	 * @param id ID to search the options for
	 * @return returns the matched options
	 */
	vector<option> FindOptionByID(string id);
};

