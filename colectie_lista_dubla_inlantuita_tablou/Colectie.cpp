#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>

using namespace std;

bool rel(TElem e1, TElem e2) {
	if (e1 <= e2)
		return true;
	return false;
}

// ................................

//BC = AC = WC = θ(n)
void Colectie::redim() {
	int newCapacity = cp * 2;
	TElem* newE = new TElem[newCapacity];
	int* newUrm = new int[newCapacity];
	int* newPrec = new int[newCapacity];

	// copiem vectorul de elemente in cel nou
	for (int i = 0; i < n; i++)
		newE[i] = e[i];
	delete[] e;
	e = newE;

	// copiem vectorul de legaturi inainte in cel nou
	for (int i = 0; i < n; i++)
		newUrm[i] = urm[i];	
	delete[] urm;
	urm = newUrm;

	// copiem vectorul de legaturi inapoi in cel nou
	for (int i = 0; i < n; i++)
		newPrec[i] = prec[i];
	delete[] prec;
	prec = newPrec;

	// modificam noua capacitate
	cp = newCapacity;

	// refacem legaturile
	initSpatiuLiber();

	primLiber = n;
}

//BC = AC = WC = θ(1)
// returneaza pozitia unui spatiu liber in lista
int Colectie::aloca() {
	int i = primLiber;
	primLiber = urm[primLiber];
	return i;
}

//BC = AC = WC = θ(1)
// dealoca un spatiu ce are indicele i
void Colectie::dealoca(int i) {
	urm[i] = primLiber;
	primLiber = i;
}

//BC = AC = WC = θ(cp - n)
void Colectie::initSpatiuLiber() {	

	// punem pozitiile in locul potrivit
	for (int i = n; i < cp - 1; i++) {
		urm[i] = i + 1;
		prec[i] = i - 1;
	}

	// pozitia urmatoare dupa ultimul element va fi -1 (nimic)
	urm[cp - 1] = -1;
}

// ...............................

//BC = AC = WC = θ(cp)
Colectie::Colectie() {
	// alocam spatiu
	prec = new int[cp];
	urm = new int[cp];
	e = new TElem[cp];
	// setam numarul de elemente cu 0
	n = 0;
	// lista e vida
	prim = -1;
	ultim = -1;	
	// se initializeaza spatiul liber
	initSpatiuLiber();
	// primul spatiu liber va fi 0
	primLiber = 0;
}

// BC = θ(1)
// AC = WC = θ(n)
void Colectie::adauga(TElem e) {

	// daca lista e nu e vida
	if (!vida()) {
		// redimensionam daca vectorul este plin
		if (n == cp)
			redim();
		// daca elementul de adaugat trebuie sa fie pe prima pozitie
		if (rel(e, this->e[prim])) {
			// sigur vom avea un loc
			int poz = aloca();			
			this->e[poz] = e;
			// refacem legaturile
			prec[poz] = -1;
			urm[poz] = prim;
			prec[prim] = poz;
			prim = poz;

			// crestem numarul de elemente
			n++;
		}
		// daca elementul de adaugat trebuie sa fie pe ultima pozitie
		else if (rel(this->e[ultim], e)) {
			// sigur vom avea un loc
			int poz = aloca();
			this->e[poz] = e;
			// refacem legaturile
			urm[poz] = -1;
			prec[poz] = ultim;
			urm[ultim] = poz;
			ultim = poz;

			// crestem numarul de elemente
			n++;
		}
		else {
			// trebuie pus undeva in mijlocul listei
			int i = urm[prim];
			while (rel(this->e[i], e)) {
				i = urm[i];
			}
			// l am gasit			
			int poz = aloca();
			// sigur vom avea loc
			this->e[poz] = e;
			// refacem legaturile
			prec[poz] = prec[i];
			urm[prec[i]] = poz;
			prec[i] = poz;
			urm[poz] = i;

			// crestem numarul de elemente
			n++;
		}
	}
	else {
		int poz = aloca();
		this->e[poz] = e;
		// facem legaturile pentru un prim element adaugat in lista goala
		urm[poz] = -1;
		prec[poz] = -1;
		ultim = poz;
		prim = poz;
		
		// crestem numarul de elemente
		n++;

	}		
}

// BC = θ(1)
// AC = WC = θ(n)
bool Colectie::sterge(TElem e) {
	if (vida())
		return false;

	// fiind o colectie ordonata putem afla usor prin rel daca e
	// ar putea exista in lista
	if (!rel(this->e[prim], e) || !rel(e, this->e[ultim]))
		return false;

	// daca este chiar primul element
	if (this->e[prim] == e) {
		int newprim = urm[prim];
		dealoca(prim);
		prim = newprim;
		// micsoram numarul de elemente
		n--;
		return true;
	}

	// daca este chiar ultimul element
	if (this->e[ultim] == e) {
		int newultim = prec[ultim];
		dealoca(ultim);
		ultim = newultim;
		// micsoram numarul de elemente
		n--;
		return true;
	}
	
	// elementul de afla poate intre prim si ultim
	int i = urm[prim];
	while (this->e[i] != e && urm[i] != -1) {
		i = urm[i];
	}
	if (this->e[i] == e) {
		// l am gasit
		urm[prec[i]] = urm[i];
		prec[urm[i]] = prec[i];
		dealoca(i);
		// micsoram numarul de elemente
		n--;
		return true;
	}

	return false;
}

// BC = θ(n)
// AC = WC = θ(n)
bool Colectie::cauta(TElem elem) const {
	if (vida())
		return false;

	// fiind o colectie ordonata putem afla usor prin rel daca e
	// ar putea exista in lista
	if (!rel(this->e[prim], elem) || !rel(elem, this->e[ultim]))
		return false;

	// daca este chiar primul element
	if (this->e[prim] == elem) {
		return true;
	}

	// daca este chiar ultimul element
	if (this->e[ultim] == elem) {
		return true;
	}

	// elementul de afla poate intre prim si ultim
	int i = urm[prim];
	while (this->e[i] != elem && urm[i] != -1) {
		i = urm[i];
	}
	if (this->e[i] == elem) {
		// l am gasit
		return true;		
	}

	return false;
}

//BC = AC = WC = θ(n)
int Colectie::nrAparitii(TElem elem) const {
	if (vida())
		return 0;

	// fiind o colectie ordonata putem afla usor prin rel daca e
	// ar putea exista in lista
	if (!rel(this->e[prim], elem) || !rel(elem, this->e[ultim])) {		
		return 0;
	}

	// il cautam	
	int nrAparitii = 0;	
	for (int i = prim; i != -1; i = urm[i]) {
		if (this->e[i] == elem)
			nrAparitii++;
	}	

	return nrAparitii;
}

// BC = θ(1)
// AC = WC = θ(n)
int Colectie::eliminaToateAparitiile(TElem elem) {

	if (vida())
		return 0;

	// fiind o colectie ordonata putem afla usor prin rel daca e
	// ar putea exista in lista
	if (!rel(this->e[prim], elem) || !rel(elem, this->e[ultim])) {		
		return 0;
	}

	int nrEliminari = nrAparitii(elem);

	for (int i = 1; i <= nrEliminari; i++) {
		sterge(elem);
	}

	return nrEliminari;
}


//BC = AC = WC = θ(1)
int Colectie::dim() const {
	return n;
}


//BC = AC = WC = θ(1)
bool Colectie::vida() const {
	if (n == 0)
		return true;
	return false;
}


//BC = AC = WC = θ(1)
IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


//BC = AC = WC = θ(1)
Colectie::~Colectie() {
	delete[] e;
	delete[] urm;
	delete[] prec;
}
