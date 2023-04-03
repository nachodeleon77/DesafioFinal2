#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#include "Loan.h"

Loan::Loan(Exemplar exemplar, Member member)
{
	this->exemplar = exemplar;
	this->member = member;
	this->date = time(0);
}

Loan::Loan(Exemplar exemplar, Member member, time_t date)
{
	this->exemplar = exemplar;
	this->member = member;
	this->date = date;
}

Loan::Loan()
{
}

void Loan::setExemplar(Exemplar e)
{
	this->exemplar = e;
}

Exemplar Loan::getExemplar()
{
	return this->exemplar;
}

void Loan::setMember(Member m)
{
	this->member = m;
}

Member Loan::getMember()
{
	return this->member;
}

string Loan::getDate() {
	char buffer[80];
	std::strftime(buffer, 80, "%d/%m/%Y %H:%M:%S", localtime(&this->date));
	std::string result(buffer);
	return result;
}

time_t Loan::getDateRaw()
{
	return this->date;
}
