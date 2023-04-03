#pragma once
#include "Exemplar.h";
#include "Member.h";
#include "Book.h";
#include <time.h>

class Return
{
private:
	Exemplar exemplar;
	Member member;
	time_t date;
public:
	Return(Exemplar exemplar, Member member);
	Return(Exemplar exemplar, Member member, time_t date);
	void setExemplar(Exemplar e);
	Exemplar getExemplar();
	void setMember(Member m);
	Member getMember();
	string getDate();
	time_t getDateRaw();
};

