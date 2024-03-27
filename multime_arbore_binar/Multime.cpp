#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

//using namespace std;

//o posibila relatie
bool rel(TElem e1, TElem e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

// θ(1) 
Multime::Multime() {
	this->radacina = nullptr;	
	this->nrElemente = 0;
}

// BC = O(1)
// AC = O(h)
// WC = O(h) 
// h inaltimea arborelui
Nod* Multime::adauga_recursiv(Nod* rad, TElem elem, bool& adaugat) {

	if (rad == nullptr) {
		// alocam spatiu pentru noul nod
		rad = new Nod(elem, nullptr, nullptr);		
		// semnalam adaugarea cu succes a noului nod
		adaugat = true;			
	}
	// daca am gasit un nod cu aceeasi cheie
	// nu mai adaugam alt nod (este o multime)
	else if (elem == rad->e) {
		adaugat = false;
	}
	else if (rel(elem, rad->e)) {
		rad->stanga = adauga_recursiv(rad->stanga, elem, adaugat);
	}
	else {
		rad->dreapta = adauga_recursiv(rad->dreapta, elem, adaugat);
	}

	return rad;

}

// BC = O(1)
// AC = O(h)
// WC = O(h) 
// h inaltimea arborelui
bool Multime::adauga(TElem elem) {

	// o variabila booleana pentru a semnala 
	// adaugarea cu succes sau nu a unui element
	bool adaugat = false;

	// apelam functia recrusiva
	this->radacina = adauga_recursiv(this->radacina, elem, adaugat);

	// daca l am adaugat cu succes
	if(adaugat)
		// crestem numarul de elemente
		this->nrElemente++;

	return adaugat;

	/*Nod* cnod = this->radacina;
	Nod* parinte = nullptr;

	while (cnod != nullptr) {
		parinte = cnod;
		if (elem == cnod->e)
			return false;
		else if (rel(elem, cnod->e)) {
			cnod = cnod->stanga;
		}
		else {
			cnod = cnod->dreapta;
		}
	}

	Nod* newNod = new Nod(elem, nullptr, nullptr);
	if (this->radacina == nullptr)
		this->radacina = newNod;
	else if (rel(elem, parinte->e))
		parinte->stanga = newNod;
	else
		parinte->dreapta = newNod;
	this->nrElemente++;
	return true;*/

}

// BC = O(1)
// AC = O(h)
// WC = O(h) 
// h inaltimea arborelui
Nod* Multime::minim(Nod* rad) {
	while (rad->stanga != nullptr) {
		rad = rad->stanga;
	}
	return rad;
}

// BC = O(1)
// AC = O(h)
// WC = O(h) 
// h inaltimea arborelui
Nod* Multime::sterge_recursiv(Nod* rad, TElem elem, bool& sters) {

	if (rad == nullptr) {
		return rad;
	}
	else if (rel(elem, rad->e) && rad->e != elem) {
		rad->stanga = sterge_recursiv(rad->stanga, elem, sters);
		return rad;
	}
	else if (!(rel(elem, rad->e)) && rad->e != elem) {
		rad->dreapta = sterge_recursiv(rad->dreapta, elem, sters);
		return rad;
	}
	// l am gasit	
	else if (rad->stanga != nullptr && rad->dreapta != nullptr) {
		// suntem cazul in care nodul are subarbore stang si drept

		// determinam minimul din subarborele drept al nodului de sters
		Nod* temp = minim(rad->dreapta);

		// se muta cheia in nodul de sters
		rad->e = temp->e;

		// stergem minimul
		bool nimic = false;
		rad->dreapta = sterge_recursiv(rad->dreapta, temp->e, nimic);

		// semnalam stergerea elementului
		sters = true;

		return rad;
	}
	else {
		Nod* temp = rad;
		Nod* newrad = nullptr;

		// nu exista subarbore stang
		if (temp->stanga == nullptr) {
			newrad = temp->dreapta;
		}
		// nu exista subarbore drept
		else {
			newrad = temp->stanga;
		}

		// semnalam stergerea elementului
		sters = true;

		// dealocam nodul de sters
		delete temp;

		return newrad;
	}
}

// BC = O(1)
// AC = O(h)
// WC = O(h) 
// h inaltimea arborelui
bool Multime::sterge(TElem elem) {

	// o variabila booleana pentru a semnala 
	// stergerea cu succes sau nu a unui element
	bool sters = false;

	// apelam functia recrusiva
	this->radacina = sterge_recursiv(this->radacina, elem, sters);

	// daca a fost sters cu succes
	if (sters)
		// micsoram numarul de elemente
		this->nrElemente--;

	return sters;
}

// BC = O(1)
// AC = O(h)
// WC = O(h) 
// h inaltimea arborelui
bool Multime::cauta(TElem elem) const {
	// varianta iterativa

	if (vida())
		return false;
	
	Nod* rad = this->radacina;
	// cautam elementul
	while (rad != nullptr && rad->e != elem) {
		if (rel(elem, rad->e))
			rad = rad->stanga;
		else
			rad = rad->dreapta;
	}

	// daca nu exista
	if (rad == nullptr)
		return false;
	
	return true;

}

// functionalitate noua
// O(m*n)
void Multime::reuniune(const Multime& B) {

	IteratorMultime it = IteratorMultime(B);
	it.prim();

	while (it.valid()) {

		this->adauga(it.element());
		it.urmator();		
	}
}

// θ(1)
int Multime::dim() const {

	return this->nrElemente;
}


// θ(1)
bool Multime::vida() const {

	if (this->nrElemente == 0)
		return true;

	return false;
}

IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

// θ(n)
void Multime::distrug_recursiv(Nod* rad) {
	if (rad != nullptr) {
		distrug_recursiv(rad->stanga);
		distrug_recursiv(rad->dreapta);
		delete rad;
	}
}

Multime::~Multime() {
	distrug_recursiv(this->radacina);
}

