#pragma once
#include <iostream>
#include <conio.h>
#include "Loan.h"
#include "Book.h"
#include "Return.h"


using namespace std;

class View
{
public:
	void showMenu();
	void loanHistory(vector<Loan> l);
	void returnHistory(vector<Return> r);
	void membersMenu();
	void membersList(vector<Member> members);
	void memberNew(int param, int error);
	void memberDelete(vector<Member> members);
	void addLoan(int param, vector<Member> members, vector<Book> books, Book selectedbook, int error);
	void showLoan(Exemplar exemplar, Book book);
	void showNoExemplars();
	void addReturn(int param, vector<Member> members, vector<Exemplar> exemplars, int error);
	void bookMenu();
	void bookList(vector<Book> books);
	void bookNew(int param, int error);
	void bookDelete(vector<Book> books);
	void exemplarMenu(Book book);
	void exemplarList(vector<Exemplar> exemplar, Book book);
	void exemplarNew(int param, Book book, int error);
	void exemplarDelete(vector<Exemplar> exemplar, Book book);
	void exemplarBook(vector<Book> books, int error);
};

