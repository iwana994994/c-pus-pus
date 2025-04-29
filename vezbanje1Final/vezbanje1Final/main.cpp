
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<fstream>

using namespace std;

class FlyingObject {
	protected:
		string name;
public:
	FlyingObject(string name):name(name) {}
	virtual void fly()const = 0;
	virtual ~FlyingObject() {}
	virtual string getFlightInfo() const = 0;
	string getName() const { return name; };
};


class Airplane : public FlyingObject {

public: Airplane(string name) :FlyingObject(name) {}
	  void fly() const override {
		  cout << "Avion [" << name << "] leti na visini od 10000m. " << endl;
	  }
	  string getFlightInfo() const override {
		  return "Avion [" + name + "] leti na visini od 10000m.\n";
	  }
};
class Helicopter : public FlyingObject {
public: Helicopter(string name) : FlyingObject(name) {}

	  void fly() const override {
		  cout << "Helikopter [" << name << "] leti na visini od 2000m. " << endl;
	  }
	  string getFlightInfo() const override {
		  return "Helikopter [" + name + "] leti na visini od 2000m.\n";
	  }

};


void prva3ObjektaSortiraj(vector<FlyingObject*>& o) {

	partial_sort(o.begin(), o.begin() + 3, o.end(),
		[](FlyingObject* a, FlyingObject* b) {
			return a->getName() < b->getName();
		});


}

void sortByName(vector<FlyingObject*>& o) {
	sort(o.begin(), o.end(), 
		[](FlyingObject* a, FlyingObject* b) {
			return a->getName() < b->getName();
				});

}
/*Pretraga objekata po imenu
•	Implementirajte funkciju koja omogu?ava pretragu lete?ih objekata po imenu koriste?i std::find_if i lambda funkciju.
•	Ako objekat postoji, ispišite poruku o objektu i pozovite njegovu metodu fly().
•	Ako objekat ne postoji, ispišite poruku da nije prona?en.
*/

void findByName(vector<FlyingObject*> &o, const string& targetName) {

	auto iterator = find_if(o.begin(),o.end(),
		[&](FlyingObject* obj) {
		
			return obj->getName() == targetName;

		});
	if (iterator != o.end())
	{
		(*iterator)->fly();
	}
	else {
		cout << "Ime nije pronadjeno " << endl;
	}

}
class Drone :public FlyingObject {
public: 
	Drone(string name) :FlyingObject(name) {}
	void fly() const override {
		cout << "Dron [" << name << "] leti na visini od 500m." << endl;
	
	}
	string getFlightInfo() const override {
		return "Dron [" + name + "] leti na visini od 500m.";
	}
};

void dronFirst(vector<FlyingObject*>& o) {

	partition (o.begin(),o.end(),
		[](FlyingObject* obj) {
			return dynamic_cast<Drone*>(obj) != nullptr;
		
		
		});
}
/* Zadatak: Prebrojati koliko ima Airplane  objekata u kolekciji. Koristiti std::count_if i lambda izraz koji koristi */

int numberOfAirplane(vector<FlyingObject*>& o) {

	int count = count_if(o.begin(),o.end(),
		[](FlyingObject* obj) {
			return dynamic_cast <Airplane*>(obj) != nullptr;
		});

	
	return count;

}



int main() {

	vector<FlyingObject*> objekti;
	objekti.push_back(new Airplane("A1"));
	objekti.push_back(new Airplane("O1"));
	objekti.push_back(new Airplane("Z1"));

	objekti.push_back(new Helicopter("H2"));
	objekti.push_back(new Helicopter("C2"));
	objekti.push_back(new Helicopter("L2"));



	


	cout << "-------------------------------------------"<<endl;
	for (auto o : objekti)
		o->fly();

	cout << "--------------- ISPIS IZ FAJLA ----------------------------" << endl;
	
	ofstream fout("data.txt", ios::out);
	if (!fout) {

		cout << " Nije moguce otvoriti data.txt" << endl;
		return 0;
	}
	for (auto o : objekti)
		fout << o->getFlightInfo() << endl;

	fout.close();

	ifstream fin("data.txt", ios::in);
	if (!fin)
	{
		cout << "Nije moguce otvoriti fajl" << endl;
		return 0;
	}
	string line;
	while (!fin.eof()) {
		getline(fin,line);
		if (line != "")
			cout << line << endl;
	}
	fin.close();

	cout << "------------- SORTIRANJE PRVA 3 ------------------------------" << endl;

	prva3ObjektaSortiraj(objekti);
	for (auto o : objekti)
		o->fly();

	cout << "--------------- SORTIRANJE PO IMENU ----------" << endl;
	sortByName(objekti);
	for (auto o : objekti)
		o->fly();
	cout << "---------------- PRETRAGA PO IMENU ---------------------------" << endl;

	findByName(objekti, "M3");

	cout << "----------------------- DODAVANJE DRONOVA --------------------" << endl;
	objekti.push_back(new Drone("M3"));

	sortByName(objekti);
	for (auto o : objekti)
		o->fly();


	cout << "---------------- DRONOVI PRVI ---------------------------" << endl;

	dronFirst(objekti);
	for (auto o : objekti)
		o->fly();

	cout << "----------------- Brroj aviona --------------------------" << endl;

	cout << "Broj aviona je " << numberOfAirplane(objekti) << endl;
	


	cout << "------------------ END -----------------------" << endl;
	for (auto o : objekti)
		delete o;
	return 0;
}

