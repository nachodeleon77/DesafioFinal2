#include "Member.h"

Member::Member()
{
	this->name = "Sin Nombre";
	this->lastname = "Sin Apellido";
	this->idnumber = "367784";
	this->setMaxBooks(1);
	this->type = 0;
}

string Member::getName()
{
    return this->name;
}

void Member::setName(string name)
{
    this->name = name;
}

string Member::getLastname()
{
    return this->lastname;
}

void Member::setLastName(string lastname)
{
    this->lastname = lastname;
}

string Member::getIdnumber()
{
    return this->idnumber;
}

void Member::setIDnumber(string idnumber)
{
    this->idnumber = idnumber;
}

string Member::getType()
{
	if (this->type == 0) {
		return "Socio Regular";
	}
	else {
		return "Socio VIP";
	}
}

int Member::getTypeRaw()
{
	return this->type;
}

void Member::Borrow(Exemplar e)
{
	this->exemplarList.push_back(e);
}

void Member::printExemplars()
{
	// declare iterator
	vector<Exemplar>::iterator iter;

	// use iterator with for loop
	for (iter = this->exemplarList.begin(); iter != this->exemplarList.end(); ++iter) {
		cout << iter->getLocation() << " - " << iter->geteditionNumber() << "\n";
	}
}

int Member::getMaxBooks()
{
	return this->maxBooksQty;
}

void Member::setMaxBooks(int qty)
{
	this->maxBooksQty = qty;
}

int Member::getBooksLoaned()
{
	return this->exemplarList.size();
}

bool Member::canBorrow()
{
	int size = this->exemplarList.size();
	if (this->maxBooksQty > size) {
		return true;
	}
	else {
		return false;
	}
	
}

void Member::returnExemplar(Exemplar e)
{
	// declare iterator
	vector<Exemplar>::iterator iter;

	// use iterator with for loop
	for (iter = this->exemplarList.begin(); iter != this->exemplarList.end(); ++iter) {
		if (e.geteditionNumber() == iter->geteditionNumber()) {
			exemplarList.erase(iter);
			break;
		}
	}
}

vector<Exemplar> Member::getExemplarList()
{
	return this->exemplarList;
}
