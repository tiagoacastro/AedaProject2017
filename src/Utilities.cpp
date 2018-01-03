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
		if(s.find_first_not_of(' ') == string::npos){
			//String is only spaces, set it to empty string and return
			s = "";
			return;
		}

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
			input = input.substr(input.find(splitter) + splitter.length());
		}

		//Push back the remainder, or the whole string if no ocurrence of splitter exists
		output.push_back(input);

		return output;
	}

	vector<string> splitString(const string &input, char splitter) {
		vector<string> output;
		stringstream temp(input);
		string currentsegment;

		//while the splitter sequence exists in the stream
		while (getline(temp, currentsegment, splitter)) {
			output.push_back(currentsegment);
		}

		return output;
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
			Utilities::clearCinBuffer();
		}

		//Pause to see output
		cout << "Press enter to continue....";
		cin.get();

		//Ensuring cin is clear after receiving input in it (cin.get())
		//If cin.get received input (if it was just enter there is no need to clear, thus this verification again)
		if (cin.rdbuf()->in_avail() > 0) {
			Utilities::clearCinBuffer();
		}
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

	bool correctHourFormat(string hour) {
		if (hour.length() == 5) {
			if (hour.at(2) == ':') {
				for (unsigned int i = 0; i < 5; i++)
				{
					if (i != 2)
						if (!isNumber(hour.at(i)))
							return false;
				}
			}
			if (hour.at(0) < '3') {
				if (hour.at(0) == '2') {
					if (hour.at(1) >= '4')
						return false;
				}
				if (hour.at(3) >= '6')
					return false;
				return true;
			}
		}
		return false;
	}


	bool correctDateFormat(string &la) {

		vector<string> k = splitString(la, "/");
		if (la.empty() || k.size() != 3)
			return false;
		vector<int> x;
		for (auto &i : k){
			trimString(i);
			if (stoi(i) != 0)
				x.push_back(stoi(i));
			else
				return false;
		}


		if (x.size() == 3) {

	
			if (x[0] <= 9999 && x[0] >= 1000) {
				if (x[1] == 1 || x[1] == 3 || x[1] == 5 || x[1] == 7 || x[1] == 8 || x[1] == 10 || x[1] == 12)
					return (x[2] <= 31 && x[2] >= 1);
				else if (x[1] == 2)
					return (x[2] <= 28 && x[2] >= 1);
				else if (x[1] == 4 || x[1] == 6 || x[1] == 9 || x[1] == 10) 
					return (x[2] <= 30 && x[2] >= 1);
			}
		}
		return false;
	}

	bool DatesCompare(string &l, string &r) {
		if (!(correctDateFormat(l) && correctDateFormat(r)))
			return false;

		vector<string> lv = splitString(l, "/"), rv = splitString(r,"/");

		if (lv[0] < rv[0])
			return false;
		else if (lv[0] > rv[0])
			return true;
		else {
			if (lv[1] < rv[1])
				return false;
			else if (lv[1] > rv[1])
				return true;
			else {
				if (lv[2] < rv[2])
					return false;
				else 
					return true;
			}
		}

	}


	bool isNumber(char c) {
		return c >= '0' && c <= '9';
	}

	void clearCinBuffer(){
		//Clears any potential set flags
		cin.clear();
		//Ignores everything in the cin buffer
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	bool correctDateFormat(string &la) {
		vector<string> k = splitString(la, "/");
		vector<int> x;
		for (auto &i : k) {
			trimString(i);
			if (stoi(i) != 0)
				x.push_back(stoi(i));
			else
				return false;
		}

		if (x.size() == 3) {
			if (x[0] <= 9999 && x[0] >= 0000) {
				if (x[1] == 01 || x[1] <= 03 || x[1] == 05 || x[1] == 07 || x[1] == 8 || x[1] == 10 || x[1] == 12)
					return (x[2] <= 31 && x[2] >= 01);
				else if (x[1] == 02)
					return (x[2] <= 28 && x[2] >= 01);
				else if (x[1] == 04 || x[1] == 06 || x[1] == 9 || x[1] == 10)
					return (x[2] <= 30 && x[2] >= 01);
			}
		}
		return false;
	}
}