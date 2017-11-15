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

void LeisureGuide::createBayouBeach(vector<string> &beach){
	pair<string, *BayouBeach>

}

void LeisureGuide::createRiverBeach(vector<string> &beach){

}
