#include "Matrice.h"

#include <iostream>
#include <exception>
#include <math.h>

using namespace std;

// ...............................

// BC = AC = WC = θ(cp)
void Matrice:: actPrimLiber() {

	this->PrimLiber++;

	while (PrimLiber < cp && e[PrimLiber].cheie != NULL_TELEMENT) {
		PrimLiber++;
	}
}

// BC = AC = WC = θ(1)
int Matrice:: d(TElem e) {

	// elementul poate fi < 0 si nu este pozitie valida 
	return abs(e) % cp;
}

// BC = AC = WC = θ(cp)
void Matrice:: initSpatiuLiber() {

	// alocam spatiu
	this->e = new Triplet[cp];
	this->urm = new int[cp];

	for (int i = 0; i < cp; i++) {
		e[i].linie = -1;
		e[i].coloana = -1;
		e[i].cheie = NULL_TELEMENT;

		urm[i] = -1;
	}	

	// setam PrimLiber cu primul loc liber din vectorul urm
	this->PrimLiber = 0;
}

// ..................................

// BC = O(1)
// AC = WC = O(cp)
Matrice::Matrice(int m, int n) {

	// aruncam exceptie
	if (m <= 0 || n <= 0)
		throw std::exception();

	// setam capacitatea (intotdeauna o matrice va avea n * m elemente)
	this->cp = m * n;

	// setam numarul de linii si coloane
	this->nrL = m;
	this->nrC = n;

	// initalizam spatiul liber
	initSpatiuLiber();
}


// BC = AC = WC = θ(1)
int Matrice::nrLinii() const{

	return nrL;
}


// BC = AC = WC = θ(1)
int Matrice::nrColoane() const{

	return nrC;
}


// BC = O(1)
// AC = WC = O(cp)
TElem Matrice::element(int i, int j) const{

	// aruncam exceptie
	if (i < 0 || j < 0 || i >= this->nrL || j >= this->nrC)
		throw std::exception();

	// parcurgem vectorul e pentru a gasi cheia
	for (int k = 0; k < this->cp; k++)
		if (this->e[k].linie == i && this->e[k].coloana == j) {
			return e[k].cheie;
		}

	// nu a fost gasit tripletul (i, j, c)
	return NULL_TELEMENT;
}


//	BC = AC = WC = O(cp)
void Matrice::sterge(int i, int j, TElem e) {

	int curent = d(e);
	int anterior = -1;

	// cautam cheia care sigurat exista
	while (this->e[curent].cheie != e && this->e[curent].linie != i && this->e[curent].coloana != j) {
		anterior = curent;
		curent = this->urm[curent];
	}

	bool gata = false;

	// readucem elementele pe pozitia corecta
	do {
		int p = this->urm[curent];
		int pp = curent;

		while (p != -1 && d(this->e[curent].cheie) != curent) {
			pp = p;
			p = this->urm[p];

			if (p == -1)
				gata = true;
			else {
				this->e[curent] = this->e[p];
				curent = p;
				anterior = pp;
			}
		}
	} while (gata);

	// din cauza acestui if avem complexitate medie O(cp) -- cp = capacitate
	if (anterior == -1) {
		int k = 0;
		
		while (k < this->cp && this->urm[k] != anterior) {
			k++;
		}

		if (k < cp) {
			anterior = k;
		}
	}

	if (anterior != -1) {
		this->urm[anterior] = this->urm[curent];
	}

	// eliminam vechiul element
	this->e[curent].linie = -1;
	this->e[curent].coloana = -1;
	this->e[curent].cheie = NULL_TELEMENT;
	this->urm[curent] = -1;

	// setam PrimLiber
	if (i < this->PrimLiber) {
		this->PrimLiber = i;
	}	
}


// BC = O(1)
// AC = WC = O(cp)
TElem Matrice::modifica(int i, int j, TElem e) {

	// ! modificarea unui vechi element este acelasi lucru ca stergerea acestuia

	// aruncam exceptie
	if (i < 0 || j < 0 || i >= this->nrL || j >= this->nrC)
		throw std::exception();

	// valoarea de dispersie
	int disp = d(e);

	// nu exista tripletul (i, j, cheie)
	if (element(i, j) == NULL_TELEMENT) {		
		// daca e e NULL_TELEMENT nu avem ce sa modificam
		if (e != NULL_TELEMENT) {
			// daca prima pozitie e libera
			if (this->e[disp].cheie == NULL_TELEMENT) {
				
				this->e[disp].linie = i;
				this->e[disp].coloana = j;
				this->e[disp].cheie = e;

				this->urm[disp] = -1;	

				if (disp == PrimLiber)
					actPrimLiber();
			}
			else {
				// parcurgem lista		
				int curent = disp;

				while (this->urm[curent] != -1) {
					curent = this->urm[curent];
				}

				// daca terminam while-ul inseamna ca am ajuns la ultimul element din lista
				// alocam spatiu pentru noul element

				this->e[PrimLiber].linie = i;
				this->e[PrimLiber].coloana = j;
				this->e[PrimLiber].cheie = e;

				this->urm[PrimLiber] = -1;

				// refacem legaturile
				this->urm[curent] = this->PrimLiber;
				actPrimLiber();
			}
		}		

		return NULL_TELEMENT;
	}
	// daca noul element este acelasi ca vechiul element 
	else if (element(i, j) == e) {

		//cout << "**" << i << ' ' << j << ' ' << element(i, j) << endl;
		// nu avem ce sa modificam
		return e;
	}
	// daca dispersia vechii chei este aceeasi ca cea noua, doar il modificam
	else if (d(element(i, j)) == disp && e != NULL_TELEMENT){
		
		//cout << "***" << i << ' ' << j << ' ' << element(i, j) << endl;

		//retinem vechea valoare
		TElem oldValue = element(i, j);		

		// cautam vechiul triplet
		int curent = disp;

		while (this->urm[curent] != -1 || (this->e[curent].linie == i && this->e[curent].coloana == j)) {
			curent = this->urm[curent];
		}

		// il modificam
		this->e[curent].cheie = e;

		//cout << "***" << i << ' ' << j << ' ' << element(i, j) << endl;

		return oldValue;

	}
	// daca tripletul (i, j, cheie) exista, are dispersie diferita si trebuie modificat
	else {		
		//retinem vechea valoare
		TElem oldValue = element(i, j);

		// stergem tripletul vechi (i, j, cheie)		
		sterge(i, j, oldValue);

		// adaugam tripletul nou (i, j, e)
		// la fel ca primul if -> element(i, j) va fi NULL_TELEMENT
		// ! daca vrem sa modificam vechea cheie cu NULL_TELEMENT
		//   inseamna ca vrem intr un fel sa o stergem deci nu mai facem modificari				
		if (e != NULL_TELEMENT) {
			// parcurgem lista		
			int curent = disp;

			while (this->urm[curent] != -1) {
				curent = this->urm[curent];
			}

			// daca terminam while-ul inseamna ca am ajuns la ultimul element din lista
			// alocam spatiu pentru noul element

			this->e[PrimLiber].linie = i;
			this->e[PrimLiber].coloana = j;
			this->e[PrimLiber].cheie = e;

			// refacem legaturile
			this->urm[curent] = this->PrimLiber;
			actPrimLiber();
			
		}	
		return oldValue;
	}
	
}

// BC = O(1)
// AC = WC = O(nrL * cp)
int Matrice::numarElementeNenule(int line) const {

	if (line < 0 || line >= nrL)
		throw std::exception();

	int numarElementeNenule = 0;

	for (int j = 0; j < nrL; j++) {
		if (element(line, j) != NULL_TELEMENT)
			numarElementeNenule++;
	}

	return numarElementeNenule;
}


