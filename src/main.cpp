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

	//Tests here

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
	int menureturn = menuRunner(lg);

	if (menureturn == 0)
		// menu exited successfully with no errors
		return 0;

	//maybe errors? don't know how menu can have error - read error (?)
	return 1;

	return 0;
}

//Most menu stuff
int menuRunner(LeisureGuide &lg) {

	string currentselection; //current selection holds the menu state
	unsigned int tempinput; //temporary input holder - unsigned int to make sure that only numbers are inputted

	try {
		//Attempting to create the Menu using the default txt file location
		Menu menumaozinhas(Menu::menutxt_defaultlocation);
	} catch(InvalidFilePath &ifp){
		//If the file was not found, an exception is thrown so we will instead use harcoded options with a warning beforehand
		cout << "Warning: Menu.txt file not found at the default path."
		     << "\nFalling back to hardcoded Menu text."
			 << "(This might not be the most recent version of the Menu text)" << endl;

		Menu menumaozinhas;

		//Hardcoded options adding:
		//Development NOTE: Try to always add the options here besides the txt file
		menumaozinhas.addOption("1 Visualize");
		menumaozinhas.addOption("2 Manage");
		menumaozinhas.addOption("3 File I/O");
		menumaozinhas.addOption("1.1 TBD test 1.1");
		menumaozinhas.addOption("1.2 TBD test 1.2");
		menumaozinhas.addOption("1.3 TBD test 1.3");
		menumaozinhas.addOption("1.4 TBD test 1.4");
		menumaozinhas.addOption("1.7 TBD test 1.7");
		menumaozinhas.addOption("2.1 Leisure Guide (General Manager)");
		menumaozinhas.addOption("2.1.1 Listagem de linhas");
		menumaozinhas.addOption("2.1.2 Informação detalhada sobre uma linha");
		menumaozinhas.addOption("2.2 Test big 2.2");
		menumaozinhas.addOption("2.2.1 Sub-option for 2.2");
		menumaozinhas.addOption("2.2.2 Sub-option for 2.2 2");
		menumaozinhas.addOption("2.2.3 et cetera for 2.2");
		menumaozinhas.addOption("2.3 Last sub option for 2");
		menumaozinhas.addOption("2.3.1 test");
		menumaozinhas.addOption("2.3.2 other test");
		menumaozinhas.addOption("2.3.3 another test");
		menumaozinhas.addOption("2.3.4 last test");
		menumaozinhas.addOption("3.1 Carregar informação de ficheiros (Load) TODO");
		menumaozinhas.addOption("3.2 Escrever informação em ficheiros (Save) TODO");
	}


	//clear screen of whatever was printed before, just in case with a pause before so all output is read with time
	Utilities::pause();
	Utilities::clearScreen();

	menumaozinhas.DisplayWholeMenu();
	Utilities::pause();

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

	//Example implemented option
	if (id == "1.1") {
		//Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		id = id.substr(0, id.find_last_of('.'));
		//calls function based on hardcoded id

		//pause to see output
		Utilities::pause();
		//function was found, return true
		return true;
	}

	//Not yet implemented stuff
	if (id == "unimplemented option ID" || id == "1.5") {
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