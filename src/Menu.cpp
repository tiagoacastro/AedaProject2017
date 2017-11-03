#include "Menu.h"
#include "Utilities.h"
using namespace std;

string Menu::menutxt_defaultlocation = "Menu.txt";

Menu::Option::Option(const string &rawoption){

	string id = rawoption.substr(0, rawoption.find_first_of(' '));
	string optiontext = rawoption.substr(rawoption.find_first_of(' ') + 1);
	int depth_level = Utilities::countCharInString(id, '.');

	this->id = id;
	this->option_text = optiontext;
	this->depth_level = depth_level;
}

Menu::Menu(string path) {
	ifstream menu_txt(path);

	//If text file couldn't be open, throw InvalidFilePath exception
	if(!menu_txt.is_open()){
		throw Utilities::FileNotFound(path);
	}

	//Reading the text file and adding the options to the menu
	vector<string> rawfile = Utilities::ReadFile(menu_txt);
	for(const auto &line : rawfile) {
		addOption(line);
	}
}

Menu::Menu(vector<string> rawlines) {
	for(const auto &rawline : rawlines) {
		addOption(rawline);
	}
}

void Menu::addOption(const string &newOption){
	menuOptions.emplace_back(newOption);
}

void Menu::DisplayWholeMenu() const{
	for (int i = 0; i < menuOptions.size(); i++) {
		cout << i << ": " << menuOptions[i].id << " " << menuOptions[i].option_text << "\t depth: " << menuOptions[i].depth_level << endl;
	}
}

void Menu::DisplayByID(string &id) const{
	vector<Option> display = FindOptionByID(id);

	//Dealing with invalid option -> empty vector
	if (display.empty()) {
		cout << "Seleção inválida! Tente novamente!\n\n";
		//Removing last selected option from ID
		if (id.size() == 1) {
			//First level selection, requested ID can be cleared with no problems to reset the menu
			id = "";
		}
		else {
			//More than first level selection, to clear the last selection from the requested ID we must remove the ".N"
			id = id.substr(0, id.find_last_of('.')); //Finds last '.' and uses substr until it, exlcuding it, thus excluding the ".N"
		}
		//Displays the menu again with the new reverted ID
		this->DisplayByID(id);
	}
	else {
		for(auto &opt : display) {
			cout << opt.id << " " << opt.option_text << endl;
		}
		//Exit option and fancy last line for input
		if (id.empty()) {
			//If in main menu (string empty) show exit instead of back
			cout << "0 Sair" << endl;
		}
		else {
			cout << "0 Voltar ao menu inicial" << endl;
		}
		cout << "\n>>> ";
	}

}

//returns a vector of options based on the provided ID. If ID is empty, returns all options with 0 depth, otherwise with a matching ID and depth level
vector<Menu::Option> Menu::FindOptionByID(string id) const{
	vector<Option> output;

	if (id.empty()) {
		//find all options with depth_level 0
		for(auto &menuOption : menuOptions) {
			if (menuOption.depth_level == 0)
				output.push_back(menuOption);
		}
	}
	else {
		//Hardcoded dot at end to avoid printing parent options
		//Inside else because the string would never be empty otherwise
		id += ".";

		//finds depth level and also uses it as comparison to avoid "1.1" from getting "1" too, etc
		//another solution would be changing compareDiffSizeStrings to look at the size of either the first or second string, I guess
		int wanteddepth = Utilities::countCharInString(id, '.');

		for(auto &menuOption : menuOptions) {
			if (Utilities::compareDiffSizeStrings(menuOption.id, id) && menuOption.depth_level == wanteddepth) {
				output.push_back(menuOption);
			}
		}
	}

	return output;
}

Menu::~Menu(){}

Menu::Menu(){}

void Menu::reset(){
	menuOptions.clear();
}

void Menu::load(string filepath){
	ifstream menu_txt(filepath);

	//If text file couldn't be open, throw InvalidFilePath exception
	if(!menu_txt.is_open()){
		throw Utilities::FileNotFound(filepath);
	}

	//Reading the text file and adding the options to the menu
	vector<string> rawfile = Utilities::ReadFile(menu_txt);
	for(const auto &line : rawfile) {
		addOption(line);
	}
}
