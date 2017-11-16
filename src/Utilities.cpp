#include "Utilities.h"

namespace Utilities {
	vector<string> ReadFile(string path) {

		vector<string> inputstuff;

		ifstream myfile;
		string line;

		myfile.open(path);

		while (getline(myfile, line)) {
			inputstuff.push_back(line);
		}

		myfile.close();

		return inputstuff;
	}

	vector<string> ReadFile(ifstream &input) {
		vector<string> inputstuff;
		string line;

		while (getline(input, line)) {
			inputstuff.push_back(line);
		}

		return inputstuff;
	}

	int countCharInString(string input, char searchchar) {
		int counter = 0;
		for(char c : input) {
			if (c == searchchar)
				counter++;
		}

		return counter;
	}

	bool compareDiffSizeStrings(string a, string b) {
		bool output = true;

		if (a.size() < b.size()) {
			for (int i = 0; i < a.size(); i++) {
				if (a[i] != b[i]) {
					output = false;
					break;
				}
			}
		}
		else {
			for (int i = 0; i < b.size(); i++) {
				if (b[i] != a[i]) {
					output = false;
					break;
				}
			}
		}

		return output;
	}

	void trimString(string &s) {
		if (s.find(' ') != string::npos) {
			s = s.substr(s.find_first_not_of(' ')); // Cut spaces to the left
			s = s.substr(0, s.find_last_not_of(' ') + 1); // Cut spaces to the right
		}
	}

	vector<string> splitString(string input, string splitter) {
		vector<string> output;

		//while the splitter sequence exists in input
		while (input.find(splitter) != string::npos) {
			output.push_back(input.substr(0, input.find(splitter)));
			input = input.substr(input.find(splitter) + splitter.length() + 1);
		}

		//Push back the remainder, or the whole string if no ocurrence of splitter exists
		output.push_back(input);

		return output;
	}

	vector<string> splitString(string input, char splitter) {
		return splitString(input, to_string(splitter));
	}

	void clearScreen() {
		//system("cls"); //temporary - will move to something else later on due to not being cross platform and having security issues
		cout << string(100, '\n'); //this is also not the best solution due to being a bit laggy but is the easiest to implement and 100% cross platform while avoiding system calls
	}

	void pause() {
		//Legacy explanation comments, moved from where cin.get() was used to pause:
		//
		//This seems like it will be necessary before every cin.get(),
		//because it seems that cin is getting the "\n" from the enter press at the end of every input...
		//So, cin.ignore before pause is mandatory!
		//However, if cin.ignore is used and there is nothing in the buffer, it waits until it gets something, thus resulting in a double pause.
		//To get around that we check if there is something in the cin buffer and we only clear if there is

		//If there are more than 0 characters in the cin buffer, clear them
		if (cin.rdbuf()->in_avail() > 0) {
			//Ignores everything in the cin buffer
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			//Clears any potential set flags
			cin.clear();
		}

		//Pause to see output
		cout << "Press enter to continue....";
		cin.get();
	}

	string minutesToHHMM(unsigned int minutes) {

		//Final time
		int hours = 0;

		while (minutes >= 60) {
			minutes -= 60;
			hours++;
		}

		stringstream ss;
		ss << setfill('0') << setw(2) << hours << ":" << setw(2) << minutes;

		return ss.str();
	}

	time minutesToTime(int minutes) {
		time temptime;
		if (minutes >= 10080) {
			temptime.weekday = 6;
			temptime.hourAndMinutes = "23:59";
			return temptime;
		}

		//Final time
		int hours = 0;
		int days = 0;


		while (minutes >= 60) {
			minutes -= 60;
			hours++;
		}

		while (hours >= 24) {
			hours -= 24;
			days++;
		}

		stringstream ss;
		ss << setfill('0') << setw(2) << hours << ":" << setw(2) << minutes;

		temptime.weekday = days;
		temptime.hourAndMinutes = ss.str();

		return temptime;
	}

	unsigned int HHMMtoMinutes(string hhmm) {

		//considering that the string is in the HH:MM format

		//getting hours string
		string hours = hhmm.substr(0, hhmm.find(":"));
		//hhmm is now only MM (after ':' )
		hhmm = hhmm.substr(hhmm.find(":") + 1);

		//hours converted to int * 60 (converting to minutes) + hhmm converted to int which now was only MM
		return stoi(hours)*60 + stoi(hhmm);
	}
}