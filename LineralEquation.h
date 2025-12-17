#ifndef LINERAL_EQUATION_H
#define LINERAL_EQUATION_H

#include "Equations.h"

class LineralEquation: public Equations
{
    static const int lineralDegree = 1;       //Степень линейного ур-ия
    
public:
    LineralEquation(int a = 1, int b = 0);
    LineralEquation(const LineralEquation& other): Equations(other)
    {   }
      
     void solve() override;  //Нахождение корней ур-ия, bool пока не настроены исключения
};

#endif