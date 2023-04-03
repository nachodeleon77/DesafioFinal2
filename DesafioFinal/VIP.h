#pragma once
#include "Member.h"
class VIP :
    public Member
{
public:
    VIP();
    int getCuotaMensual();
    void setCuotaMensual(int cuota);
};

