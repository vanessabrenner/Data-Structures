#include "IteratorColectie.h"
#include "Colectie.h"

//BC = AC = WC = θ(1)
IteratorColectie::IteratorColectie(const Colectie& c): col(c) {

	curent = col.prim;
}

//BC = AC = WC = θ(1)
TElem IteratorColectie::element() const{
	if (!valid())
		throw std::bad_exception();

	return col.e[curent];
}

//BC = AC = WC = θ(1)
bool IteratorColectie::valid() const {
	if(curent == -1)
		return false;
	return true;
}

//BC = AC = WC = θ(1)
void IteratorColectie::urmator() {
	if (!valid())
		throw std::bad_exception();

	curent = col.urm[curent];
}

//BC = AC = WC = θ(1)
void IteratorColectie::prim() {
	
	curent = col.prim;
}
