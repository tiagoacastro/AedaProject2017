#include "LeisureGuide.h"



LeisureGuide::LeisureGuide() {
}

void LeisureGuide::displayAllBeaches() const {
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

		//Separator between Concelhos
		cout << "\n\n";
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
	for(auto const &pair : beaches) {
		if(pair.first == concelho) {
			output.emplace_back(pair.second);
		}
	}

	return output;
}

void LeisureGuide::saveFile() {
	string file, path;
	ofstream s;

	cout << "What kind of information do you want to save? (Points of Interest (POI), Restaurant, Beach, Lodging or Closed Touristic Points)" << endl;
	getline(cin, file);
	Utilities::trimString(file);

	while (file != "Points of Interest" && file != "Restaurant" && file != "Beach" && file != "Lodging" && file != "POI" && file != "Closed Touristic Points"){
		cout << "Choose one of them please\n";
		getline(cin, file);
		Utilities::trimString(file);
	}

	cout << "Enter the path for the file please (EOF to exit)" << endl;
	getline(cin, path);
	Utilities::trimString(path);
	s.open(path);

	while(!s.is_open()){
		if(cin.eof()){
			cout << "EOF received, exiting file saving operation!" << endl;
			//Clearing the EOF
			Utilities::clearCinBuffer();
			return;
		}
		cout << "Error opening the file, enter the path again please (EOF to exit)" << endl;
		getline(cin,path);
		s.open(path);
	}

	if(file == "Points of Interest" || file == "POI"){
		savePOI(s);
	} else if(file == "Restaurant"){
		saveRestaurants(s);
	} else if(file == "Beach"){
		saveBeaches(s);
	} else if(file == "Lodging"){
		saveLodging(s);
	} else if (file == "Closed Touristic Points") {
		saveClosedTouristicPoints(s);
	}

	s.close();
}

void LeisureGuide::saveBeaches(ofstream &s){
	string format, concelho;

	for(auto &beach : beaches){
		format = beach.second->toString();
		concelho = beach.first + " | ";
		//nome da praia + numero de char existentes até à posicao da latitude
		format.insert(beach.second->getName().length() + 7, concelho);
		s << format << '\n';
	}
}

void LeisureGuide::saveRestaurants(ofstream &s){
	for (auto const &rest : restaurants)
		s << rest.toString() << endl;
}

void LeisureGuide::savePOI(ofstream &s){
	for (auto const &pois : POIs)
		s << pois.toString() << endl;
}
void LeisureGuide::saveLodging(ofstream &s){
	for (auto const &lodg : lodging)
		s << lodg.toString() << endl;
}

void LeisureGuide::loadFile(){
	ifstream s;
	string file, path;
	char answer;

	cout << "What kind of files do you want to read? (Points of Interest aka POI, Restaurant, Beach, Lodging or Closed Touristic Points)" << endl;
	getline(cin, file);
	Utilities::trimString(file);
	while (file != "Points of Interest" && file != "POI" && file != "Restaurant" && file != "Beach" && file != "Lodging" && file != "Closed Touristic Points"){
		cout << "Not a valid option! Please choose one of the options listed!\n";
		getline(cin, file);
		Utilities::trimString(file);
	}

	cout << "Enter the path for the file (EOF to exit)" << endl;
	getline(cin, path);
	Utilities::trimString(path);
	s.open(path);

	while(!s.is_open()){
		if(cin.eof()){
			cout << "EOF received, exiting file loading operation!" << endl;
			//Clearing the EOF
			Utilities::clearCinBuffer();
			return;
		}
		cout << "Error opening the file, please enter the path again (EOF to exit)" << endl;
		getline(cin,path);
		Utilities::trimString(path);
		s.open(path);
	}

	vector<string> readfile = Utilities::ReadFile(s);

	try{
		if(file == "Points of Interest" || file == "POI"){
			createPOI(readfile);
		} else if(file == "Restaurant"){
			createRestaurants(readfile);
		} else if(file == "Beach"){
			createBeach(readfile);
		} else if(file == "Lodging") {
			createLodging(readfile);
		} else if(file == "Closed Touristic Points") {
			createTouristicPoint(readfile);
		}
	} catch(Utilities::WrongFileFormat &wff){
		cout << "Wrong file format! Error in : " << wff.getType() << " format!" << endl;
	}

	//Always closing the stream before exiting
	s.close();
}


void LeisureGuide::createRestaurants(vector<string> &restaurants){
	for(auto &restaurant : restaurants){
		createRestaurants(restaurant);
	}
}

void LeisureGuide::createRestaurants(string &restaurant){
	vector<string> infos;
	infos = Utilities::splitString(restaurant, '|');

	vector<string> coords;
	string name, descrip;

	Utilities::trimString(infos[0]);
	Utilities::trimString(infos[1]);
	Utilities::trimString(infos[2]);
	Utilities::trimString(infos[3]);

	name = infos[0];
	coords = Utilities::splitString(infos[1], ',');
	descrip = infos[3];

	Utilities::trimString(coords[0]);
	Utilities::trimString(coords[1]);

	Schedule sch;
	sch.weekSchedule = Utilities::splitString(infos[2], ',');

	for(auto &line : sch.weekSchedule) {
		Utilities::trimString(line);
	}

	restaurants.emplace_back(name, sch, Coordinates(stod(coords[0]),stod(coords[1])), descrip);
}

void LeisureGuide::createPOI(vector<string> &poi){
	for(auto &points : poi){
		createPOI(points);
	}
}

void LeisureGuide::createPOI(string &poi){
	//POI file string format
	//name | coords | description
	//coords are x , y

	vector<string> infos = Utilities::splitString(poi, '|');

	string name, descrip;


	Utilities::trimString(infos[0]);
	Utilities::trimString(infos[1]);
	Utilities::trimString(infos[2]);

	name = infos[0];
	descrip = infos[2];

	vector<string> coords = Utilities::splitString(infos[1], ',');

	Utilities::trimString(coords[0]);
	Utilities::trimString(coords[1]);

	POIs.emplace_back(name, Coordinates(stod(coords[0]),stod(coords[1])), descrip);
}


void LeisureGuide::createLodging(vector<string> &lodging){
	for(auto &lodg : lodging){
		createLodging(lodg);
	}
}

void LeisureGuide::createLodging(string &lodg){
	//Lodging file string format
	//name | coords | isFull | description
	//coords are x , y
	//isFull can be 0 or 1

	vector<string> infos = Utilities::splitString(lodg, '|');

	//Trimming the read strings to remove extra spaces
	Utilities::trimString(infos[0]);
	Utilities::trimString(infos[2]);
	Utilities::trimString(infos[3]);

	bool full = (infos[2] == "1");

	string name = infos[0];
	string desc = infos[3];
	vector<string> coords = Utilities::splitString(infos[1], ',');

	Utilities::trimString(coords[0]);
	Utilities::trimString(coords[1]);


	lodging.emplace_back(name, Coordinates(stod(coords[0]),stod(coords[1])), full, desc);
}


void LeisureGuide::createBeach(vector<string> &beaches){
	for(auto &beach : beaches){
		createBeach(beach);
	}
}

void LeisureGuide::createBeach(string &beach){

	vector<string> infos = Utilities::splitString(beach, '|');

	//Eliminate whitespace for all the items
	for(auto &item : infos){
		Utilities::trimString(item);
	}

	if (infos[0] == "B" || infos[0] == "b")
		this->createBayouBeach(infos);
	else if (infos[0] == "R" || infos[0] == "r")
		this->createRiverBeach(infos);
	else
		//Throwing exception since file is in the wrong format
		throw Utilities::WrongFileFormat("Beach identifier");
}

void LeisureGuide::createBayouBeach(vector<string> &beach) {

	//beachtype ([bB]) | Name | Concelho | x , y (coords) | capacity | blue flag | services | area
	//services are name, type, description, inspection date (YYYY/DD/MM) ; name, type, description, inspection date (YYYY/DD/MM); name, type, description, inspection date (YYYY/DD/MM)


	//For throwing WrongFileFormat exception if anything goes wrong in parsing
	try {

		double xc, yc, area;
		bool bf;
		string blueFlag;

		string name = beach[1];
		string concelho = beach[2];

		unsigned int capacity = static_cast<unsigned int>(stoul(beach[4]));

		bf = (beach[5] == "1");

		vector<string> rawcoordinates = Utilities::splitString(beach[3], ',');
		Utilities::trimString(rawcoordinates[0]);
		Utilities::trimString(rawcoordinates[1]);

		xc = stod(rawcoordinates[0]);
		yc = stod(rawcoordinates[1]);

		area = stod(beach[7]);

		vector<Service> serv;
		//If the string at beach.size() - 1 is empty, aka the part where the services would be listed is empty
		//Then we add no services (the vector is initializated as empty, so there is no problem there)
		if(!beach[6].empty()) {
			//If it isn't empty then there are services to search for, so we parse the text as usual

			vector<string> services = Utilities::splitString(beach[6], ';');
			vector<string> serviceitems;

			for(auto &service : services) {
					Utilities::trimString(service);
				serviceitems = Utilities::splitString(service, ',');
				Utilities::trimString(serviceitems[0]);
				Utilities::trimString(serviceitems[1]);
				Utilities::trimString(serviceitems[2]);
				Utilities::trimString(serviceitems[3]);
				serv.emplace_back(serviceitems[0], serviceitems[1], serviceitems[2], serviceitems[3]);
			}
		}


		Beach *p = new BayouBeach(name, Coordinates(xc, yc), capacity, bf, serv, area);
		beaches.emplace(concelho, p);

	
	} catch(...){
		throw Utilities::WrongFileFormat("Bayou Beach");
	}
}


void LeisureGuide::createRiverBeach(vector<string> &beach){
	//beachtype ([rR] or [bB]) | Name | Concelho | x , y (coords) | capacity | blue flag | services | width | RiverFlow | maxDepth
	//services are name, type, description ; name, type, description; name, type, description

	//For throwing WrongFileFormat exception if anything goes wrong in parsing
	try {
		vector<string> stuff;

		//Eliminate whitespace for all the items
		for(auto &item : beach) {
			Utilities::trimString(item);
		}

		string concelho = beach[2];
		string name = beach[1];

		unsigned int capacity = static_cast<unsigned int>(stoul(beach[4]));

		bool bf = (beach[5] == "1");

		stuff = Utilities::splitString(beach[3], ',');
		Utilities::trimString(stuff[0]);
		Utilities::trimString(stuff[1]);
		double xc = stod(stuff[0]);
		double yc = stod(stuff[1]);

		double width = stod(beach[7]);
		double riverFlow = stod(beach[8]);
		double maxDepth = stod(beach[9]);

		vector<Service> serv;
		//If the string at beach.size() - 1 is empty, aka the part where the services would be listed is empty
		//Then we add no services (the vector is initializated as empty, so there is no problem there)
		if(!beach[6].empty()) {
			//If it isn't empty then there are services to search for, so we parse the text as usual
			vector<string> services = Utilities::splitString(beach[6], ';');

			for(auto &service : services) {
				Utilities::trimString(service);
				stuff = Utilities::splitString(service, ',');
				Utilities::trimString(stuff[0]);
				Utilities::trimString(stuff[1]);
				Utilities::trimString(stuff[2]);
				Utilities::trimString(stuff[3]);

				serv.emplace_back(stuff[0], stuff[1], stuff[2], stuff[3]);

			}
		}

		Beach *p = new RiverBeach(name, Coordinates(xc, yc), capacity, bf, serv, width, riverFlow, maxDepth);
		beaches.emplace(concelho, p);
	} catch(...){
		throw Utilities::WrongFileFormat("River Beach");
	}
}

ConcelhoBeachBST::iterator LeisureGuide::findBeachByName(string name) {
	//Searching for a beach with the given name in the beaches vector using find_if and a lambda function
	return find_if(beaches.begin(), beaches.end(), [=](const pair<string, Beach*> &p) {
		return p.second->getName() == name;
	});
}

bool LeisureGuide::removeBeach() {
	string name;
	cout << "What is the name of the beach that you wish to remove?\n";
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
	vector<Service> services;

	string concelho;
	cout << "What concelho does the beach belong to? " << endl;
	getline(cin, concelho);
	Utilities::trimString(concelho);

	string name;
	cout << "What is the name of the beach? " << endl;
	getline(cin, name);
	Utilities::trimString(name);

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
			Utilities::clearCinBuffer();
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
			Utilities::clearCinBuffer();
		}
		else {
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
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
			Utilities::clearCinBuffer();
		}
		else {
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	string response;
	bool blueFlag;
	cout << "Does the beach have blue flag (yes or no)? " << endl;

	while (true) {
		cin >> response;
		Utilities::trimString(response);
		if (cin.fail() || (response != "yes" && response != "no" && response != "Yes" && response != "No")) {
			cout << "Invalid input, please enter yes or no." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	blueFlag = ((response == "yes") || (response == "Yes"));

	//Ensuring cin is clear after using it as a stream
	Utilities::clearCinBuffer();

	string serviceName, serviceType, serviceDescription;

	while (true) {
		cout << "Do you want to add a service (yes or no)? " << endl;
		while (true) {
			cin >> response;
			Utilities::trimString(response);
			if (cin.fail() || (response != "yes" && response != "no" && response != "Yes" && response != "No")) {
				cout << "Invalid input, please enter yes or no." << endl;
				//Clearing error flag and cin buffer
				Utilities::clearCinBuffer();
			}
			else {
				//if cin didn't fail we have a good input so we break the loop
				break;
			}
		}	

		//Ensuring cin is clear after using it as a stream
		Utilities::clearCinBuffer();

		if (response == "yes" || response == "Yes") {

			cout << "What is the service's name?" << endl;
			getline(cin, serviceName);
			Utilities::trimString(serviceName);

			cout << "What is the service's type?" << endl;
			getline(cin, serviceType);
			Utilities::trimString(serviceType);

			cout << "Do you want to add a description to the service?" << endl;

			while (true) {
				cin >> response;
				Utilities::trimString(response);
				if (cin.fail() || (response != "yes" && response != "no" && response != "Yes" && response != "No")) {
					cout << "Invalid input, please enter yes or no." << endl;
					Utilities::clearCinBuffer();
					//It is not necessary to clear the buffer since getline leaves the buffer in a good state
				}
				else {
					//Clearing error flag and cin buffer
					Utilities::clearCinBuffer();
					//if cin didn't fail we have a good input so we break the loop
					break;
				}
			}

			//If adding a service description is desired
			if (response == "yes" || response == "Yes") {
				cout << "Service description: ";
				getline(cin, serviceDescription);

				services.emplace_back(serviceName, serviceType, serviceDescription, "0");
				continue;
			}

			//If the user does not want to add a service description
			services.emplace_back(serviceName, serviceType, "None", "0");
		} else {
			//If the user entered "no" or "No", he does not wish to input any (further) services
			break;
		}
	}

	string beachType;

	cout << "Is it a river beach or a bayou beach (river or bayou)?" << endl;

	while (true) {
		cin >> beachType;
		Utilities::trimString(beachType);
		if (cin.fail() || (beachType != "river" && beachType != "bayou" && beachType != "River" && beachType != "Bayou")) {
			cout << "Invalid input, please enter river or bayou." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}


	//Ensuring cin is clear after using it as a stream
	Utilities::clearCinBuffer();

	//If the user wants to create a river beach
	if (beachType == "river" || beachType == "River") {
		double width, riverFlow, maxDepth;

		cout << "What is the river's width? " << endl;
		while (true) {
			cin >> width;
			if (cin.fail() || width <= 0) {
				cout << "Invalid river width value, please insert a valid river width value (positive decimal)." << endl;
				//Clearing error flag and cin buffer
				Utilities::clearCinBuffer();
			}
			else {
				//Clearing error flag and cin buffer
				Utilities::clearCinBuffer();
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
				Utilities::clearCinBuffer();
			}
			else {
				//Clearing error flag and cin buffer
				Utilities::clearCinBuffer();
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
				Utilities::clearCinBuffer();
			} else {
				//if cin didn't fail we have a good input so we break the loop
				break;
			}
		}

		//Ensuring cin is clear after using it as a stream
		Utilities::clearCinBuffer();

		Beach *beachpntr = new RiverBeach(name, Coordinates(x, y), maxCapacity, blueFlag, services, width, riverFlow, maxDepth);
		beaches.emplace(concelho, beachpntr);
	}
	//If the user wants to create a bayou beach
	else {
		double usableAquaticArea;

		cout << "What is the bayou's usable aquatic area? " << endl;
		while (true) {
			cin >> usableAquaticArea;
			if (cin.fail() || usableAquaticArea <= 0) {
				cout << "Invalid bayou usable aquatic area, please insert a valid usable aquatic area (positive decimal)." << endl;
				//Clearing error flag and cin buffer
				Utilities::clearCinBuffer();
			} else {
				//Clearing error flag and cin buffer
				Utilities::clearCinBuffer();
				//if cin didn't fail we have a good input so we break the loop
				break;
			}
		}

		Beach *beachpntr = new BayouBeach(name, Coordinates(x, y), maxCapacity, blueFlag, services, usableAquaticArea);
		beaches.emplace(concelho, beachpntr);
	}

	cout << "Beach has been successfully created" << endl;
	return true;
}

bool LeisureGuide::removePOI(){
	//Getting input
	string name;
	cout << "What is the name of the POI that you wish to remove?\n";
	getline(cin, name);

	//Finding the POI
	auto it = findPOIByName(name);

	//POI was not found with the given name
	if (it == POIs.end()) {
		cout << "POI not found!" << endl;
		return false;
	}

	//POI was found, removing
	POIs.erase(it);

	return true;
}

vector<POI>::iterator LeisureGuide::findPOIByName(const string &name) {
	return find_if(POIs.begin(), POIs.end(), [=](const POI &poi){
		return poi.getName() == name;
	});
}

bool LeisureGuide::removeRestaurant(){
	//Getting input
	string name;
	cout << "What is the name of the Restaurant that you wish to remove?\n";
	getline(cin, name);

	//Finding the Restaurant
	auto it = findRestaurantByName(name);

	//Restaurant was not found with the given name
	if (it == restaurants.end()) {
		cout << "Restaurant not found!" << endl;
		return false;
	}

	//Restaurant was found, removing
	restaurants.erase(it);

	return true;
}

vector<Restaurant>::iterator LeisureGuide::findRestaurantByName(const string &name) {
	auto it = find_if(restaurants.begin(), restaurants.end(), [=](const Restaurant &r){
		return r.getName() == name;
	});
	return it;
}

bool LeisureGuide::removeLodging(){
	//Getting input
	string name;
	cout << "What is the name of the Lodging that you wish to remove?\n";
	getline(cin, name);

	//Finding the Lodging
	auto it = findLodgingByName(name);

	//Lodging was not found with the given name
	if (it == lodging.end()) {
		cout << "Lodging not found!" << endl;
		return false;
	}

	//Restaurant was found, removing
	lodging.erase(it);

	return true;
}

vector<Lodging>::iterator LeisureGuide::findLodgingByName(const string &name) {
	auto it = find_if(lodging.begin(), lodging.end(), [=](const Lodging &l){
		return l.getName() == name;
	});
	return it;
}

bool LeisureGuide::addRestaurant() {
	string name, description, iHour, fHour, day, response;
	Schedule sch;
	double x, y;

	cout << "What is the name of the Restaurant? " << endl;
	getline(cin, name);
	Utilities::trimString(name);

	//If the restaurant is found, it already exists (it is found if the iterator returned by findRestaurantByName is different from 0)
	if (findRestaurantByName(name) != restaurants.end()) {
		cout << "Restaurant already exists" << endl;
		return false;
	}

	cout << "What are the coordinates of the restaurant (X followed by Y)?" << endl;

	//Getting X
	while (true) {
		cin >> x;
		if (cin.fail()) {
			cout << "Invalid X value, please insert a valid X coordinate value (decimal number)." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
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
			Utilities::clearCinBuffer();
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	Coordinates coords(x, y);

	//Ensuring cin is clear after using it as a stream
	Utilities::clearCinBuffer();

	string transition;
	for (unsigned int i = 0; i < 7; i++)
	{
		cout << "When does the restaurant open on " << Utilities::weekdays[i] << " (HH:MM)?" << endl;
		while (true) {
			getline(cin, iHour);
			Utilities::trimString(iHour);
			if (! Utilities::correctHourFormat(iHour)) {
				cout << "Wrong hour format, must be HH:MM and max hour must be 23:59" << endl;
			}
			else {
				break;
			}
		}
		cout << "When does the restaurant close on " << Utilities::weekdays[i] << " (HH:MM)?" << endl;
		while (true) {
			getline(cin, fHour);
			Utilities::trimString(fHour);
			if (!Utilities::correctHourFormat(fHour)) {
				cout << "Wrong hour format, must be HH:MM and max hour must be 23:59" << endl;
			}
			else {
				break;
			}
		}
		if (iHour > fHour) {
			transition = iHour;
			iHour = fHour;
			fHour = transition;
		}
		day.assign(iHour + " to " + fHour);
		//Day schedule format: "HH:MM to HH:MM"
		sch.weekSchedule.push_back(day);
	}

	cout << "Do you want to add a description to the restaurant?" << endl;

	while (true) {
		getline(cin, response);
		Utilities::trimString(response);
		if (cin.fail() || (response != "yes" && response != "no" && response != "Yes" && response != "No")) {
			cout << "Invalid input, please enter yes or no." << endl;
			//It is not necessary to clear the buffer since getline leaves the buffer in a good state
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	if (response == "yes" || response == "Yes") {
		cout << "Restaurant description: ";
		getline(cin, description);
		Utilities::trimString(description);

		restaurants.emplace_back(name, sch, coords, description);
		return true;
	}

	restaurants.emplace_back(name, sch, coords, "None");
	return true;
}

bool LeisureGuide::addPOI() {
	string name, description, response;
	double x, y;

	cout << "What is the name of the POI? " << endl;
	getline(cin, name);
	Utilities::trimString(name);

	//If the POI is found, it already exists (it is found if the iterator returned by findPOIByName is different from 0)
	if (findPOIByName(name) != POIs.end()) {
		cout << "POI already exists" << endl;
		return false;
	}

	cout << "What are the coordinates of the POI (X followed by Y)?" << endl;

	//Getting X
	while (true) {
		cin >> x;
		if (cin.fail()) {
			cout << "Invalid X value, please insert a valid X coordinate value (decimal number)." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
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
			Utilities::clearCinBuffer();
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	Coordinates coords(x, y);

	//Ensuring the cin buffer is clear to use getline
	Utilities::clearCinBuffer();

	cout << "Do you want to add a description to the POI?" << endl;

	while (true) {
		getline(cin, response);
		Utilities::trimString(response);
		if (cin.fail() || (response != "yes" && response != "no" && response != "Yes" && response != "No")) {
			cout << "Invalid input, please enter yes or no." << endl;
			//It is not necessary to clear the buffer since getline leaves the buffer in a good state
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	if (response == "yes" || response == "Yes") {
		cout << "POI description: ";
		getline(cin, description);
		Utilities::trimString(description);

		POIs.emplace_back(name, coords, description);
		return true;
	}

	POIs.emplace_back(name, coords, "None");
	return true;
}

bool LeisureGuide::addLodging() {
	string name, description, response;
	double x, y;
	bool full;

	cout << "What is the name of the Lodging? " << endl;
	getline(cin, name);
	Utilities::trimString(name);

	//If the Lodging is found, it already exists (it is found if the iterator returned by findLodgingByName is different from 0)
	if (findLodgingByName(name) != lodging.end()) {
		cout << "Lodging already exists" << endl;
		return false;
	}

	cout << "What are the coordinates of the Lodging (X followed by Y)?" << endl;

	//Getting X
	while (true) {
		cin >> x;
		if (cin.fail()) {
			cout << "Invalid X value, please insert a valid X coordinate value (decimal number)." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
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
			Utilities::clearCinBuffer();
		}
		else {
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}


	Coordinates coords(x, y);

	cout << "Is the Lodging full (yes or no)? " << endl;

	while (true) {
		cin >> response;
		Utilities::trimString(response);
		if (cin.fail() || (response != "yes" && response != "no" && response != "Yes" && response != "No")) {
			cout << "Invalid input, please enter yes or no." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	full = ((response == "yes") || (response == "Yes"));

	//Ensuring cin is clear after using it as a stream
	Utilities::clearCinBuffer();

	cout << "Do you want to add a description to the Lodging?" << endl;

	while (true) {
		getline(cin, response);
		Utilities::trimString(response);
		if (cin.fail() || (response != "yes" && response != "no" && response != "Yes" && response != "No")) {
			cout << "Invalid input, please enter yes or no." << endl;
			//It is not necessary to clear the buffer since getline leaves the buffer in a good state
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			break;
		}
	}

	if (response == "yes" || response == "Yes") {
		cout << "Lodging description: ";
		getline(cin, description);
		Utilities::trimString(description);

		lodging.emplace_back(name, coords, full, description);
		return true;
	}

	lodging.emplace_back(name, coords, full, "None");
	return true;
}

bool LeisureGuide::modifyBeach(){
	string beachname;
	cout << "What is the name of the beach you want to modify?" << endl;
	getline(cin, beachname);
	Utilities::trimString(beachname);

	auto it = findBeachByName(beachname);

	if(it == beaches.end()){
		cout << "Beach not found! Exiting..." << endl;
		return false;
	}

	//Because we are using a set and the underlying BST needs to stay balanced, we should remove the element, modify it, and only then insert it again
	auto copied_pair = *it;

	beaches.erase(it);

	cout << "Beach found! Initiating modification process." << endl;
	copied_pair.second->modifyBeach();

	//Inserting the modified element back again
	beaches.emplace(copied_pair);

	return true;
}

bool LeisureGuide::modifyRestaurant() {
	string restaurantname;
	cout << "What is the name of the restaurant you want to modify?" << endl;
	getline(cin, restaurantname);
	Utilities::trimString(restaurantname);

	auto it = findRestaurantByName(restaurantname);

	if (it == restaurants.end()) {
		cout << "Restaurant not found! Exiting..." << endl;
		return false;
	}

	cout << "Restaurant found! Initiating modification process." << endl;
	it->modifyRestaurant();
	return true;
}

bool LeisureGuide::modifyPOI() {
	string POIname;
	cout << "What is the name of the POI you want to modify?" << endl;
	getline(cin, POIname);
	Utilities::trimString(POIname);

	auto it = findPOIByName(POIname);

	if (it == POIs.end()) {
		cout << "POI not found! Exiting..." << endl;
		return false;
	}

	cout << "POI found! Initiating modification process." << endl;
	it->modifyPOI();
	return true;
}

bool LeisureGuide::modifyLodging() {
	string lodgingname;
	cout << "What is the name of the Lodging you want to modify?" << endl;
	getline(cin, lodgingname);
	Utilities::trimString(lodgingname);

	auto it = findLodgingByName(lodgingname);

	if (it == lodging.end()) {
		cout << "Lodging not found! Exiting..." << endl;
		return false;
	}

	cout << "Lodging found! Initiating modification process." << endl;
	it->modifyLodging();
	return true;
}

void LeisureGuide::sortEverythingByDistanceToBeach(Beach *b){
	sortPOIsByDistanceToBeach(b);
	sortRestaurantsByDistanceToBeach(b);
	sortLodgingByDistanceToBeach(b);
}

void LeisureGuide::sortRestaurantsByDistanceToBeach(Beach *b){
	auto beachcoords = b->getCoords();
	sort(restaurants.begin(), restaurants.end(), [&beachcoords](const Restaurant &r1, const Restaurant &r2){
		return r1.getCoordinates().distanceTo(beachcoords) < r2.getCoordinates().distanceTo(beachcoords);
	});
}

void LeisureGuide::sortPOIsByDistanceToBeach(Beach *b){
	auto beachcoords = b->getCoords();
	sort(POIs.begin(), POIs.end(), [&beachcoords](const POI &poi1, const POI &poi2){
		return poi1.getCoordinates().distanceTo(beachcoords) < poi2.getCoordinates().distanceTo(beachcoords);
	});
}

void LeisureGuide::sortLodgingByDistanceToBeach(Beach *b){
	auto beachcoords = b->getCoords();
	sort(lodging.begin(), lodging.end(), [&beachcoords](const Lodging &l1, const Lodging &l2){
		return l1.getCoordinates().distanceTo(beachcoords) < l2.getCoordinates().distanceTo(beachcoords);
	});
}

void LeisureGuide::displaySortedByDistance() {
	string beachname;
	cout << "What is the name of the beach you want to search for?" << endl;

	getline(cin, beachname);
	Utilities::trimString(beachname);

	auto it = findBeachByName(beachname);

	if (it == beaches.end()) {
		cout << "Beach not found! Exiting..." << endl;
		return;
	}

	//Keeping it at 3 results for now, but we can ask for user input later on if need be
	int nresults = 3;

	//Sorting the internal data by distance to the found beach
	sortEverythingByDistanceToBeach(it->second);

	//Getting the coordinates of the beach for distance printing
	auto beachcoords = it->second->getCoords();

	//Printing the results

	//For Restaurants
	if (restaurants.size() != 0) {
		if (restaurants.size() < nresults) {
			if(restaurants.size()==1)
				cout << "The closest Restaurant to the given beach is:" << endl;
			else
				cout << "The " << restaurants.size() << " closest Restaurants to the given beach are:" << endl;
			nresults = restaurants.size();
		}
		else
			cout << "The " << nresults << " closest Restaurants to the given beach are:" << endl;

		for (unsigned int i = 0; i < nresults; ++i) {
			cout << "result number " << i + 1 << ":" << endl;
			cout << restaurants.at(i);
			cout << "Distance to given beach: " << restaurants[i].getCoordinates().distanceTo(beachcoords) << endl << endl;
		}
	} else {
		cout << "There are no restaurants listed on the leisure guide " << endl;
	}

	Utilities::pause();
	cout << endl;

	nresults = 3;

	//For POIs
	if (POIs.size() != 0) {
		if (POIs.size() < nresults) {
			if (POIs.size() == 1)
				cout << "The closest POI to the given beach is:" << endl;
			else
				cout << "The " << POIs.size() << " closest POIs to the given beach are:" << endl;
			nresults = POIs.size();
		}
		else
			cout << "The " << nresults << " closest POIs to the given beach are:" << endl;
		for (unsigned int i = 0; i < nresults; ++i) {
			cout << "result number " << i + 1 << ":" << endl;
			cout << POIs.at(i);
			cout << "Distance to given beach: " << POIs[i].getCoordinates().distanceTo(beachcoords) << endl << endl;
		}
	} else {
		cout << "There are no POIs listed on the leisure guide " << endl;
	}

	Utilities::pause();
	cout << endl;

	nresults = 3;

	//For Lodging
	if (lodging.size() != 0) {
		if (lodging.size() < nresults) {
			if (lodging.size() == 1)
				cout << "The closest Lodging facility to the given beach is:" << endl;
			else
				cout << "The " << lodging.size() << " closest Lodging facilities to the given beach are:" << endl;
			nresults = lodging.size();
		}
		else
			cout << "The " << nresults << " closest Lodging facilities to the given beach are:" << endl;
		for (unsigned int i = 0; i < nresults; ++i) {
			cout << "result number " << i + 1 << ":" << endl;
			cout << lodging.at(i);
			cout << "Distance to given beach: " << lodging[i].getCoordinates().distanceTo(beachcoords) << endl << endl;
		}
	} else {
		cout << "There are no lodging facilities listed on the leisure guide " << endl;
	}

	//All results listed successfully
}

void LeisureGuide::displayBeachesByConcelho() {

	cout << "What Concelho do you want to display the beaches for?" << endl;

	string input;
	getline(cin, input);
	Utilities::trimString(input);

	auto allConcelhos = getAllConcelhos();

	auto it = find(allConcelhos.begin(), allConcelhos.end(), input);

	if(it == allConcelhos.end()){
		cout << "Given concelho was not found!" << endl;
		return;
	}

	auto desiredBeaches = getBeachesByConcelho(input);
	if(!desiredBeaches.empty()) {
		cout << "The beaches for " << input << " are:" << endl;
		for(auto const &desiredBeach : desiredBeaches){
			desiredBeach->print(cout);
		}
	} else {
		cout << "No beaches were found for the given concelho!" << endl;
	}
}

void LeisureGuide::displayBeachInfo() {

	cout << "What is the name of the beach for which you desire to print the info for?" << endl;
	string name;
	getline(cin, name);

	Utilities::trimString(name);

	auto it = findBeachByName(name);

	if(it == beaches.end()){
		cout << "Beach not found! Exiting!" << endl;
		return;
	}

	cout << "The info for the requested beach is:" << endl;
	it->second->print(cout);
}

void LeisureGuide::displayPOIInfo() {
	cout << "What is the name of the POI for which you desire to print the info for?" << endl;
	string name;
	getline(cin, name);

	Utilities::trimString(name);

	auto it = findPOIByName(name);

	if(it == POIs.end()){
		cout << "POI not found! Exiting!" << endl;
		return;
	}

	cout << "The info for the requested POI is:" << endl;
	cout << *it;
}

void LeisureGuide::displayRestaurantInfo() {
	cout << "What is the name of the Restaurant for which you desire to print the info for?" << endl;
	string name;
	getline(cin, name);

	Utilities::trimString(name);

	auto it = findRestaurantByName(name);

	if(it == restaurants.end()){
		cout << "Restaurant not found! Exiting!" << endl;
		return;
	}

	cout << "The info for the requested restaurant is:" << endl;
	cout << *it;
}

void LeisureGuide::displayLodgingInfo() {
	cout << "What is the name of the Lodging for which you desire to print the info for?" << endl;
	string name;
	getline(cin, name);

	Utilities::trimString(name);

	auto it = findLodgingByName(name);

	if(it == lodging.end()){
		cout << "Lodging not found! Exiting!" << endl;
		return;
	}

	cout << "The info for the requested lodging is:" << endl;
	cout << *it;
}

 bool LeisureGuide::closeTouristicPoint() {
	cout << "What type of touristic point do you desire to close? (Restaurant, POI, Lodging)" << endl;
	string type;
	classType cType;

	while (true) {
		getline(cin, type);
		Utilities::trimString(type);
		if (cin.fail() || (type != "Restaurant" && type != "restaurant" && type != "POI" && type != "poi" && type != "lodging" && type != "Lodging")) {
			cout << "Invalid input, please enter a valid type." << endl;
			//Clearing error flag and cin buffer
			Utilities::clearCinBuffer();
		}
		else {
			//if cin didn't fail we have a good input so we break the loop
			if (type == "Restaurant" || type == "restaurant")
				cType = classType::restaurant;
			else
				if (type == "POI" || type == "poi")
					cType = classType::poi;
				else
					if (type == "Lodging" || type == "lodging")
						cType = classType::lodging;
			break;
		}
	}

	cout << "What is the day when it will be closed? (YYYY/MM/DD) " << endl;
	string date;
	while (true) {
		getline(cin, date);
		Utilities::trimString(date);
		if (!Utilities::correctDateFormat(date)) {
			cout << "Wrong date format, must be YYYY/MM/DD and must be an acceptable date" << endl;
		}
		else {
			break;
		}
	}

	cout << "What is the name of the touristic point that you desire to close?" << endl;
	string name;
	getline(cin, name);
	Utilities::trimString(name);

	TouristicPointPointer t;
	
	if (cType == classType::lodging) {
		auto it = findLodgingByName(name);
		if (it == lodging.end()) {
			cout << "Lodging doesn't exist" << endl;
			return false;
		}

		TouristicPoint * tpp = new Lodging(*it);

		t.touristicPoint = tpp;

		lodging.erase(it);
	}
	else {
		if (cType == classType::poi) {
			auto it = findPOIByName(name);
			if (it == POIs.end()) {
				cout << "POI doesn't exist" << endl;
				return false;
			}

			TouristicPoint * tpp = new POI(*it);

			t.touristicPoint = tpp;

			POIs.erase(it);
		}
		else {
			if (cType == classType::restaurant) {
				auto it = findRestaurantByName(name);
				if (it == restaurants.end()) {
					cout << "Restaurant doesn't exists" << endl;
					return false;
				}

				TouristicPoint * tpp = new Restaurant(*it);

				t.touristicPoint = tpp;

				restaurants.erase(it);
			}
		}
	}

	t.touristicPoint->setCloseDate(date);

	closedTouristicPoints.insert(t); 

	return true;
}

bool LeisureGuide::reopenTouristicPoint() {
	cout << "What is the name of the touristic point that you desire to reopen?" << endl;
	string name;
	getline(cin, name);
	Utilities::trimString(name);

	for (auto it = closedTouristicPoints.begin(); it != closedTouristicPoints.end(); it++)
	{
		TouristicPointPointer tp = (*it);
		TouristicPoint* t = tp.touristicPoint;
		classType cType = t->getType();
		if (t->getName() == name) {
			if (cType == classType::lodging) {
				Lodging* lp = dynamic_cast<Lodging*>(t);
				Lodging l(*lp);
				l.setCloseDate("");
				lodging.push_back(l);
			}
			else {
				if (cType == classType::poi) {
					POI* pp = dynamic_cast<POI*>(t);
					POI p(*pp);
					p.setCloseDate("");
					POIs.push_back(p);
				}
				else {
					if (cType == classType::restaurant) {
						Restaurant* rp = dynamic_cast<Restaurant*>(t);
						Restaurant r(*rp);
						r.setCloseDate("");
						restaurants.push_back(r);
					}
				}
			}
			closedTouristicPoints.erase(tp);
			return true;
		}
	}

	cout << "No touristic point with that name was found." << endl;
	return false;
}

void LeisureGuide::displayClosedTouristicPoints() {
	int c = 0;
	int i = 0;
	for (auto it = closedTouristicPoints.begin(); it != closedTouristicPoints.end(); it++)
	{
		c++;
		TouristicPointPointer tp = (*it);
		TouristicPoint* t = tp.touristicPoint;
		classType cType = t->getType();
		if (cType == classType::restaurant) {
			if(i == 0)
				cout << "Restaurants: " << endl << endl;
			cout << *t << endl;
			i++;
		}
	}
	cout << endl;
	i = 0;
	for (auto it = closedTouristicPoints.begin(); it != closedTouristicPoints.end(); it++)
	{
		TouristicPointPointer tp = (*it);
		TouristicPoint* t = tp.touristicPoint;
		classType cType = t->getType();
		if (cType == classType::poi) {
			if(i == 0)
				cout << "POIs: " << endl;
			cout << *t << endl;
			i++;
		}
	}
	cout << endl;
	i = 0;
	for (auto it = closedTouristicPoints.begin(); it != closedTouristicPoints.end(); it++)
	{
		TouristicPointPointer tp = (*it);
		TouristicPoint* t = tp.touristicPoint;
		classType cType = t->getType();
		if (cType == classType::lodging) {
			if(i == 0)
				cout << "Lodging: " << endl;
			cout << *t << endl;
			i++;
		}
	}
	cout << endl;
	if (c == 0) {
		cout << "No closed Touristic Points" << endl << endl;
	}
}

void LeisureGuide::saveClosedTouristicPoints(ofstream &s) {
	for (auto it = closedTouristicPoints.begin(); it != closedTouristicPoints.end(); it++)
	{
		TouristicPointPointer tp = (*it);
		TouristicPoint* t = tp.touristicPoint;
		classType cType = t->getType();
		if (cType == classType::restaurant) {
			Restaurant* rp = dynamic_cast<Restaurant*>(t);
			Restaurant r(*rp);
			s << "restaurant | " << r.getCloseDate() << " | " << r.toString() << endl;
		}
		if (cType == classType::poi) {
			POI* pp = dynamic_cast<POI*>(t);
			POI p(*pp);
			s << "poi | " << p.getCloseDate() << " | " << p.toString() << endl;
		}
		if (cType == classType::lodging) {
			Lodging* lp = dynamic_cast<Lodging*>(t);
			Lodging l(*lp);
			s << "lodging | " << l.getCloseDate() << " | " << l.toString() << endl;
		}
	}
}

void LeisureGuide::createTouristicPoint(vector<string> &touristicPoint) {
	for (auto &tp : touristicPoint) {
		createTouristicPoint(tp);
	}
}

void LeisureGuide::createTouristicPoint(string &touristicPoint) {
	//TouristicPoint file string format
	//type | closeDate | (type specific information)

	vector<string> infos = Utilities::splitString(touristicPoint, '|');

	Utilities::trimString(infos[0]);

	TouristicPointPointer t;

	if (infos[0] == "restaurant") {
		Utilities::trimString(infos[1]);
		Utilities::trimString(infos[2]);
		Utilities::trimString(infos[3]);
		Utilities::trimString(infos[4]);
		Utilities::trimString(infos[5]);

		string name = infos[2];
		vector<string> coords = Utilities::splitString(infos[3], ',');
		string desc = infos[5];

		Utilities::trimString(coords[0]);
		Utilities::trimString(coords[1]);

		Schedule sch;
		sch.weekSchedule = Utilities::splitString(infos[4], ',');

		for (auto &line : sch.weekSchedule) {
			Utilities::trimString(line);
		}

		TouristicPoint *tp = new Restaurant(name, sch, Coordinates(stod(coords[0]), stod(coords[1])), desc);
		tp->setCloseDate(infos[1]);

		t.touristicPoint = tp;
	} else
	if (infos[0] == "poi") {
		Utilities::trimString(infos[1]);
		Utilities::trimString(infos[2]);
		Utilities::trimString(infos[3]);
		Utilities::trimString(infos[4]);

		string name = infos[2];
		string desc = infos[4];

		vector<string> coords = Utilities::splitString(infos[3], ',');

		Utilities::trimString(coords[0]);
		Utilities::trimString(coords[1]);

		TouristicPoint *tp = new POI(name, Coordinates(stod(coords[0]), stod(coords[1])), desc);
		tp->setCloseDate(infos[1]);

		t.touristicPoint = tp;
	} else
	if (infos[0] == "lodging") {
		Utilities::trimString(infos[1]);
		Utilities::trimString(infos[2]);
		Utilities::trimString(infos[4]);
		Utilities::trimString(infos[5]);

		bool full = (infos[4] == "1");

		string name = infos[2];
		string desc = infos[5];
		vector<string> coords = Utilities::splitString(infos[3], ',');

		Utilities::trimString(coords[0]);
		Utilities::trimString(coords[1]);

		TouristicPoint *tp = new Lodging(name, Coordinates(stod(coords[0]), stod(coords[1])), full, desc);
		tp->setCloseDate(infos[1]);

		t.touristicPoint = tp;
	}

	closedTouristicPoints.insert(t);
}

int LeisureGuide::checkType(const string &type){

	if (!dates.empty()){
		for (int i = 0; i < dates.size(); i++){
			if(dates[i].top().first.getType() == type){
				return i;
			}
		}
	}
	return -1;
}

vector<Inspection> LeisureGuide::getDates(){
	return dates;
}


void LeisureGuide::createInspections() {

	dates.clear();

	for (auto &dt : beaches) {

		vector<Service> serv = dt.second->getServices();

		for (auto s : serv) {
		
			if (s.getInspectionDate() == "0")
				continue;

			int i = checkType(s.getType());
			
			if ( i != -1) {
				pair<Service, string> p(s, dt.second->getName());
				dates[i].push(p);

			}

			else{
				pair<Service, string> p(s, dt.second->getName());
				Inspection k;
				k.push(p);
				dates.push_back(k);
			}
		}
	}
}


bool LeisureGuide::addInspection() {
	string beachname, servicename, date;
	ConcelhoBeachBST::iterator i;
	cout << "What is the name of the beach?\n";
	getline(cin, beachname);
	cout << endl;
	i = findBeachByName(beachname);
	if (i == beaches.end()) {
		cout << "Beach does not exist!\n";
		return false;
	}

	auto cpy = *i;
	cout << "What is the name of the service?\n";

	while (true) {
		getline(cin, servicename);
		cout << endl;
		for (auto &f : i->second->getServices()) {
			if (f.getName() == servicename) {
				cout << "Insert the date of last inspection in the format YYYY/MM/DD\n";
				getline(cin, date);

				while(!Utilities::correctDateFormat(date)) {
					cout << "The date inserted is not in the correct format, please insert a date in the YYYY/MM/DD format\n";
					getline(cin, date);
				}

				if (f.getInspectionDate() == "0" || Utilities::DatesCompare(date, f.getInspectionDate()) ) {
					changeInspection(i, servicename, date);
					updateInspections(f, beachname);
					cout << "Addition successful!\n";
					return true;
				} else {
					cout << "Date inserted is older than the existing one. Returning to the menu.\n";
					return false;
				}
			}
		}
	}
	cout << "Service does not exist. Insert an existing service at " << beachname << "\t";
}

void LeisureGuide::changeInspection(const ConcelhoBeachBST::iterator &i, const string &servicename, const string &date) {
	auto cpy = *i;
	beaches.erase(i);
	
	vector<Service> aux = cpy.second->getServices();
	for (auto &x : aux) {
		if (x.getName() == servicename) {
			x.setInspectionDate(date);
			break;
		}
	}
	cpy.second->setServices(aux);

	beaches.emplace(cpy);

}


void LeisureGuide::updateInspections(Service &s, string &beachName) {
	Inspection aux;

	int i = checkType(s.getType());

	if (i == -1) {
		aux.push(make_pair(s, beachName));
		dates.push_back(aux);
	}

	else {
		while (!dates[i].empty()) {
			if (dates[i].top().second == beachName) {
				if (dates[i].top().first.getName() == s.getName()) {
					dates[i].pop();
					aux.emplace(s, beachName);
				}
				else {
					aux.push(dates[i].top());
					dates[i].pop();
				}
			}
			else {
				aux.push(dates[i].top());
				dates[i].pop();
			}
		}

		dates[i] = aux;
	}
}



void LeisureGuide::displayInspectionofaBeach() {
	ConcelhoBeachBST::iterator i;
	string beachname;
	cout << "What is the name of the beach?\n";
	getline(cin, beachname);
	i = findBeachByName(beachname);
	if (i == beaches.end()) {
		cout << "The inserted Beach does not exist!\n";
        return;
	}

	vector<Service> serv = i->second->getServices();

	cout << "Inspections at " << beachname << endl;
	for (auto &j : serv) {
		cout << j << "\n\n";
	}
}

void LeisureGuide::displayInspectionTypeService() {
	
	createInspections();

	string type;

	cout << "What is the Service Type?\n";
	getline(cin, type);

	for (auto &i : dates) {
		if (i.top().first.getType() != type)
			continue;
		else {
			Inspection aux = i;
			while (!aux.empty()) {
				cout << "Beach: " << aux.top().second << endl << "Service:\n";
				cout << aux.top().first << endl;
				aux.pop();
			}
			return;
		}	
	}
	cout << "Type does not exist...\n";

}