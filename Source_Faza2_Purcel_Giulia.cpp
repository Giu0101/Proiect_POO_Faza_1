#pragma warning (disable:4996)
#include <iostream>
#include<fstream>
#include<string>
using namespace std;

//Aplicatie pentru genstionarea unor piese de teatru

class Eveniment
{
private:
	string teatru;
	const int idEveniment;
	int bilet;
	int nrEvenimente;
	int* evenimente;
	float* pretEveniment;


public:
	virtual double incasariEveniment() = 0;
	virtual double pret() = 0;

	//metode accesor pentru toate atributele

	string getTeatru() {
		return this->teatru;
	}

	int getNrEvenimente() {
		return this->nrEvenimente;
	}

	float* getPretEveniment() {
		return this->pretEveniment;
	}

	void setTeatru(string teatru) {
		if (teatru.length() > 5)
			this->teatru = teatru;
	}

	void setNrEvenimente(int nrEvenimente) {
		if (nrEvenimente > 0)
			this->nrEvenimente = nrEvenimente;
	}

	//constructor cu un parametru
	Eveniment() : idEveniment()
	{
		this->teatru = nullptr;
		this->nrEvenimente = 0;
		this->pretEveniment = nullptr;
	}

	//constructor cu toti parametrii
	Eveniment(const int idEveniment, string teatru, int nrEvenimente, float* pretEveniment) : idEveniment(idEveniment)
	{
		this->teatru = teatru;
		if (nrEvenimente > 0 && pretEveniment != NULL) {
			this->nrEvenimente = nrEvenimente;
			this->pretEveniment = new float[this->nrEvenimente];
			for (int i = 0; i < this->nrEvenimente; i++)
				this->pretEveniment[i] = pretEveniment[i];
		}
		else {
			this->nrEvenimente = 0;
			this->pretEveniment = NULL;
		}
	}

	//destructor
	~Eveniment() {
		if (this->pretEveniment != nullptr)
			delete[] this->pretEveniment;
	}

	//constructor de copiere
	Eveniment(const Eveniment& e) :idEveniment(e.idEveniment)
	{
		this->teatru = e.teatru;
		if (nrEvenimente > 0 && pretEveniment != NULL) {
			this->nrEvenimente = e.nrEvenimente;
			this->pretEveniment = new float[this->nrEvenimente];
			for (int i = 0; i < this->nrEvenimente; i++)
				this->pretEveniment[i] = e.pretEveniment[i];
		}
		else {
			this->nrEvenimente = 0;
			this->pretEveniment = NULL;
		}

	}

	//operator = 
	Eveniment& operator=(const Eveniment& e)
	{
		delete[] this->pretEveniment;
		this->teatru = e.teatru;
		if (nrEvenimente > 0 && pretEveniment != NULL) {
			this->nrEvenimente = e.nrEvenimente;
			this->pretEveniment = new float[this->nrEvenimente];
			for (int i = 0; i < this->nrEvenimente; i++)
				this->pretEveniment[i] = e.pretEveniment[i];
		}
		else {
			this->nrEvenimente = 0;
			this->pretEveniment = NULL;
		}
		return *this;
	}

	//operator comparatie Eveniment < float
	bool operator<(float x)
	{
		if (nrEvenimente > 0 && pretEveniment != NULL) {
			float max = this->pretEveniment[0];
			for (int i = 0; i < this->nrEvenimente; i++)
				if (this->pretEveniment[i] > max)
					max = this->pretEveniment[i];
			if (max < x)
				return true;
			else
				return false;
		}
		else
			throw exception("Nu exista evenimente de comparat");

	}

	friend ostream& operator<<(ostream& out, const Eveniment& e);
	friend istream& operator>>(istream& in, Eveniment& e);

	//operator << de afisare
	friend ostream& operator<<(ostream& out, const Eveniment& e)
	{
		out << "\n----------------------";
		out << "\nId eveniment:" << e.idEveniment;
		out << "\nTeatru:" << e.teatru;
		if (e.nrEvenimente > 0 && e.pretEveniment != NULL)
		{
			out << "\nNumar evenimente:" << e.nrEvenimente;
			out << "\nPret eveniment:";
			for (int i = 0; i < e.nrEvenimente; i++)
				out << e.pretEveniment[i] << " ";
		}
		else
		{
			out << "\nNu exista evenimente!";
		}
		return out;
	}

	friend istream& operator>>(istream& in, Eveniment& e)
	{
		cout << "\nTeatru: ";
		in >> e.teatru;
		return in;
	}

	/*float calculPretEveniment() {
		float sum = 0;

		for (int i = 0; i < this->nrEvenimente; i++) {
			sum += this->evenimente[i]->pret();

			return sum;
		}
	}*/

	void serializare(ofstream& f) {
		//scriu teatrul
		int lungimeCuTerminator = this->teatru.size() + 1;
		f.write((char*)&lungimeCuTerminator, sizeof(int));
		
		f.write((char*)this->teatru.c_str(), lungimeCuTerminator);

		//scriu id-ul evenimentului
		f.write((char*)&this->idEveniment, sizeof(int));

		//scriu biletele
		f.write((char*)&this->bilet, sizeof(int));

		//scriu numarul evenimentelor
		f.write((char*)&this->nrEvenimente, sizeof(int));

		//scriu pretul evenimentului
		f.write((char*)&this->pretEveniment, sizeof(float));
	}

	void deserializare(ifstream& f) {
		//citesc teatrul
		int lungimeCuTerminator;

		f.read((char*)&lungimeCuTerminator, sizeof(int));
		char bufferTeatru[100];
		f.read(bufferTeatru, lungimeCuTerminator);

		this->teatru = (string)bufferTeatru;

		//citesc id-ul evenimentului
		f.read((char*)&this->idEveniment, sizeof(int));

		//citesc id-ul evenimentului
		f.read((char*)&this->bilet, sizeof(int));

		//citesc numarul de evenimente
		f.read((char*)&this->nrEvenimente, sizeof(int));

		this->evenimente = new int[this->nrEvenimente];

		//citesc evenimentul
		f.read((char*)this->evenimente, sizeof(int) * this->nrEvenimente);

		//citesc pretul evenimentului
		f.read((char*)&this->pretEveniment, sizeof(float));


	}
		
};

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

class Spectator
{
private:
	const int idSpectator;
	char* nume;
	int varsta;
	float medie;
	Spectator* spectatori;

public:
	virtual void apartineCategoriei() = 0;

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

//clasa creata prin derivarea clasei Spectator
class Adolescent : public Spectator {
public:
	int categorieVarsta;

	void apartineCategoriei() override
	{
		cout << "Spectatorul are varsta intre 18-27 de ani" << endl;
	}
};

////clasa abstracta cu o metoda virtuala pura
//class Incasari : public Eveniment {
//public:
//	double incasariEveniment() {
//		return nrEvenimente * pretEveniment;
//	}
//private:
//	int nrEvenimente;
//	float* pretEveniment;
//};

template<typename T>
void comuta(T& a, T& b)
{
	T aux;
	aux = a;
	a = b;
	b = aux;
}

int main() {
	/*int evenimente[3] = { 10, 8, 9 };

	Eveniment e( "I.L.Caragiale", 5, 50);
	Eveniment even;*/
	/*
	Spectator* spectatori[2];
	Adolescent a;
	spectatori[0] = &a;
	for (int i = 0; i < 2; i++) {
		spectatori[1]->apartineCategoriei();
	}
	return 0;*/


}

