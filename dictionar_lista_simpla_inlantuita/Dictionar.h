#pragma once


#define NULL_TVALOARE NULL
typedef int TCheie;
typedef int TValoare;

class IteratorDictionar;

#include <utility>
typedef std::pair<TCheie,TValoare> TElem;

struct Nod {
	// contine o cheie si o valoare
	TElem e;

	//referinta la urmatorul element din dictionar
	Nod* urm;
};

class Dictionar {
	friend class IteratorDictionar;

	private:		

		// referinta la primul element
		Nod* prim;

		// numarul de elemente in lista
		int n;

	public:

		// constructorul implicit al dictionarului
		Dictionar();

		// adauga o pereche (cheie, valoare) in dictionar	
		//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
		// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
		TValoare adauga(TCheie c, TValoare v);

		//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
		TValoare cauta(TCheie c) const;

		//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
		TValoare sterge(TCheie c);

		//returneaza numarul de perechi (cheie, valoare) din dictionar 
		int dim() const;

		//verifica daca dictionarul e vid 
		bool vid() const;

		// se returneaza iterator pe dictionar
		IteratorDictionar iterator() const;

		// functionalitate noua
		// adauga in dictionarul curent toate perechile din d a caror cheie nu se afla in dictionar
		// returneaza numarul de perechi adaugate
		int adaugaInexistente(Dictionar& d);


		// destructorul dictionarului	
		~Dictionar();

};


