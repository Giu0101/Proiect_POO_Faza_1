#pragma warning (disable:4996)
#include <iostream>
#include <string>
using namespace std;

class Spectator
{
private:
	const int idSpectator;
	char* nume;
	int varsta;
	float medie;
	Spectator* spectatori;

public:
	//metode accesor pentru toate atributele
	const int getIdSpectator() {
		return this->idSpectator;
	}

	char* getNume() {
		return this->nume;
	}

	int getVarsta() {
		return this->varsta;
	}

	void setNume(char* nume) {
		if (this->nume != NULL)
		{
			delete[]this->nume;
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}

	}

	void setVarsta(int varsta) {
		if (varsta > 0)
		{
			this->varsta = varsta;
		}
		else {
			this->varsta = 0;
		}
	}

	//constructor cu un parametru
	static int nrSpectatori;
	Spectator() :idSpectator()
	{
		this->nume = new char[strlen("Anonim" + 1)];
		strcpy(this->nume, "Anonim");
		this->varsta = 0;
		nrSpectatori++;
	}

	//constructor cu toti parametrii
	Spectator(const int idSpectator, char* numeSpectator, int varstaSpectator, float medie) : idSpectator(idSpectator)
	{
		nume = new char[strlen(numeSpectator) + 1];
		strcpy(nume, numeSpectator);
		varsta = varstaSpectator;
		if (medie > 0)this->medie = medie;
		else this->medie = 0;
		nrSpectatori++;
	}

	//destructor
	~Spectator()
	{
		if (this->nume != NULL)
		{
			delete[]this->nume;
		}
	}
	
	//constructor de copiere
	Spectator(const Spectator& s) : idSpectator(s.idSpectator)
	{
		nume = new char[strlen(s.nume) + 1];
		strcpy(nume, s.nume);
		varsta = s.varsta;
		if (medie > 0)this->medie = s.medie;
		else this->medie = 0;
		nrSpectatori++;

	}

	//operator ==
	bool operator==(const Spectator& s)
	{
		if (this->nrSpectatori == s.nrSpectatori)
			return true;
		else

		return false;
	}

	//operator ()
	float operator()(int varsta)
	{
		if (varsta > 0)
			return this->medie;
		else throw new exception("Media nu a putut fi calculata!");
	}

	explicit operator double()
	{
		return this->medie;
	}

	friend ostream& operator<<(ostream& out, const Spectator& s);
	friend istream& operator>>(istream& in, Spectator& s);

	//operator << de afisare
	friend ostream& operator<<(ostream& out, const Spectator& c) {
		out << c.idSpectator << ", " << c.nume << " , " << c.varsta << endl;
		return out;
	}

	//operator >> de afisare
	friend istream& operator>>(istream& in, Spectator& s) {
		if (s.nume != NULL)
		{
			delete[]s.nume;
		}
		cout << "Nume: ";
		char n[20];
		in >> n;
		in.getline(n, 20);
		s.nume = new char[strlen(n) + 1];
		strcpy(s.nume, n);

		cout << "Varsta: ";
		in >> s.varsta;
		return in;
	}
};

