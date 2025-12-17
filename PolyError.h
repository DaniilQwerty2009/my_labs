#ifndef POLY_ERROR_H
#define POLY_ERROR_H
#include <stdexcept>
#include <iostream>
#include "Polynomial.h"

//Павловския практикум???

class PolyError : public std::exception
{
protected:
    const char* message;

public:
    PolyError(const char* errorMessage): message(errorMessage)
        {   }
    PolyError(const PolyError& other): message(other.message)
        {   }
    
    virtual const char* what() const noexcept
        { return message; }
};

class OutOfPolynomial : public PolyError
{
private:
    int index;
public:
    OutOfPolynomial(): PolyError("Ошибка обращения к многочлену - выход за границу значений.")
        {    }
    
    const char* what() const noexcept override
    {
        std::cout << "Обращение по индексу " << index << " привело к ошибке!" << std::endl; 
        return message;
    }
};

class PolynomialMiscastError : public PolyError
{
public:
    PolynomialMiscastError(): PolyError("Ошибка - различный тип опрандов.")
        {    } 
};

class HasNoVarError : public PolyError
{
public:
    HasNoVarError() : PolyError("В уравнении отсутсвует переменная.")
        {   }
};

class OutOfQueueError : public PolyError
{
private:
    int index;
public:
    OutOfQueueError(int index): PolyError("Ошибка обращения к очереди - выход за границу значений."), index(index)
        {   } 

    const char* what() const noexcept override
    {
        std::cout << "Обращение по индексу " << index << " привело к ошибке:" << std::endl; 
        return message;
    }
};

class QueueStructureError : public PolyError
{
public:
    QueueStructureError(): PolyError("Критическая ошибка структуры очереди." )
        {   }
};

class EmptyQueueError : public PolyError
{
public:
    EmptyQueueError(): PolyError("Ошибка обращения к очереди - очередь пуста.")
        {   }
};

class ArithmeticError: public PolyError
{
public: 
    ArithmeticError(const char* errorMessage): PolyError(errorMessage)
        {   }
};

class DivisionByZero: public ArithmeticError
{
public:
    DivisionByZero(): ArithmeticError("Деление на ноль.")
        {   }
};

#endif