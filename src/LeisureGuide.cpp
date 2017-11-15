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
	//Gets all the conselhos
	auto conselhos = getAllConselhos();

	for(auto const &conselho : conselhos){
		//Print the concelho
		cout << conselho << ": " << endl;

		//Get the beaches for this conselho
		auto beaches_to_display = getBeachesByConselho(conselho);

		//Print each beach inside a conselho
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

vector<string> LeisureGuide::getAllConselhos() const{
	set<string> temp;

	//A set only keeps unique elements, so there are no duplicates
	for(auto const &beach : beaches){
		temp.emplace(beach.first);
	}

	//Copying the stored unique keys to a vector
	vector<string> output(temp.begin(), temp.end());

	return output;
}

vector<Beach *> LeisureGuide::getBeachesByConselho(const string &conselho) const{
	vector<Beach *> output;

	//Iterating for each pair of beaches vector and if the "key" (first element, representing the Conselho)
	//matches the specified conselho, add the "data member" (second element, Beach*) to the output
	std::for_each(beaches.begin(), beaches.end(), [&output, conselho](pair<string, Beach*> p) {
		if(p.first == conselho){
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

	if (infos[0] == 'B')
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
	if (beach[5] == '1')
		x.second->setBlueFlag(true);
	else
		x.second->setBlueFlag(false);
	x.second->setMaxCapacity(stod(beach[4]));

	stuff = Utilities::splitString(beach[3], ',');

	x.second->setCoordinates(Coordinates(stod(stuff[0]), stod(stuff[1])));

	services = Utilities::splitString(beach[beach.size() - 1], ';');

	for (size_t i = 0; i < services.size(); i++) {
		stuff = Utilities::splitString(services[i], ',');
		serv.push_back(Service(stuff[0], stuff[1], stuff[2], stuff[3]));
	}
}

vector<pair<string, Beach*>>::iterator LeisureGuide::findBeachByName(string name) {
	return find_if(beaches.begin(), beaches.end(), [=](pair<string, Beach*> &p) {return p.second->getName() == name; });
}

bool LeisureGuide::removeBeach() {
	Utilities::clearScreen();
	string name;
	cout << "What is the name of the beach you wish to remove? "; cin >> name; cout << endl;
	vector<pair<string, Beach*>>::iterator it = findBeachByName(name);
	if (it == beaches.end()) {
		cout << "Beach not found" << endl;
		return false;
	}
	delete it->second;
	beaches.erase(it);
	return true;
}

bool LeisureGuide::addBeach() {
	Utilities::clearScreen();
	string name, response, beachType, serviceName, serviceType, serviceDescription, concelho;
	double x, y, width, riverFlow, maxDepth, usableAquaticArea;
	unsigned int maxCapacity;
	bool blueFlag;
	vector <Service> services;


	cout << "What concelho does the beach belong to? " << endl;
	getline(cin, concelho);
	cout << endl;
	if (cin.fail()) {
		cout << "Wrong input type, must be string" << endl;
		return false;
	}
	cout << endl;


	cout << "What is the name of the beach? " << endl;
	getline(cin, name);
	cout << endl;
	if (cin.fail()) {
		cout << "Wrong input type, must be string" << endl;
		return false;
	}
	if (findBeachByName(name) != beaches.end()) {
		cout << "Beach already exists" << endl;
		return false;
	}
	cout << endl;


	cout << "What are the coordinates of the beach (x followed by Y)? " << endl; cin >> x;
	if (cin.fail()) {
		cout << endl << "Wrong input type, must be a number" << endl;
		return false;
	}
	cin >> y; cout << endl;
	if (cin.fail()) {
		cout << "Wrong input type, must be a number" << endl;
		return false;
	}
	cout << endl;


	cout << "What is the beach's max capacity? " << endl; cin >> maxCapacity; cout << endl;
	if (cin.fail()) {
		cout << "Wrong input type, must be an unsigned integer" << endl;
		return false;
	}
	cout << endl;


	cout << "Does the beach have blue flag (yes or no)? " << endl; cin >> response; cout << endl;
	if (cin.fail()) {
		cout << "Wrong input type, must be string" << endl;
		return false;
	}
	if (response == "yes")
		blueFlag = true;
	else if (response == "no")
		blueFlag = false;
	else {
		cout << "Wrong input type, must be 'yes' or 'no'" << endl;
		return false;
	}
	cout << endl;


	while (true) {
		cout << "Do you want to add a service (yes or no)? " << endl; cin >> response;
		cout << endl;
		if (cin.fail()) {
			cout << "Wrong input type, must be string" << endl;
			return false;
		}
		if (response == "yes") {


			cout << "What is the service's name? " << endl;
			getline(cin, serviceName);
			cout << endl;
			if (cin.fail()) {
				cout << "Wrong input type, must be string" << endl;
				return false;
			}
			cout << endl;


			cout << "What is the service's type? " << endl;
			getline(cin, serviceType);
			cout << endl;
			if (cin.fail()) {
				cout << "Wrong input type, must be string" << endl;
				return false;
			}
			cout << endl;

			
			cout << "Do you want to add a description to the service? " << endl; cin >> response;
			cout << endl;
			if (cin.fail()) {
				cout << "Wrong input type, must be string" << endl;
				return false;
			}
			if (response == "yes") {
				cout << "Write description: " << endl;
				getline(cin, serviceDescription);
				cout << endl;
				if (cin.fail()) {
					cout << "Wrong input type, must be string" << endl;
					return false;
				}
				cout << endl;
				services.emplace_back(serviceName, serviceType, serviceDescription);
				cout << endl;
				continue;
			}
			else if (response != "no") {
				cout << "Wrong input, must be 'yes' or 'no'" << endl;
				return false;
			}
			services.emplace_back(serviceName, serviceType);
			cout << endl;
		}
		else if (response == "no") {
			break;
		}
		else {
			cout << "Wrong input, must be 'yes' or 'no'" << endl;
			return false;
		}
		cout << endl;
	}


	cout << "Is it a river beach or a bayou beach (river or bayou)? " << endl; cin >> beachType; cout << endl;
	if (cin.fail()) {
		cout << "Wrong input type, must be string" << endl;
		return false;
	}
	cout << endl;


	if (beachType == "river") {
		cout << "What is the river's width? " << endl; cin >> width; cout << endl;
		if (cin.fail()) {
			cout << "Wrong input type, must be a number" << endl;
			return false;
		}
		cout << endl;
		cout << "What is the river's flow? " << endl; cin >> riverFlow; cout << endl;
		if (cin.fail()) {
			cout << "Wrong input type, must be a number" << endl;
			return false;
		}
		cout << endl;
		cout << "What is the river's max depth? " << endl; cin >> maxDepth; cout << endl;
		if (cin.fail()) {
			cout << "Wrong input type, must be a number" << endl;
			return false;
		}
		cout << endl;
		RiverBeach b(name, Coordinates(x, y), maxCapacity, blueFlag, services, width, riverFlow, maxDepth);
		Beach *beachpntr = &b;
		beaches.emplace_back (concelho, beachpntr);
	}	


	else if (beachType == "bayou") {
		cout << "What is the bayou's usable aquatic area? " << endl; cin >> usableAquaticArea; cout << endl;
		if (cin.fail()) {
			cout << "Wrong input type, must be a number" << endl;
			return false;
		}
		cout << endl;
		BayouBeach b(name, Coordinates(x, y), maxCapacity, blueFlag, services, usableAquaticArea);
		Beach *beachpntr = &b;
		beaches.emplace_back(concelho, beachpntr);
	}


	else {
		cout << "Wrong input type, must be 'river' or 'bayou'" << endl;
		return false;
	}

	cout << "Beach has been successfully created" << endl;
}