#include "Book.h"

Book::Book()
{
}

string Book::getName()
{
	return this->name;
}

void Book::setName(string name)
{
	this->name = name;
}

string Book::getISBNcode()
{
	return this->ISBNcode;
}

void Book::setISBNcode(string code)
{
	this->ISBNcode = code;
}

string Book::getAuthor()
{
	return this->author;
}

void Book::setAuthor(string author)
{
	this->author = author;
}

void Book::addExemplar(Exemplar e)
{
	this->exemplarList.push_back(e);
}

void Book::printExemplars()
{
	vector<Exemplar>::iterator iter;
	for (iter = this->exemplarList.begin(); iter != this->exemplarList.end(); ++iter) {
		cout << iter->getLocation() << " - " << iter->geteditionNumber() << "\n";
	}
}

int Book::availableExemplars()
{
	return (int)this->exemplarList.size();
}

bool Book::hasExemplars()
{
	int size = this->exemplarList.size();
	if (size != 0) {
		return true;
	}
	else {
		return false;
	}
}

Exemplar Book::lendExemplar(Member m)
{
	Exemplar ret = *(this->exemplarList.begin());
	exemplarList.erase(this->exemplarList.begin());
	m.Borrow(ret);
	return ret;
}

void Book::lendExemplarIndex(int exemplarindex, Member m)
{
	exemplarList.erase(exemplarList.begin() + exemplarindex);
}

void Book::returnExemplar(Exemplar e)
{
	this->exemplarList.push_back(e);
}

vector<Exemplar> Book::getExemplarList()
{
	return this->exemplarList;
}

int Book::getExemplarIndexfromList(int editionNumber)
{
	vector<Exemplar>::iterator iter;
	int i = 0;
	for (iter = this->exemplarList.begin(); iter != this->exemplarList.end(); ++iter) {
		if (iter->geteditionNumber() == editionNumber) {
			return i;
			break;
		}
		i++;
	}
	return -1;
}

Exemplar Book::getExemplarfromIndex(int index)
{
	return exemplarList[index];
}
