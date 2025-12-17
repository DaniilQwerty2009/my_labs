#include "LineralEquation.h"


LineralEquation::LineralEquation(int a, int b) : Equations(lineralDegree)
    {
        members[0].coefficient = a;         //Заполняем коэф-ты
        members[1].coefficient = b;
        rootsQuantity = lineralDegree;
    }

void LineralEquation::solve()
{
    enum quantityOfRoots{no_roots, one_root};

    if(members[0].coefficient == 0)     //Если коэф-т при x == 0
    {
        allocateRoots(no_roots);
        throw HasNoVarError();
    }
    
    if(!roots)
        allocateRoots(one_root);
        
    *roots = (double)-members[1].coefficient/members[0].coefficient;    // х = -b/a
    isActualRoots = true;
}