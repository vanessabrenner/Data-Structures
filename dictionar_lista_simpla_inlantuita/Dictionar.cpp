#include "Dictionar.h"
#include <iostream>
#include "IteratorDictionar.h"

using namespace std;

//BC = AC = WC = θ(1)
Dictionar::Dictionar() {

	// neavand elemente in lista prim va indica o valoare NULL
	this->prim = NULL;

	// numarul de elemrnte va fi categoric 0
	this->n = 0;

}

//BC = AC = WC = θ(n)
Dictionar::~Dictionar() {
	Nod* nod = this->prim;
	while (nod != NULL) {
		Nod* dnod = nod;
		nod = nod->urm;
		delete dnod;
	}


}

//BC = AC = WC = θ(n)
TValoare Dictionar::adauga(TCheie c, TValoare v){
	
	// daca dictionarul nu e vid
	if (!vid()) {

		bool gasit = false;

		Nod* nod = this->prim;
		// cautam cheia
		while (nod != NULL) {			
			if (nod->e.first == c) {
				// in caz ca a fost gasit
				gasit = true;
				break;
			}			
			nod = nod->urm;
		}

		// daca cheia a fost gasita
		if (gasit) {
			TValoare oldv = nod->e.second;
			nod->e.second = v;
			return oldv;
		}		

		// daca nu exista cheia atunci vom adauga un nou element in dictionar
		if (!gasit) {
			Nod* nou = new Nod;
			nou->e.first = c;
			nou->e.second = v;
			nou->urm = this->prim;
			this->prim = nou;

			// setam numarul de elemente
			this->n++;
		}
	}
	else {
		// daca dictionarul e vid trebuie sa l adaugam
		Nod* nou = new Nod;
		nou->e.first = c;
		nou->e.second = v;
		//nou->urm = this->prim;
		nou->urm = NULL;
		this->prim = nou;

		// setam numarul de elemente
		this->n++;		
	}

	return NULL_TVALOARE;
}


//BC = AC = WC = θ(n)
//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare Dictionar::cauta(TCheie c) const{	

	//verificam daca nu e vid dictionarul
		Nod* nod = this->prim;
		// cautam cheia
		while (nod != NULL) {			
			if (nod->e.first == c) {
				// in caz ca a fost gasit				
				return nod->e.second;
			}			
			nod = nod->urm;
		}
	// in caz ca nu a fost gasita sau dictionarul e vid
	return NULL_TVALOARE;
}

// BC = θ(1)
// AC = WC = θ(n)
TValoare Dictionar::sterge(TCheie c){
	
	// verificam daca dictionarul nu e vid
	if (!vid()) {

		bool gasit = false;

		Nod* nod = this->prim;
		// cautam cheia
		while (nod != NULL) {		
			if (nod->e.first == c) {
				// in caz ca a fost gasit
				gasit = true;
				break;
			}			
			nod = nod->urm;
		}

		// daca cheia nu exista atunci nu avem ce sterge
		if (!gasit)
			return NULL_TVALOARE;
		else {
			Nod* nod1 = this->prim;
			
			// resetam numarul de elemente
			this->n--;

			// daca cheia se afla pe prima pozitie
			if (nod1->e.first == c) {
				this->prim = nod1->urm;
				return nod1->e.second;
			}
			else {
				Nod* nod2 = this->prim;
				nod1 = nod1->urm;

				while (nod1 != NULL) {
					if (nod1->e.first == c) {
						nod2->urm = nod1->urm;
						return nod1->e.second;
					}					
					nod1 = nod1->urm;
					nod2 = nod2->urm;
					
				}		
			}			
		}
	}
	// daca e dictionarul e vid nu avem ce sterge
	return NULL_TVALOARE;
}

// BC = AC = WC = θ(n*m) unde n si m sunt numarul de elemente a celor doua dictionare
int Dictionar::adaugaInexistente(Dictionar& d) {

	// o variabila ce va retine numarul de chei adaugate
	int nr = 0;

	// luam primul element din dictionarul dat
	Nod* dnod = d.prim;

	while (dnod != NULL) {
		
		// cautam cheia din d in dictionarul nostru
		TCheie dc = dnod->e.first;
		TValoare dv = dnod->e.second;

		// luam primul element din dictionar si ii comparam cheia
		Nod* nod = this->prim;
	
		// o variabila booleana pentru a semnala aparitia unei chei
		bool gasit = false;

		while (nod != NULL) {
			if (nod->e.first == dc) {
				// in caz ca a fost gasit
				gasit = true;
				break;
			}
			nod = nod->urm;
		}

		// daca nu gasim cheia o adaugam
		if (!gasit) {
			adauga(dc, dv);
			nr++;
		}

		// mergem la urmatorul element din dictionarul dat
		dnod = dnod->urm;
	}
	
	return nr;
}

//BC = AC = WC = θ(1)
int Dictionar::dim() const {

	return this->n;
}

//BC = AC = WC = θ(1)
bool Dictionar::vid() const{
	if (this->n == 0)
		return true;
	return false;
}

//BC = AC = WC = θ(n)
IteratorDictionar Dictionar::iterator() const {
	return  IteratorDictionar(*this);
}


