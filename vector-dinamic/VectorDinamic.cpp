#include "VectorDinamic.h"
#include "IteratorVectorDinamic.h"
#include <exception>
#include <iostream>
#include <limits>

//#define MAX INT_MAX
//#define MIN INT_MIN

using namespace std;

void VectorDinamic::redim() {
	// O(n)
	
	// alocam spatiu dublu
	TElem* enew = new int[cp * 2];

	// copiem elementele in spatiul nou rezervat
	for (int i = 0; i < n; i++) 
		enew[i] = e[i];

	// dublam capacitatea
	cp = 2 * cp;

	// eliberam vechea zona din memorie
	delete[] e; 
	
	// vectorul indica spre noua zona
	e = enew; 
	
}


VectorDinamic::VectorDinamic(int cp) {
	// O(1)

	// aruncam exceptii 
	if (cp <= 0) {
		throw bad_exception();
	}
	
	// setam capacitatea
	this->cp = cp; 
	
	// alocam spatiu de memorare pentru vector
	e = new TElem[cp]; 
	
	// setam numarul de elemente
	this->n = 0; 
}



VectorDinamic::~VectorDinamic() {
	// O(1)	

	// eliberam zona de memorie
	delete[] e; 
}



int VectorDinamic::dim() const{
	// O(1)

	// functie de returnare a dimensiuniii vectorului (size()-ul de la oop)
	return n; 
}



TElem VectorDinamic::element(int i) const{
	// O(1)

	// aruncam exceptii
	if (i > this->n) {
		throw bad_exception();
	}
	
	// functie de returnare a elemntului de pe pozitia i
	return e[i]; 
}



void VectorDinamic::adaugaSfarsit(TElem e) {
	// O(n)

	// verificam daca nu depasim capacitatea
	if (cp == n)
		redim();

	// adaugam la sfarsit
	this->e[n] = e;

	// marim dimensiunea cu 1
	n++;
}


void VectorDinamic::adauga(int i, TElem e) {
	// O(n)

	// aruncam axceptii
	if (i > this->n) {
		throw bad_exception();
	}
	
	// verificam daca nu depasim capacitatea
	if (cp == n)
		redim();	

	// tinem in variabila a valoarea elementului initial de pe pozitia i 
	TElem a = element(i);

	// marim dimensiunea cu 1
	n++;

	// punem restul elementelor la locul potrivit
	for (int j = i + 1; j < n; j++) {
		TElem b = element(j);
		this->e[j] = a;
		a = b;
	}
		
	// punem noua valoare la locul potrivit
	this->e[i] = e;

	/*cout << n << endl;
	for (int i = 0; i < n; i++)
		cout << this->e[i] << ' ';
	cout << endl;*/

}


TElem VectorDinamic::modifica(int i, TElem e) {
	// O(1)

	// aruncam exceptii
	if (i > this->n) {
		throw bad_exception();
	}
	
	// punem intr o variabila vechea valoare
	TElem a = this->e[i];

	// modificam elementul de pe pozitia i cu o noua valoare e
	this->e[i] = e;

	/*cout << n << endl;
	for (int i = 0; i < n; i++)
		cout << this->e[i] << ' ';
	cout << endl;*/

	// returnam vechea valoare
	return a;
}


TElem VectorDinamic::sterge(int i) {
	// O(n)

	// aruncam exceptii
	if (i >= this->n) {
		throw bad_exception();
	}

	// punem intr o variabila vechea valoare
	TElem a = element(i);	

	// punem elementele la locul corespunzator
	for (int j = i; j < n - 1; j++) {
		this->e[j] = this->e[j + 1];
	}
	
	// micsoram dimensiunea vectorului
	n--;

	return a;
}

// functionalitate noua
int VectorDinamic::diferentaMaxMin() const {
	// Θ(n)
	
	// daca nu exista elemente in lista
	if (n == 0)
		return -1;

	// aflam minimul din sir
	int MIN = INT_MAX;
	for (int i = 0; i < n; i++) {
		if (this->e[i] < MIN)
			MIN = this->e[i];
	}

	// aflam maximul din sir
	int MAX = INT_MIN;
	for (int i = 0; i < n; i++) {
		if (this->e[i] > MAX)
			MAX = this->e[i];
	}

	//returnam diferenta dintre MAX si MIN
	return MAX - MIN;
}

IteratorVectorDinamic VectorDinamic::iterator() {
	// O(1)

	return IteratorVectorDinamic(*this);
}



