#include "VIP.h"

VIP::VIP()
{
	this->setName("Sin Nombre");
	this->setLastName("Sin Apellido");
	this->setIDnumber("367784");
	this->setMaxBooks(3);
	this->type = 1;
}

int VIP::getCuotaMensual()
{
    return this->cuotaMensual;
}

void VIP::setCuotaMensual(int cuota)
{
    this->cuotaMensual = cuota;
}
