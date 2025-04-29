

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<fstream>

using namespace std;

class Motor {
protected:
	string marka, model, sifraModela;
	double snagaMotora;
public:
	Motor(string marka, string model, string sifraModela, double snagaMotora=85.0):marka(marka),model(model),sifraModela(sifraModela),snagaMotora(snagaMotora) {}

	
	virtual void ispis() const {};
	virtual ~Motor(){}
	double getSnagaMorota()const { return snagaMotora; };
	virtual string getIspis() const = 0;
};


class Skuter : public Motor {
public:
	Skuter(string marka, string model, string sifraModela, double snagaMotora) :Motor(marka, model,sifraModela,snagaMotora) {}
	
	void ispis() const override{
		cout << "Motor " << marka << " | " << model << " | " << sifraModela << " | " << snagaMotora << endl;
	};
	string getIspis()const override {
		return "Motor " + marka + " | " + model + " | " + sifraModela + " | " +to_string(snagaMotora) +"";
	}
	
};
class Kros : public Motor {
public: Kros(string marka, string model, string sifraModela, double snagaMotora) :Motor(marka, model, sifraModela, snagaMotora) {}


	
	  void ispis() const override {
		  cout << "Kros " << marka << " | " << model << " | " << sifraModela << " | " << snagaMotora << endl;
	  };
	  string getIspis() const override{
		  return "Motor " + marka + " | " + model + " | " + sifraModela + " | " + to_string(snagaMotora) + "";
	  }
};

void sortByMotorPower(vector<Motor*> &m) {
	stable_sort(m.begin(), m.end(), 
		[](Motor* a,Motor* b) {

			return a->getSnagaMorota() < b->getSnagaMorota();
		});


}

int main() {
	vector<Motor*> motori;
	motori.push_back(new Skuter("Suzuki", "750z", "AA02", 750));
	motori.push_back(new Skuter("Suzuki2", "600z", "BB02", 650));
	motori.push_back(new Skuter("Suzuki3", "550z", "CC02", 550));
	cout << "------------ ISPIS ------------" << endl;
	for (auto m : motori)
		m->ispis();
	cout << "------------Sortiranje od manjeg ka vecem ------------" << endl;
	sortByMotorPower(motori);
		for (auto m : motori)
			m->ispis();
		cout << "---------- UPIS PODATKE U DATA.TXT--------------" << endl;
		ofstream fout("data.txt",ios::out);
		if (!fout) {
			cout << "Upis podataka u fajl nije moguc" << endl;
			return 0;
		}
		for (auto m : motori)
			fout<< m->getIspis()<<endl;
		fout.close();

		ifstream fin;
		fin.open("data.txt", ios::in);
		if (!fin)
		{
			cout << "Nije moguce otvoriti fajl" << endl;
			return 0;
		}
		while (!fin.eof()) {
			string line;
			getline(fin,line);
			if (line != "")
			{
				cout << line << endl;
			}
		}
		fin.close();
     


		cout << "--------- end --------------" << endl;

		for (auto m : motori)
			delete m;
	return 0;
}
