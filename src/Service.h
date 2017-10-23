#pragma once
#include <string>
#include <vector>
using namespace std;

struct Schedule {
	vector<string> weekSchedule;
};

class Service {
	private:
		string name;
		string type;
		Schedule sch;
		string description;
	public:
		Service(string name, string type, Schedule sch, string description);
};