#include "IteratorMultime.h"
#include "Multime.h"

// O(n)
IteratorMultime::IteratorMultime(const Multime& m) : mult(m) {
	prim();
}

// inordine

// θ(1)
TElem IteratorMultime::element() {
	if (!valid())
		throw bad_exception();

	return this->curent->e;
}

// O(1)
bool IteratorMultime::valid() {
	if (this->curent != nullptr)
		return true;

	return false;
}

// O(n)
void IteratorMultime::urmator() {
	if (!valid())
		throw bad_exception();

	Nod* nod = this->stiva.top();
	this->stiva.pop();	
	
	if (nod->dreapta != nullptr) {
		nod = nod->dreapta;
		while (nod != nullptr) {
			this->stiva.push(nod);
			nod = nod->stanga;
		}
	}

	if (!this->stiva.empty()) {
		this->curent = this->stiva.top();
	}
	else {
		this->curent = nullptr;
	}
}

// O(n)
void IteratorMultime::prim() {

	this->curent = mult.radacina;
	while (!this->stiva.empty())
		this->stiva.pop();

	while (this->curent != nullptr) {
		this->stiva.push(this->curent);
		this->curent = this->curent->stanga;
	}

	if (!this->stiva.empty())
		this->curent = this->stiva.top();
	else
		this->curent = nullptr;
}

