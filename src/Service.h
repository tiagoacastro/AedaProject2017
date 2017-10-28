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
	const string& getDescription() const;
	void setDescription(const string& description);
	const string& getName() const;
	void setName(const string& name);
	const Schedule& getSch() const;
	void setSch(const Schedule& sch);
	const string& getType() const;
	void setType(const string& type);
	friend ostream & operator<<(ostream & o, const Service & s);

};
