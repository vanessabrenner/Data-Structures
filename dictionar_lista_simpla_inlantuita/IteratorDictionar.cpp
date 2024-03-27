#include "IteratorDictionar.h"
#include "Dictionar.h"

using namespace std;

//BC = AC = WC = θ(1)
IteratorDictionar::IteratorDictionar(const Dictionar& d) : dict(d){
	
	this->curent = d.prim;
}

//BC = AC = WC = θ(1)
void IteratorDictionar::prim() {
	
	this->curent = this->dict.prim;
}

//BC = AC = WC = θ(1)
void IteratorDictionar::urmator() {
	
	if (!valid()) {
		throw bad_exception();
	}

	this->curent = this->curent->urm;
}

//BC = AC = WC = θ(1)
TElem IteratorDictionar::element() const{
	
	if (!valid()) {
		throw bad_exception();
	}

	TCheie c = this->curent->e.first;
	TValoare v = this->curent->e.second;

	return pair <TCheie, TValoare>  (c, v);
}

//BC = AC = WC = θ(1)
bool IteratorDictionar::valid() const {
	
	if(this->curent != NULL)
		return true;
	
	return false;	
}

