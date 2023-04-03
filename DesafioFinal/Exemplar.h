#pragma once
#include <string>

using namespace std;

class Exemplar
{
private:
	int editionNumber;
	string location;
	string bookISBNcode;
	string bookName;
public:
	Exemplar(int editionNumber,string location, string ISBNcode);
	Exemplar();
	int geteditionNumber();
	void seteditionNumber(int number);
	string getLocation();
	void setLocation(string location);
	void setBookISBNcode(string ISBNcode);
	string getBookISBNcode();
	void setBookName(string bookname);
	string getBookName();
};

