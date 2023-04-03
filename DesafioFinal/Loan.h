#pragma once
#include "Exemplar.h";
#include "Member.h";
#include "Book.h";
#include <time.h>

class Loan
{
private:
	Exemplar exemplar;
	Member member;
	time_t date;
public:
	Loan(Exemplar exemplar, Member member);
	Loan(Exemplar exemplar, Member member, time_t date);
	Loan();
	void setExemplar(Exemplar e);
	Exemplar getExemplar();
	void setMember(Member m);
	Member getMember();
	string getDate();
	time_t getDateRaw();
};

