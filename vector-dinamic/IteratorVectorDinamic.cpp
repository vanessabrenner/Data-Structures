#include "IteratorVectorDinamic.h"
#include "VectorDinamic.h"


IteratorVectorDinamic::IteratorVectorDinamic(const VectorDinamic& _v) :	v(_v) {
	// O(1)

	// seteaza iteratorul pe prima pozitie din vector
	curent = 0;
}



void IteratorVectorDinamic::prim() {
	// O(1)

	// reseteaza iteratorul pe prima pozitie
	curent = 0;
}



bool IteratorVectorDinamic::valid() const{
	// O(1)

	// returneaza True daca iteratorul n a trecut de elementele containerului
	// returneaza False altfel
	return curent < v.dim();
}



TElem IteratorVectorDinamic::element() const{
	// O(1)

	// aruncam exceptii
	if (!valid()) {
		throw "Iteratorul este invalid";
	}
	
	// returneaza elementul de pe pozitia indicata de iterator
	return v.element(curent);
}



void IteratorVectorDinamic::urmator() {
	// O(1)

	// aruncam exceptii
	if (!valid()) {
		throw "Iteratorul este invalid";
	}
	
	// trecem la urmatorul element
	// incrementam curent
	curent++;

}

