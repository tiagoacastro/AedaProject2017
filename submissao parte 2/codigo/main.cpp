
#include <iostream>
#include <string>
#include <clocale>
#include "Menu.h"
#include "Utilities.h"
#include "LeisureGuide.h"

using namespace std;

#ifdef _WIN32
#include "Windows.h"
#define enablePTcharacters() SetConsoleCP(1252); SetConsoleOutputCP(1252);
#else
#define enablePTcharacters() setlocale(LC_ALL, "Portuguese");
#endif

//Prototypes
int menuRunner(LeisureGuide &lg);
bool callFunctions(string &id, LeisureGuide &lg);

int main() {

	//Enabling portuguese characters on the console - function defined above
	enablePTcharacters();
	//This should work in theory, if it does not work, which was my case, please comment out the function and uncomment the next line
	//setlocale(LC_ALL, "Portuguese");

	//Ensuring that pause is possible with cin.get
	// by allowing getting if there is anything in the buffer with cin.rdbuf()->in_avail()
	// (This was disabled by some compilers, was my case as well)
	cin.sync_with_stdio(false);

	//Init
	LeisureGuide lg;

	/*
	 * TODO:
	 * The old code used to call a load function that handled all the file I/O,
	 * we can use that or do the I/O, whatever sounds best
	 * Either way, exceptions should be used in this part
	 */

//	lg.loadFile();

	//Main menu running
/*Inspection x = lg.getDates();
	for(int i = 0; i < x.size(); i++){

		while(!x[i].empty){
			cout << x[i].top().first;
			cout << endl;
			x[i].pop();
		}
		cout << endl << endl;
	}

*/
		if (menuRunner(lg) == 0)
		// menu exited successfully with no errors
		return 0;

	//Errors ocurred, return != 0
	return 1;

}

//Running the menu with a simple implementation of a state machine
int menuRunner(LeisureGuide &lg) {

	Menu menuobj;

	try {
		//Clearing any data that could have been added to the Menu
		menuobj.reset();
		//Attempting to load options into the Menu using the default txt file location
		menuobj.load(Menu::menutxt_defaultlocation);
	} catch(Utilities::FileNotFound &fnf){
		//If the file was not found, an exception is thrown so we will instead use harcoded options with a warning beforehand
		cout << "Warning: Menu.txt file not found. Path given: " << fnf.getPath();
		cout << "\nFalling back to hardcoded Menu text. "
			 << "(This might not be the most recent version of the Menu)" << endl;

		//Clearing any data that could have been added to the Menu
		menuobj.reset();

		//Hardcoded options adding:
		//Development NOTE: Try to always add the options here besides the txt file

		menuobj.addOption("1 View");
		menuobj.addOption("1.1 Unconditional Listing");
		menuobj.addOption("1.1.1 All Beaches sorted by Concelho and Blue Flag");
		menuobj.addOption("1.1.2 All POIs");
		menuobj.addOption("1.1.3 All Restaurants");
		menuobj.addOption("1.1.4 All Lodging");
		menuobj.addOption("1.1.5 Inspections of a Beach");
		menuobj.addOption("1.1.6 Inspections of Service type");
		menuobj.addOption("1.2 Conditional Listing");
		menuobj.addOption("1.2.1 List Beaches by Concelho");
		menuobj.addOption("1.2.2 Recommendations near a Beach");
		menuobj.addOption("1.2.3 Closed Touristic Points");
		menuobj.addOption("2 Manage");
		menuobj.addOption("2.1 Beaches");
		menuobj.addOption("2.1.1 View Details");
		menuobj.addOption("2.1.2 Add");
		menuobj.addOption("2.1.3 Remove");
		menuobj.addOption("2.1.4 Modify");
		menuobj.addOption("2.2 POIs");
		menuobj.addOption("2.2.1 View Details");
		menuobj.addOption("2.2.2 Add");
		menuobj.addOption("2.2.3 Remove");
		menuobj.addOption("2.2.4 Modify");
		menuobj.addOption("2.3 Restaurants");
		menuobj.addOption("2.3.1 View Details");
		menuobj.addOption("2.3.2 Add");
		menuobj.addOption("2.3.3 Remove");
		menuobj.addOption("2.3.4 Modify");
		menuobj.addOption("2.4 Lodging");
		menuobj.addOption("2.4.1 View Details");
		menuobj.addOption("2.4.2 Add");
		menuobj.addOption("2.4.3 Remove");
		menuobj.addOption("2.5 Touristic Points");
		menuobj.addOption("2.5.1 Close");
		menuobj.addOption("2.5.2 Reopen");
		menuobj.addOption("2.6 Inspections");
		menuobj.addOption("2.6.1 Add");
		menuobj.addOption("3 File I/O");
		menuobj.addOption("3.1 Load");
		menuobj.addOption("3.2 Save");
	}


	//clear screen of whatever was printed before, just in case with a pause before so all output is read with time
	Utilities::pause();
	Utilities::clearScreen();

	//current selection holds the menu state
	string currentselection;
	//temporary input holder - unsigned int to make sure that only numbers are inputted
	unsigned int tempinput;

	//Menu loop
	while (true) {

		menuobj.DisplayByID(currentselection);
		while (true) {
			cin >> tempinput;

			if (cin.fail()) {
				//Clearing error flag and cin buffer
				Utilities::clearCinBuffer();
				//Clearing screen and reprinting
				Utilities::clearScreen();
				cout << "Invalid Selection! Try again!\n\n";
				menuobj.DisplayByID(currentselection);
			}
			else {
				//if cin didn't fail we have a good input so we break the loop
				break;
			}
		}

		//Ensuring that the cin stream is clean for use if there is a getline afterwards
		Utilities::clearCinBuffer();


		if (currentselection.empty() && tempinput == 0) {
			//This means we are at the main menu and the exit option was selected so we can exit the program by exiting the loop
			break;
		}

		if (!currentselection.empty() && tempinput == 0) {
			//This means we are in a submenu and want to go back to the main menu
			currentselection = "";
		} else {
			//in order to not append a dot to an empty string and get ".1" which wouldn't work
			if (currentselection.empty()) {
				currentselection = to_string(tempinput);
			}
			else {
				currentselection += "." + to_string(tempinput);
			}
		}

		if (callFunctions(currentselection, lg)) {
			//do something based on failed state maybe
		}

		Utilities::clearScreen();
	}

	//Menu execution exited successfully
	return 0;
}

//Function to call functions based on hardcoded ID (only way to do this), returns true if function found, false if not found
bool callFunctions(string &id, LeisureGuide &lg) {

	//before running any function, the screen is cleared
	Utilities::clearScreen();

	//Template for function calling
	/*
	if (id == "specify id here") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		//testfunction();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}
	*/

	//Listing all Beaches, sorted by Concelho
	if (id == "1.1.1") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.displayAllBeaches();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Listing all POIs
	if (id == "1.1.2") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.displayAllPOIs();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Listing all Restaurants
	if (id == "1.1.3") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.displayAllRestaurants();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Listing all Lodging
	if (id == "1.1.4") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.displayAllLodging();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Display inspections of a specific beach
	if (id == "1.1.5") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.displayInspectionofaBeach();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Display inspections of a type of service
	if (id == "1.1.6") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.displayInspectionTypeService();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Lists Beaches by Concelho
	if (id == "1.2.1") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.displayBeachesByConcelho();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Lists recomendations near Beaches
	if (id == "1.2.2") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.displaySortedByDistance();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Lists closed Touristic Points
	if (id == "1.2.3") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.displayClosedTouristicPoints();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Display information for a beach
	if (id == "2.1.1") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.displayBeachInfo();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Adds a new beach based on user input
	if (id == "2.1.2") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.addBeach();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Removes a beach by its name
	if (id == "2.1.3") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.removeBeach();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Modifies a beach based on its name
	if (id == "2.1.4") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.modifyBeach();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Display information for a POI
	if (id == "2.2.1") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.displayPOIInfo();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Add a POI
	if (id == "2.2.2") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.addPOI();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Remove a POI based on its name
	if (id == "2.2.3") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.removePOI();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Modify a POI based on its name
	if (id == "2.2.4") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.modifyPOI();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Display information for a Restaurant
	if (id == "2.3.1") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.displayRestaurantInfo();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Add a Restaurant
	if (id == "2.3.2") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.addRestaurant();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Remove a Restaurant based on its name
	if (id == "2.3.3") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.removeRestaurant();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Modify a Restaurant based on its name
	if (id == "2.3.4") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.modifyRestaurant();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Display information for a Lodging
	if (id == "2.4.1") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.displayLodgingInfo();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Add a Lodging
	if (id == "2.4.2") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.addLodging();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Remove a Lodging based on its name
	if (id == "2.4.3") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));	
		//calls function based on hardcoded id
		lg.removeLodging();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Modify a Lodging based on its name
	if (id == "2.4.4") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.modifyLodging();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Close a touristic point and add it to the hash table removing it from the designed list
	if (id == "2.5.1") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.closeTouristicPoint();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Reopen a touristic point and add it back to the designed list and removing it from the hash table
	if (id == "2.5.2") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.reopenTouristicPoint();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Add inspection
	if (id == "2.6.1") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.addInspection();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;

	}

	//File Load
	if (id == "3.1") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.loadFile();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//File Save
	if (id == "3.2") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		lg.saveFile();
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Not yet implemented stuff
	if (id == "unimplemented option ID") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		cout << "WIP, function not yet implemented" << endl;
		//pause to see output
		Utilities::pause();
		//function was found, return true
		return false;
	}

	return false;
}
