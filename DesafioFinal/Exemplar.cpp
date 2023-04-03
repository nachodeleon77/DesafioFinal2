#include "Exemplar.h"

Exemplar::Exemplar(int editionNumber,string location, string ISBNcode)
{
    this->editionNumber = editionNumber;
    this->location = location;
    this->bookISBNcode = ISBNcode;
}

Exemplar::Exemplar()
{

}

int Exemplar::geteditionNumber()
{
    return this->editionNumber;
}

void Exemplar::seteditionNumber(int number)
{
    this->editionNumber = number;
}

string Exemplar::getLocation()
{
    return this->location;
}

void Exemplar::setLocation(string location)
{
    this->location = location;
}

void Exemplar::setBookISBNcode(string ISBNcode)
{
    this->bookISBNcode = ISBNcode;
}

string Exemplar::getBookISBNcode()
{
    return this->bookISBNcode;
}

void Exemplar::setBookName(string bookname)
{
    this->bookName = bookname;
}

string Exemplar::getBookName()
{
    return bookName;
}
