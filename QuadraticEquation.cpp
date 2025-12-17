#include "QuadraticEquation.h"
#include <cmath>

QuadraticEquation::QuadraticEquation(int a, int b, int c): Equations(quadraticDegree)
{
    //a*x^2 + b*x + c = 0
    members[0].coefficient = a;
    members[1].coefficient = b;
    members[2].coefficient = c;
    rootsQuantity = quadraticDegree;    
}

void QuadraticEquation::solve()
{
    int a = members[0].coefficient;
    int b = members[1].coefficient;
    int c = members[2].coefficient; 

    enum quantityOfRoots{no_roots, one_root, two_roots};

// Старший или все коэф-ты нулевые (принимает вид линейного уравнения)
if(a == 0)
    {
        if(b == 0)  // Все коэф-ты нулевые
        {
            allocateRoots(no_roots);
            throw HasNoVarError();
        }
        else        // Старшая (x^2) переменная нулевая - один корень
        {
            if((rootsQuantity == one_root) && roots) //Если уже выделенна память под один корень, переписываем ее
                *roots = (double)-c/b;
            else
            {                                        //Иначе выделяем новую память
                allocateRoots(one_root);
                *roots = (double)-c/b;
            }
            isActualRoots = true;
            return;
        }
    }

// Старший коэф-т не нулевой (вид квадратного уравнения)
    double discriminant = b*b - 4*a*c;
    const double sqrtD = std::sqrt(discriminant);
 
    if(discriminant > 0)
    {
        if((rootsQuantity == two_roots) && roots)   //Если есть память под два корня, перепистываем ее
        {
            roots[0] = (double)(-b + sqrtD) / (2*a);
            roots[1] = (double)(-b - sqrtD) / (2*a);
        }
        else
        {
            allocateRoots(two_roots);               //Если нет, выделяем новую и пишем в нее корни
            roots[0] = (double)(-b + sqrtD) / (2*a);
            roots[1] = (double)(-b - sqrtD) / (2*a);
        }
    }
    else if(discriminant == 0)
    {
        if((rootsQuantity == one_root) && roots)    //Если есть память под один корень, перепистываем ее
            *roots = (double)-b / (2*a);
        else
        {
            allocateRoots(one_root);                //Если нет, выделяем новую и пишем в нее корень
            *roots = (double)-b / (2*a);
            isActualRoots = true;
        }
    }
    else                                            //discriminant < 0, корней нет
        allocateRoots(no_roots);

    isActualRoots = true;
}