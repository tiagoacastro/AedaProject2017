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
	//lg.Load();

	//Main menu running


	if (menuRunner(lg) == 0)
		// menu exited successfully with no errors
		return 0;

	//Errors ocurred, return != 0
	return 1;
}

//Running the menu with a simple implementation of a state machine
int menuRunner(LeisureGuide &lg) {

	Menu menumaozinhas;

	try {
		//Clearing any data that could have been added to the Menu
		menumaozinhas.reset();
		//Attempting to load options into the Menu using the default txt file location
		menumaozinhas.load(Menu::menutxt_defaultlocation);
	} catch(Utilities::FileNotFound &fnf){
		//If the file was not found, an exception is thrown so we will instead use harcoded options with a warning beforehand
		cout << "Warning: Menu.txt file not found. Path given: " << fnf.getPath();
		cout << "\nFalling back to hardcoded Menu text. "
			 << "(This might not be the most recent version of the Menu)" << endl;

		//Clearing any data that could have been added to the Menu
		menumaozinhas.reset();

		//Hardcoded options adding:
		//Development NOTE: Try to always add the options here besides the txt file

		menumaozinhas.addOption("1 View");
		menumaozinhas.addOption("1.1 Unconditional Listing");
		menumaozinhas.addOption("1.1.1 All Beaches sorted by Concelho");
		menumaozinhas.addOption("1.1.2 All POIs");
		menumaozinhas.addOption("1.1.3 All Restaurants");
		menumaozinhas.addOption("1.1.4 All Lodging");
		menumaozinhas.addOption("1.2 Conditional Listing");
		menumaozinhas.addOption("1.2.1 List Beaches by Concelho");
		menumaozinhas.addOption("1.2.2 Recommendations near a Beach");
		menumaozinhas.addOption("2 Manage");
		menumaozinhas.addOption("2.1 Beaches");
		menumaozinhas.addOption("2.1.1 View Details");
		menumaozinhas.addOption("2.1.2 Add");
		menumaozinhas.addOption("2.1.3 Remove");
		menumaozinhas.addOption("2.1.4 Modify");
		menumaozinhas.addOption("2.2 POIs");
		menumaozinhas.addOption("2.2.1 View Details");
		menumaozinhas.addOption("2.2.2 Add");
		menumaozinhas.addOption("2.2.3 Remove");
		menumaozinhas.addOption("2.2.4 Modify");
		menumaozinhas.addOption("2.3 Restaurants");
		menumaozinhas.addOption("2.3.1 View Details");
		menumaozinhas.addOption("2.3.2 Add");
		menumaozinhas.addOption("2.3.3 Remove");
		menumaozinhas.addOption("2.3.4 Modify");
		menumaozinhas.addOption("2.4 Lodging");
		menumaozinhas.addOption("2.4.1 View Details");
		menumaozinhas.addOption("2.4.2 Add");
		menumaozinhas.addOption("2.4.3 Remove");
		menumaozinhas.addOption("2.4.4 Modify");
		menumaozinhas.addOption("3 File I/O");
		menumaozinhas.addOption("3.1 Load");
		menumaozinhas.addOption("3.2 Save");
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

		menumaozinhas.DisplayByID(currentselection);
		while (true) {
			cin >> tempinput;

			if (cin.fail()) {
				//Clearing error flag and cin buffer
				cin.clear();
				cin.ignore(1000000, '\n');
				//Clearing screen and reprinting
				Utilities::clearScreen();
				cout << "Seleção inválida! Tente novamente!\n\n";
				menumaozinhas.DisplayByID(currentselection);
			}
			else {
				//if cin didn't fail we have a good input so we break the loop
				break;
			}

			break;
		}

		if (currentselection.empty() && tempinput == 0) {
			//This means we are at the main menu and the exit option was selected so we can exit the program by exiting the loop

			//TODO: Implement having unsaved changes

			//But first, checking if there are unsaved changes
			//This was lg.getIfHasUnsavedChanges()
			if (false) {
				string option;
				cout << "Tem alterações não gravadas, deseja mesmo assim sair do programa? (S/N)" << endl;
				cout << ">> ";
				while (true) {
					cin >> option;
					if (cin.fail() || (option != "S" && option != "N")) {
						//Clearing error flags and buffer
						cin.clear();
						cin.ignore(10000, '\n');
						//Clearing screen to display input prompt again
						cout << "Opção inválida." << endl;
						cout << "Tem alterações não gravadas, deseja mesmo assim sair do programa? (S/N)" << endl;
						cout << ">> ";
					}
					else {
						//input is valid so we break the loop
						break;
					}
				}

				//If the user specifies that he does not want to exit the program because he has unsaved progress we do not exit the program
				if (option == "N") {
					//As such, we do nothing
				}
				else {
					//Otherwise, the user specified that he does want to exit so we break the loop to exit the program
					break;
				}
			}
			else {
				//If the user does not have unsaved changes we simply exit the program as usual
				break;
			}

		}
		else
		if (!currentselection.empty() && tempinput == 0) {
			//This means we are in a submenu and want to go back to the main menu
			currentselection = "";
		}
		else {
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

	//Lists Beaches by Concelho
	if (id == "1.2.1") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		cout << "To be implemented!" << endl;
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

	//Display information for a beach
	if (id == "2.1.1") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id
		cout << "To be implemented!" << endl;
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
		cout << "To be implemented!" << endl;
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
		cout << "To be implemented!" << endl;
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
		cout << "To be implemented!" << endl;
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