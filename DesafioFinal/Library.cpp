#include "Library.h"

void Library::addLoanHistory(Loan loan)
{
	this->loanHistory.push_back(loan);
}

vector<Loan> Library::getLoanHistory()
{
	return this->loanHistory;
}

void Library::addReturnHistory(Return ret)
{
	this->returnHistory.push_back(ret);
}

vector<Return> Library::getReturnHistory()
{
	return this->returnHistory;
}

void Library::addMember(Member member)
{
	this->memberList.push_back(member);
}

vector<Member> Library::getmemberList()
{
	return this->memberList;
}

vector<Book> Library::getBookList()
{
	return this->bookList;
}

void Library::addBook(Book book)
{
	this->bookList.push_back(book);
}

int Library::getMemberIndexfromList(string idnumber)
{
	vector<Member>::iterator iter;
	int i = 0;
	for (iter = this->memberList.begin(); iter != this->memberList.end(); ++iter) {
		if (iter->getIdnumber() == idnumber) {
			return i;
			break;
		}
		i++;
	}
	return -1;
}

int Library::getBookIndexfromList(string ISBNcode)
{
	vector<Book>::iterator iter;
	int i = 0;
	for (iter = this->bookList.begin(); iter != this->bookList.end(); ++iter) {
		if (iter->getISBNcode() == ISBNcode) {
			return i;
			break;
		}
		i++;
	}
	return -1;
}

void Library::deleteMemberByIndex(int i)
{
	this->memberList.erase(this->memberList.begin() + i);
}

void Library::deleteBookByIndex(int i)
{
	this->bookList.erase(this->bookList.begin() + i);
}

Book Library::getBookfromIndex(int index)
{
	return bookList[index];
}

void Library::setBookfromIndex(int index, Book book)
{
	bookList[index] = book;
}

Member Library::getMemberfromIndex(int index)
{
	return memberList[index];
}

void Library::setMemberfromIndex(int index, Member member)
{
	memberList[index] = member;
}

void Library::printBooks()
{
	vector<Book>::iterator iter;
	for (iter = this->bookList.begin(); iter != this->bookList.end(); ++iter) {
		cout << iter->getISBNcode() << " - " << iter->getName() << "\n";
	}
}

int Library::getExemplarfromList(vector<Exemplar> exemplars, int editionNumber)
{
	vector<Exemplar>::iterator iter;
	int i = 0;
	for (iter = exemplars.begin(); iter != exemplars.end(); ++iter) {
		if (iter->geteditionNumber() == editionNumber) {
			return i;
			break;
		}
		i++;
	}
	return -1;
}

