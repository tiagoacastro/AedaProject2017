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
		string getDescription() const;
		void setDescription(const string &description);
		string getName() const;
		void setName(const string &name);
		Schedule getSchedule() const;
		void setSchedule(const Schedule& sch);
		string getType() const;
		void setType(const string &type);

		friend ostream & operator<<(ostream &o, const Service &s);

};
