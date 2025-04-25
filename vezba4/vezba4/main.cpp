/*•	U main funkciji kreirajte kolekciju objekata klase Shape (krugova i pravougaonika).*/

#include <iostream>
#include<vector>
#include<algorithm>
#include <string>

using namespace std;

class Shape {
protected:
	string color;
public:
	virtual double povrsina()const = 0;
	virtual double obim() const = 0;

	Shape(string color) :color(color) {}
	virtual ~Shape() {}

	virtual void Ispis()const = 0;

	string getColor() const { return color; }
};
class Circle : public Shape {
private: int radius;
public:
	Circle(int radius, string color) :Shape(color),radius(radius) {}
	double povrsina()  const override {
		return 2 * radius;
	}
	double obim() const override {
		return (radius * radius)*2;
	}

	void Ispis()const override {
	
		cout <<"Boja : "<<color<< ", Povrsina Kruga " << povrsina() << ", Obim kruga " << obim() << endl;
	
	}

};
class Rectangle : public Shape {
private: int width, height;
public: 
	Rectangle(int width,int height, string color):Shape(color), width(width), height(height){}
	double povrsina()  const override {
		return width * height;
	}
	double obim() const override {
		return 2 * (width + height);
	}


	void Ispis()const override {

		cout << "Boja : " << color << ",Povrsina Pravougaonika " << povrsina() << " Obim Pravougaonika " << obim() << endl;

	}

};

void sortPovrsina(vector<Shape*>& o) {
 
	sort(o.begin(), o.end(), 
		[](Shape* a,Shape* b) {
		
			return a->povrsina() < b->povrsina() ;
		});
}
void searchColor(vector<Shape*>& o, const string& colorName) {

	auto f = find_if(o.begin(), o.end(),
		[&](Shape* obj) {
			return obj->getColor() == colorName;
		});
	if (f != o.end())
	{
		(*f)->Ispis();
	}
	else {
	
		cout << "Boja ne postoji u ovim oblicima!" << endl;
	}
}
/*Zadatak 6: Pretraga objekta po površini
•	Na?ite prvi oblik u kolekciji koji ima površinu ve?u od 100. Koristite std::find_if i lambda izraz koji kombinuje dynamic_cast.
*/
void findPovrsina100(vector<Shape*>& o) {

	auto iterator =find_if(o.begin(), o.end(), //find_if ispisuje samo prvi veci od 100
		
	[](Shape* obj) {
		
			return obj->povrsina() >= 100;
		});
	if (iterator != o.end())
	{
		(*iterator)->Ispis();
	}
	else {
		cout << "Povrsina od 100 ne postoji u ovoj grupi oblika!" << endl;
	}
}
/*void findPovrsinaVecaOd(vector<Shape*>& o) {              // radi se bez find_if!!!!!
    bool found = false;

    for (Shape* obj : o) {
        if (obj->povrsina() >= 100) {
            obj->Ispis();                                
            found = true;
        }
    }

    if (!found) {
        cout << "Nema oblika sa povrsinom >= 100" << endl;
    }
}*/


int countRectangle(vector<Shape*>& o) {

	int number = count_if(o.begin(), o.end(),


		[](Shape* obj) {
			return dynamic_cast<Rectangle*>(obj) != nullptr;
		});
	return number;
}

class Triangle : public Shape {
private: int base, height;
public: 
	Triangle(int base,int height, string color):Shape(color),base(base),height(height){}

	double povrsina()const override {
		return 0.5 * base * height;
	}
	double obim()const override { return 0; }

	void Ispis()const override {

		cout << "Boja : " << color << ",Povrsina Trougla " << povrsina() << endl;

	}
};
class Square :public Shape {
private: int side;
public: Square(int side, string color):Shape(color),side(side) {}
	 
	  double povrsina()const override {
		  return side * side;
	  }
	  void Ispis() const override {
		  cout << "Boja : " << color << ",Povrsina Kvadrata " << povrsina() << endl;
	  
	  }
};

int main() {

	vector<Shape*> oblik;
	oblik.push_back(new Circle(2, "crvena"));
	oblik.push_back(new Circle(70, "plava"));

	oblik.push_back(new Rectangle(20, 30,"crna"));
	oblik.push_back(new Rectangle(50, 80,"roze"));

	for (auto o : oblik)
	{
		o->Ispis();
		
	}

	 
		cout << "------------- SORTIRANJE -------" << endl;

		sortPovrsina(oblik);
		
		for (auto o : oblik)
			o->Ispis();
		
		cout << "---------- PRETRAGA BOJE ----------" << endl;
		searchColor(oblik, "siva");
		searchColor(oblik, "roze");


		cout << "---------- DODAVANJE TROUGLA I KVADRATA ----------" << endl;
		oblik.push_back(new Triangle(7,8,"BELA"));
		oblik.push_back(new Triangle(10, 22, "BORDO"));

		for (auto o : oblik)
			o->Ispis();

		cout << "--------------------" << endl;
		int  number = countRectangle(oblik);

		cout << "Broj trougla je : " << number<<endl;

		cout << "---------- Povrsina od 100 ----------" << endl;

		findPovrsina100(oblik);
		


		cout << "---------- END ------------" << endl;
	for (auto o : oblik)
		delete o;
	return 0;
}