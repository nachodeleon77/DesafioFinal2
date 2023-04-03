#pragma once
#include "Book.h"
#include "Exemplar.h"
#include "Member.h"
#include "VIP.h"
#include "View.h";
#include "Library.h";
#include "Loan.h";
#include <map>;
#include <fstream>;
#include <sstream>;

#define esc 27

class Presenter
{
private:
	string member_name, member_lastname, member_number, member_stringtype;
	string book_name, book_autor, book_ISBNcode;
	int exemplar_editionNumber;
	string exemplar_location, exemplar_en;
	View* view = new View();
	Library* library = new Library();
	map<int, int> exemplarloaned;
	void initializeBooks();
	void initializeMembers();
	void initializeExemplars();
	void initializeLoanHistory();
	void initializeReturnHistory();
	void menu();
	void loanHistory();
	void returnHistory();
	void membersMenu();
	void membersList();
	void membersNew(int step, int error);
	void saveMembersToFile();
	void membersDelete();
	void addLoan_ChooseMember(int error);
	void addLoan_ChooseBook(int memberindex);
	void addLoan_ChooseExemplar(int memberindex,int bookindex);
	void addLoan_Save(int memberindex, int bookindex);
	void addReturn_ChooseMember(int error);
	void addReturn_ChooseExemplar(int memberindex, int param, int error);
	void addReturn_Save(int memberindex, Exemplar exemplar);
	void saveLoanOnFile(Loan loan);
	void saveReturnOnFile(Return ret);
	void bookMenu();
	void bookList();
	void bookNew(int step, int error);
	void saveBooksToFile();
	void bookDelete();
	void exemplarMenu(Book b,int index);
	void exemplarList(Book b, int index);
	void exemplarNew(Book b, int index, int step, int error);
	void saveExemplarsToFile(Book book);
	void exemplarDelete(Book b, int index);
	void bookExemplars(int error);
public:
	Presenter();
};

std::vector<std::string> explode(std::string const& s, char delim);
