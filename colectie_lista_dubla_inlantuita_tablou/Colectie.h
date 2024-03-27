#pragma once

#define CAPACITATE 100

typedef int TElem;

typedef bool(*Relatie)(TElem, TElem);

// in implementarea operatiilor se va folosi functia (relatia) rel (de ex, pentru <=)
// va fi declarata in .h si implementata in .cpp ca functie externa colectiei
bool rel(TElem, TElem);

class IteratorColectie;

class Colectie {

	friend class IteratorColectie;

private:

	// capacitatea initiala a vectorilor
	int cp = CAPACITATE;

	// numarul de elemente in lista
	int n;

	// vectorul de elemente (dinamic)
	TElem* e;

	// vectorul pentru legaturi inainte
	int* urm;

	// vectorul pentru legaturi inapoi
	int* prec;

	// referinta la primul element din lista de elemente
	int prim;

	// referinta la ultimul element din lista
	int ultim;

	// referinta la primul element din lista de legaturi
	int primLiber;

	// functie privata pentru redimensionare
	void redim();

	// pentru alocare, dealocare, initializare spatiu liber

	int aloca();

	void dealoca(int i);

	void initSpatiuLiber();

public:
		//constructorul implicit
		Colectie();

		//adauga un element in colectie
		void adauga(TElem e);

		//sterge o aparitie a unui element din colectie
		//returneaza adevarat daca s-a putut sterge
		bool sterge(TElem e);

		//verifica daca un element se afla in colectie
		bool cauta(TElem elem) const;

		//returneaza numar de aparitii ale unui element in colectie
		int nrAparitii(TElem elem) const;

		//intoarce numarul de elemente din colectie;
		int dim() const;

		//verifica daca colectia e vida;
		bool vida() const;

		//returneaza un iterator pe colectie
		IteratorColectie iterator() const;

		// functionalitate noua
		// elimina toate aparitiile elementului elem din colectie
		// returneaza numarul de elemente eliminate
		int eliminaToateAparitiile(TElem elem);

		// destructorul colectiei
		~Colectie();


};

