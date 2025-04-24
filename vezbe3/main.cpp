#include <iostream>
#include<vector>
#include <algorithm>

using namespace std;
 
class FlyingObject {
protected:
	string name;
public:
	virtual void fly() const = 0;

	FlyingObject(string name):name(name) {}
	virtual ~FlyingObject() {}

	string getName() const { return name; };

};
	
class Airplane: public FlyingObject {
public:
	Airplane(string name):FlyingObject(name){}
	void fly() const override {
	
		cout << "Avion " << name << " leti na visini od 10000m." << endl;
	
	}

};


class Helicopter :public FlyingObject {
public:
	Helicopter(string name) :FlyingObject(name) {}
	void fly() const override {

		cout << "Helikopter " << name << " leti na visini od 2000m." << endl;

	}

};

class Drone : public FlyingObject {
public: 
	Drone(string name):FlyingObject(name){}

	void fly() const override {

		cout << "Dron " << name << " leti autonomno na visini od 500m." << endl;
	}
};

void searchByName(vector<FlyingObject*>& o, const string& TargetName) {

	auto iterator = find_if(o.begin(),o.end(),
		[&](FlyingObject* obj) {
			return obj->getName() == TargetName;		
		});
	if (iterator != o.end())
	{
		(*iterator)->fly();
	}
	else {
		cout << "Ne postoji objekat tog imena." << endl;
	}

}

void sortByName(vector<FlyingObject*>& o) {
	sort(o.begin(), o.end(), 
		[](FlyingObject* a, FlyingObject* b) {
			return a->getName() < b->getName();
		});
}


void droneFirst(vector<FlyingObject*>& o) {

	partition(o.begin(), o.end(), 
		[](FlyingObject* obj)
		{
			return dynamic_cast<Drone*>(obj) != nullptr;
		});

}
void droneFirst_Stable(vector<FlyingObject*>& o) {

	stable_partition(o.begin(), o.end(),
		[](FlyingObject* obj)
		{
			return dynamic_cast<Drone*>(obj) != nullptr;
		});
}
int count_Airplane(vector<FlyingObject*>& o) {
	int count = count_if(o.begin(), o.end(),
		[](FlyingObject* obj) {
			return dynamic_cast<Airplane*>(obj) != nullptr;
		});

		return count;
}

void find_Airplane_Name(vector<FlyingObject*>& o, const string& targetName) {
	auto iterator=find_if(o.begin(), o.end(),
		[&](FlyingObject* obj)
		{ Airplane* a = dynamic_cast<Airplane*>(obj);
	return
		 a != nullptr && a->getName() == targetName;		}
	);
	if (iterator != o.end())
		(*iterator)->fly();
	else {
		cout << "Avion sa tim imenom ne postoji" << endl;
	}

}
void stabe_sort(vector<FlyingObject*>& o) {

	stable_sort(o.begin(), o.end(),
		[](FlyingObject* a, FlyingObject* b)
		{
			return a->getName() < b->getName(); }


		); 

}

int main() {
	vector<FlyingObject*> objekti;
	objekti.push_back(new Airplane("A1"));
	objekti.push_back(new Airplane("K2"));
	objekti.push_back(new Airplane("O3"));

	objekti.push_back(new Helicopter("P1"));
	objekti.push_back(new Helicopter("S2"));
	objekti.push_back(new Helicopter("B3"));

	cout << "-----------------------"<<endl;
	for (auto o : objekti)
		o->fly();

	cout << "-----------------------" << endl;
	sortByName(objekti);
	for (auto o : objekti)
		o->fly();

	cout << "-----------------------" << endl;
	searchByName(objekti,"Avion");

	cout << "-------------ADD DRONE -----------" << endl;
	objekti.push_back(new Drone("A5"));
	objekti.push_back(new Drone("M20"));

	for (auto o : objekti)
		o->fly();


	cout << "-------------------" << endl;
	droneFirst_Stable(objekti);

	for (auto o : objekti)
		o->fly();

	cout << "-------------------" << endl;
	droneFirst(objekti);

	for (auto o : objekti)
		o->fly();
	
	cout << "-------------------" << endl;
	int number= count_Airplane(objekti);
	cout << "Number of Airplane is "<<number << endl;

	cout << "-------------------" << endl;
	find_Airplane_Name(objekti, "Airline");

	cout << "-----------Stable sort--------" << endl;
	stabe_sort(objekti);
	for (auto o : objekti)
		o->fly();

	return 0;
}