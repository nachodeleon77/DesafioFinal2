#pragma once
#include <vector>
#include "Loan.h"
#include "Return.h"
#include "Book.h"

class Library
{
private:
	vector<Loan> loanHistory;
	vector<Return> returnHistory;
	vector<Member> memberList;
	vector<Book> bookList;
public:
	void addLoanHistory(Loan loan);
	vector<Loan> getLoanHistory();
	void addReturnHistory(Return ret);
	vector<Return> getReturnHistory();
	void addMember(Member member);
	vector<Member> getmemberList();
	vector<Book> getBookList();
	void addBook(Book book);
	int getMemberIndexfromList(string idnumber);
	int getBookIndexfromList(string ISBNcode);
	void deleteMemberByIndex(int i);
	Book getBookfromIndex(int index);
	void setBookfromIndex(int index, Book book);
	Member getMemberfromIndex(int index);
	void setMemberfromIndex(int index, Member member);
	void printBooks();
	int getExemplarfromList(vector<Exemplar> exemplars, int editionNumber);
};

