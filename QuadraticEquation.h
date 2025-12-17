#ifndef QUADRATIC_EQUATION_H
#define QUADRATIC_EQUATION_H

#include "Equations.h"

class QuadraticEquation: public Equations
{
    static const int quadraticDegree = 2;   //Степерь квадратного ур-ия


public:
    QuadraticEquation(int a = 1, int b = 0, int c = 0);
    QuadraticEquation(const QuadraticEquation& other): Equations(other)
        {   }
    
    void solve() override;      //Нахождение корней ур-ия, bool пока не настроены исключения
   
};

#endif