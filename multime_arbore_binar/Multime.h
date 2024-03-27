#pragma once

using namespace std;

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

//in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorMultime;

// pointer la nod
//typedef Nod* PNod;

struct Nod {
public:

	TElem e;
	Nod* stanga;
	Nod* dreapta;

	Nod(TElem _e, Nod* _st, Nod* _dr) : e{ _e }, stanga{ _st }, dreapta{ _dr } {};
};

class Multime {	

private:

	// pointer la radacina
	Nod* radacina;	

	int nrElemente;

	friend class IteratorMultime;

	Nod* adauga_recursiv(Nod* rad, TElem elem, bool& adaugat);

	Nod* sterge_recursiv(Nod* rad, TElem elem, bool& sters);

	Nod* minim(Nod* rad);

	void distrug_recursiv(Nod* rad);

public:
		//constructorul implicit
		Multime();

		//adauga un element in multime
		//returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
		bool adauga(TElem e);

		//sterge un element din multime
		//returneaza adevarat daca elementul a existat si a fost sters
		bool sterge(TElem e);

		//verifica daca un element se afla in multime
		bool cauta(TElem elem) const;

		//intoarce numarul de elemente din multime;
		int dim() const;

		//verifica daca multimea e vida;
		bool vida() const;

		//returneaza un iterator pe multime
		IteratorMultime iterator() const;

		// functionalitate noua
		// adauga toate elementele din multimea B i multimea curenta
		void reuniune(const Multime& B);

		// destructorul multimii
		~Multime();

};

