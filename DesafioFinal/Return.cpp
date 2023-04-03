#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS
#include "Return.h"

Return::Return(Exemplar exemplar, Member member)
{
	this->exemplar = exemplar;
	this->member = member;
	this->date = time(0);
}

Return::Return(Exemplar exemplar, Member member, time_t date)
{
	this->exemplar = exemplar;
	this->member = member;
	this->date = date;
}

void Return::setExemplar(Exemplar e)
{
	this->exemplar = e;
}

Exemplar Return::getExemplar()
{
	return this->exemplar;
}

void Return::setMember(Member m)
{
	this->member = m;
}

Member Return::getMember()
{
	return this->member;
}

string Return::getDate() {
	char buffer[80];
	std::strftime(buffer, 80, "%d/%m/%Y %H:%M:%S", localtime(&this->date));
	std::string result(buffer);
	return result;
}

time_t Return::getDateRaw()
{
	return this->date;
}

