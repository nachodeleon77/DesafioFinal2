#include <string>
#include "Exemplar.h"
#include "Member.h"
#include <vector>
#include <iostream>

#pragma once
using namespace std;


class Book
{
private:
	string name;
	string ISBNcode;
	string author;
	vector<Exemplar> exemplarList;
public:
	Book();
	string getName();
	void setName(string name);
	string getISBNcode();
	void setISBNcode(string code);
	string getAuthor();
	void setAuthor(string author);
	void addExemplar(Exemplar e);
	void printExemplars();
	int availableExemplars();
	bool hasExemplars();
	Exemplar lendExemplar(Member m);
	void lendExemplarIndex(int exemplarindex, Member m);
	void returnExemplar(Exemplar e);
	vector<Exemplar> getExemplarList();
	int getExemplarIndexfromList(int editionNumber);
	Exemplar getExemplarfromIndex(int index);
	void deleteExemplarByIndex(int i);
};

