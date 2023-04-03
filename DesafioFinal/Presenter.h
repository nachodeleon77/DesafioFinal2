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
	View* view = new View();
	Library* library = new Library();
	map<int, int> exemplarloaned;
	void initializeBooks();
	void initializeMembers();
	void initializeLoanHistory();
	void initializeReturnHistory();
	void menu();
	void loanHistory();
	void returnHistory();
	void membersMenu();
	void membersList();
	void membersNew();
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
public:
	Presenter();
};

std::vector<std::string> explode(std::string const& s, char delim);
