#pragma warning (disable:4996)
#include <iostream>
#include<string>
using namespace std;

//Aplicatie pentru genstionarea unor piese de teatru

class Eveniment
{
private:
	const int idEveniment;
	string teatru;
	int nrEvenimente;
	float* pretEveniment;
	Eveniment* evenimente;


public:
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
	Eveniment(const int idEveniment, string teatru, int nrEvenimente, float* pretEveniment): idEveniment(idEveniment)
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

	//operator >> de citire
	/*friend istream& operator>>(istream& in, Eveniment& e)
	{
		cout << "\nIntroduceti teatru: ";
		char teatru[100];
		in.getline(teatru, 100);
		e.teatru = teatru;
		cout << "Introduceti nr evenimente: ";
		in >> e.nrEvenimente;
		delete[] e.pretEveniment;
		if (e.pretEveniment > 0)
		{
			cout << "Introduceti pret eveniment: ";
			e.pretEveniment = new float[e.nrEvenimente];
			for (int i = 0; i < e.nrEvenimente; i++)
				in >> e.pretEveniment[i];
		}
		else
		{
			e.nrEvenimente = 0;
			e.pretEveniment = NULL;
		}

		return in;
	};*/
};

int main()
{
	std::cout << "Hello World!\n";
}






