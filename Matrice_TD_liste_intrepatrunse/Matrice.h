 #pragma once

typedef int TElem;


#define NULL_TELEMENT 0

struct Triplet {
	int linie;
	int coloana;
	TElem cheie;
};

class Matrice {

private:

	// capacitatea vectorului e
	int cp;

	// numarul de linii
	int nrL;

	// numarul de coloane
	int nrC;

	// va contine elementele
	Triplet* e;
	
	// referinta la urmatorul din lista
	int* urm;
	
	// referinta la prima pozitie libera din lista
	int PrimLiber;

	
	// actualizeaza PrimLiber
	void actPrimLiber();

	// functia de dispersie
	int d(TElem e);

	// initializeaza spatiul liber
	void initSpatiuLiber();

	// pentru redimensionare
	// void redim();

public:

	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);

	//destructor
	~Matrice(){};

	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//indicii se considera incepand de la 0
	TElem element(int i, int j) const;


	// returnare numar linii
	int nrLinii() const;

	// returnare numar coloane
	int nrColoane() const;

	// sterge o cheie din lista
	void sterge(int i, int j, TElem e);


	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	TElem modifica(int i, int j, TElem e);

	// functionalitate noua
	// returneaza numarul de elemente nenule de pe o linie data
	// arunca exceptie in cazul in care linie nu este valida
	int numarElementeNenule(int line) const;

};







