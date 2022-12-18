#pragma warning (disable:4996)
#include <iostream>
#include <string>
using namespace std;

class Locatie
{
private:
	const int idLocatie;
	char* oras;
	char* strada;
	Locatie* locatii;

public:
	//metode accesor pentru toate atributele
	char* getOras() {
		return this->oras;
	}

	char* getStrada() {
		return this->strada;
	}

	void setOras(const char* oras) {
		if (this->oras != NULL)
		{
			delete[]this->oras;
			this->oras = new char[strlen(oras) + 1];
			strcpy(this->oras, oras);
		}
	}

	void setStrada(char* strada) {
		if (this->strada != NULL)
		{
			delete[]this->strada;
			this->strada = new char[strlen(strada) + 1];
			strcpy(this->strada, strada);
		}
	}

	//constructor cu un parametru
	static int nrLocatii;
	Locatie() : idLocatie(nrLocatii) {
		this->oras = new char[strlen("Anonim") + 1];
		strcpy(this->oras, "Anonim");
		this->strada = new char[strlen("NECUNOSCUT") + 1];
		strcpy(this->strada, "NECUNOSCUT");
		nrLocatii++;
	}

	//constructor cu toti parametrii
	Locatie(int idLocatie, char* orasLocatie, char* stradaLocatie) :idLocatie(idLocatie) 
	{
		oras = new char[strlen(orasLocatie) + 1];
		strcpy(oras, orasLocatie);
		strada = new char[strlen(stradaLocatie) + 1];
		strcpy(strada, stradaLocatie);
		nrLocatii++;
	}

	//destructor
	~Locatie() {
		if (this->oras != NULL)
		{
			delete[]this->oras;
		}

		if (this->strada != NULL)
		{
			delete[]this->strada;
		}
	}

	//constructor de copiere
	Locatie(const Locatie& l) :idLocatie(l.idLocatie)
	{
		oras = new char[strlen(l.oras) + 1];
		strcpy(oras, l.oras);
		strada = new char[strlen(l.strada) + 1];
		strcpy(strada, l.strada);
		nrLocatii++;
	}

	//operator >=
	bool operator>=(const Locatie& l)
	{
		if (this->oras >= l.oras) 
			return true;
		else
		return false;
	}

	//operator []
	/*int& operator[](int index)
	{
		if (index >= 0 && index < this->nrLocatii)
		{
			return this->locatii[index];
		}
		else throw new exception("Index invalid!");
	}*/

	friend ostream& operator<<(ostream& out, const Locatie& l);
	friend istream& operator>>(istream& in, Locatie& l);

	//operator << de afisare
	friend ostream& operator<<(ostream& out, const Locatie& l) 
	{
		out << l.idLocatie << ", " << l.oras << ", " << l.strada << endl;
	}

	//operator >> de citire
	friend istream& operator>>(istream& in, Locatie& l) {
		if (l.oras != NULL)
		{
			delete[]l.oras;
		}
		cout << "Oras: ";
		char y[30];
		in >> y;
		in.getline(y, 30);
		l.oras = new char[strlen(y) + 1];
		strcpy(l.oras, y);

		if (l.strada != NULL)
		{
			delete[]l.strada;
		}
		cout << "Strada: ";
		char z[80];
		in >> z;
		in.getline(z, 80);
		l.strada = new char[strlen(z) + 1];
		strcpy(l.strada, z);
		return in;
	}
};

