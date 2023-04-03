#pragma once
#include <string>
#include <vector>
#include "Exemplar.h"
#include <iostream>

using namespace std;

class Member
{
private:
	string name;
	string lastname;
	string idnumber;
	vector<Exemplar> exemplarList;
	int maxBooksQty;
protected:
	int cuotaMensual;
public:
	Member();
	int type;
	string getName();
	void setName(string name);
	string getLastname();
	void setLastName(string lastname);
	string getIdnumber();
	void setIDnumber(string idnumber);
	string getType();
	int getTypeRaw();
	void Borrow(Exemplar e);
	void printExemplars();
	int getMaxBooks();
	void setMaxBooks(int qty);
	int getBooksLoaned();
	bool canBorrow();
	void returnExemplar(Exemplar e);
	vector<Exemplar> getExemplarList();
};

