#include "LeisureGuide.h"


LeisureGuide::LeisureGuide() {
}

LeisureGuide::LeisureGuide(const vector<pair<string, Beach*>> &beaches):
									beaches(beaches) {
}

LeisureGuide::LeisureGuide(const vector<pair<string, Beach*>> &beaches, const vector<Restaurant> &restaurants, const vector<POI> &POIs, const vector<Lodging> &lodging):
									beaches(beaches), restaurants(restaurants), POIs(POIs), lodging(lodging) {
}

void LeisureGuide::displayAllBeaches() const{
	//Gets all the concelhos
	auto concelhos = getAllConcelhos();

	for(auto const &concelho : concelhos){
		//Print the concelho
		cout << concelho << ": " << endl;

		//Get the beaches for this concelho
		auto beaches_to_display = getBeachesByConcelho(concelho);

		//Print each beach inside a concelho
		for(auto const &beach_to_display : beaches_to_display){
			beach_to_display->print(cout);
		}
	}
}

void LeisureGuide::displayAllPOIs() const{
	for(auto const &poi : POIs)	{
		cout << poi << endl;
	}
}

void LeisureGuide::displayAllRestaurants() const{
	for(auto const &restaurant : restaurants){
		cout << restaurant << endl;
	}
}

void LeisureGuide::displayAllLodging() const{
	for(auto const &l : lodging){
		cout << l << endl;
	}
}

vector<string> LeisureGuide::getAllConcelhos() const{
	set<string> temp;

	//A set only keeps unique elements, so there are no duplicates
	for(auto const &beach : beaches){
		temp.emplace(beach.first);
	}

	//Copying the stored unique keys to a vector
	vector<string> output(temp.begin(), temp.end());

	return output;
}

vector<Beach *> LeisureGuide::getBeachesByConcelho(const string &concelho) const{
	vector<Beach *> output;

	//Iterating for each pair of beaches vector and if the "key" (first element, representing the Concelho)
	//matches the specified concelho, add the "data member" (second element, Beach*) to the output
	std::for_each(beaches.begin(), beaches.end(), [&output, concelho](pair<string, Beach*> p) {
		if(p.first == concelho){
			output.push_back(p.second);
		}
	});

	return output;
}

void LeisureGuide::loadFile(){
	string file;
	vector <string> poi, rest, lod, beach;
	cout << "Insert the path for the Points of Interest path\n";
	getline(cin, file);
	Utilities::trimString(file);
	poi = Utilities::ReadFile(file);

	cout << "Insert the path for the Restaurants path\n";
	getline(cin, file);
	Utilities::trimString(file);
	rest = Utilities::ReadFile(file);

	cout << "Insert the path for the Lodging path\n";
	getline(cin, file);
	Utilities::trimString(file);
	lod = Utilities::ReadFile(file);


	cout << "Insert the path for the Beaches file\n";
	getline(cin, file);
	Utilities::trimString(file);
	beach = Utilities::ReadFile(file);

}

void LeisureGuide::createBeach(vector<string> &beaches){
	for(auto &beach : beaches){
		createBeach(beach);
	}
}

void LeisureGuide::createBeach(string &beach){

	vector<string> infos;
	infos = Utilities::splitString(beach, '|');

	if (infos[0] == "B")
		this->createBayouBeach(infos);
	else
		this->createRiverBeach(infos);
}


void LeisureGuide::createBayouBeach(vector<string> &beach) {
	pair<string, Beach*> x;
	vector <string> stuff, services;
	vector<Service> serv;
	x.first = beach[2];
	x.second->setName(beach[1]);
	if (beach[5] == "1")
		x.second->setBlueFlag(true);
	else
		x.second->setBlueFlag(false);
	x.second->setMaxCapacity(stod(beach[4]));

	stuff = Utilities::splitString(beach[3], ',');

	x.second->setCoordinates(Coordinates(stod(stuff[0]), stod(stuff[1])));

	services = Utilities::splitString(beach[beach.size() - 1], ';');

	for (size_t i = 0; i < services.size(); i++) {
		stuff = Utilities::splitString(services[i], ',');
		//serv.push_back(Service(stuff[0], stuff[1], stuff[2], stuff[3]));          APAGUEI ISTO AQUI PORQUE JA NAO HA SCHEDULE NO SERVICE, DA FIX PLZ
	}
}

vector<pair<string, Beach*>>::iterator LeisureGuide::findBeachByName(string name) {
	return find_if(beaches.begin(), beaches.end(), [=](pair<string, Beach*> &p) {return p.second->getName() == name; });
}

bool LeisureGuide::removeBeach() {
	Utilities::clearScreen();
	string name;
	cout << "What is the name of the beach you wish to remove?\n";
	getline(cin, name);
	auto it = findBeachByName(name);

	if (it == beaches.end()) {
		cout << "Beach not found!" << endl;
		return false;
	}

	//Deallocating memory for the Beach *
	//This works for derivate classes because Beach has a virtual destructor
	delete it->second;
	beaches.erase(it);
	cout << "Beach deleted successfully!" << endl;

	return true;
}

bool LeisureGuide::addBeach() {
	Utilities::clearScreen();

	string beachType, serviceName, serviceType, serviceDescription;
	vector<Service> services;

	//getline does not fail so there is no need to test cin.fail

	string concelho;
	cout << "What concelho does the beach belong to? " << endl;
	getline(cin, concelho);

	string name;
	cout << "What is the name of the beach? " << endl;
	getline(cin, name);

	//If the beach is found, it already exists (it is found if the iterator returned by findBeachByName is different from 0)
	if (findBeachByName(name) != beaches.end()) {
		cout << "Beach already exists" << endl;
		return false;
	}

	double x, y;
	cout << "What are the coordinates of the beach (X followed by Y)?" << endl;

	//Getting X
	while (true) {
		cin >> x;
		if (cin.fail()) {
			cout << "Invalid X value, please insert a valid X coordinate value (decimal number)." << endl;
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	//Getting Y
	while (true) {
		cin >> y;
		if (cin.fail()) {
			cout << "Invalid Y value, please insert a valid Y coordinate value (decimal number)." << endl;
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	unsigned int maxCapacity;
	cout << "What is the beach's maximum capacity? " << endl;

	while (true) {
		cin >> maxCapacity;
		if (cin.fail()) {
			cout << "Invalid max capacity value, please insert a valid maximum capacity value (positive integer)." << endl;
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	string response;
	bool blueFlag;
	cout << "Does the beach have blue flag (yes or no)? " << endl;

	while (true) {
		cin >> response;
		if (cin.fail() || (response != "yes" && response != "no") || (response != "Yes" && response != "No")) {
			cout << "Invalid input, please enter yes or no." << endl;
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	blueFlag = ((response == "yes") || (response == "Yes"));

	while (true) {
		cout << "Do you want to add a service (yes or no)? " << endl;
		while (true) {
			cin >> response;
			if (cin.fail() || (response != "yes" && response != "no") || (response != "Yes" && response != "No")) {
				cout << "Invalid input, please enter yes or no." << endl;
				//Clearing error flag and cin buffer
				cin.clear();
				cin.ignore(100000, '\n');
			}
			else {
				//if cin didn't fail we have a good input so we break the loop
				break;
			}
		}

		if (response == "yes" || response == "Yes") {

			//Must use ignore before getline since cin was used as a stream before, a newline might be stuck in the buffer
			cin.ignore(100000, '\n');

			cout << "What is the service's name?" << endl;
			getline(cin, serviceName);

			cout << "What is the service's type?" << endl;
			getline(cin, serviceType);

			cout << "Do you want to add a description to the service?" << endl;

			while (true) {
				getline(cin, response);
				if (cin.fail() || (response != "yes" && response != "no") || (response != "Yes" && response != "No")) {
					cout << "Invalid input, please enter yes or no." << endl;
					//Clearing error flag and cin buffer
					cin.clear();
					cin.ignore(100000, '\n');
				}
				else {
					//if cin didn't fail we have a good input so we break the loop
					break;
				}
			}

			//If adding a service description is desired
			if (response == "yes" || response == "Yes") {
				cout << "Service description: ";
				getline(cin, serviceDescription);

				services.emplace_back(serviceName, serviceType, serviceDescription);
				continue;
			}

			//If the user does not want to add a service description
			services.emplace_back(serviceName, serviceType, "None");
			cout << endl;
		} else {
			//If the user entered "no" or "No", he does not wish to input any (further) services
			break;
		}
	}


	cout << "Is it a river beach or a bayou beach (river or bayou)?" << endl;

	while (true) {
		cin >> beachType;
		if (cin.fail() || (beachType != "river" && beachType != "bayou") || (beachType != "River" && beachType != "Bayou")) {
			cout << "Invalid input, please enter river or bayou." << endl;
			//Clearing error flag and cin buffer
			cin.clear();
			cin.ignore(100000, '\n');
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}


	//If the user wants to create a river beach
	if (beachType == "river" || beachType == "River") {
		double width, riverFlow, maxDepth;

		cout << "What is the river's width? " << endl;
		while (true) {
			cin >> width;
			if (cin.fail() || width <= 0) {
				cout << "Invalid river width value, please insert a valid river width value (positive decimal)." << endl;
				//Clearing error flag and cin buffer
				cin.clear();
				cin.ignore(100000, '\n');
			}
			else {
				//if cin didn't fail we have a good input so we break the loop
				break;
			}
		}

		cout << "What is the river's flow? " << endl;
		while (true) {
			cin >> riverFlow;
			if (cin.fail() || riverFlow <= 0) {
				cout << "Invalid river flow value, please insert a valid river flow value (positive decimal)." << endl;
				//Clearing error flag and cin buffer
				cin.clear();
				cin.ignore(100000, '\n');
			}
			else {
				//if cin didn't fail we have a good input so we break the loop
				break;
			}
		}

		cout << "What is the river's max depth? " << endl;
		while (true) {
			cin >> maxDepth;
			if (cin.fail() || maxDepth <= 0) {
				cout << "Invalid river max depth, please insert a valid river maximum depth (positive decimal)." << endl;
				//Clearing error flag and cin buffer
				cin.clear();
				cin.ignore(100000, '\n');
			}
			else {
				//if cin didn't fail we have a good input so we break the loop
				break;
			}
		}

		Beach *beachpntr = new RiverBeach(name, Coordinates(x, y), maxCapacity, blueFlag, services, width, riverFlow, maxDepth);
		beaches.emplace_back(concelho, beachpntr);
	}
	//If the user wants to create a bayou beach
	else {
		double usableAquaticArea;

		cout << "What is the bayou's usable aquatic area? " << endl; cin >> usableAquaticArea; cout << endl;
		while (true) {
			cin >> usableAquaticArea;
			if (cin.fail() || usableAquaticArea <= 0) {
				cout << "Invalid bayou usable aquatic area, please insert a valid usable aquatic area (positive decimal)." << endl;
				//Clearing error flag and cin buffer
				cin.clear();
				cin.ignore(100000, '\n');
			}
			else {
				//if cin didn't fail we have a good input so we break the loop
				break;
			}
		}

		Beach *beachpntr = new BayouBeach(name, Coordinates(x, y), maxCapacity, blueFlag, services, usableAquaticArea);
		beaches.emplace_back(concelho, beachpntr);
	}

	cout << "Beach has been successfully created" << endl;
}