#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cmath>

#include "PolyError.h"

class Polynomial
{
private:
    unsigned degree;            //Кратность многочлена

protected:
    struct Member           //Одночлен
    {
    int coefficient = 0;      //Значение коэф-та
    int degree;         //Степень переменной
    };

    Member* members = nullptr;  //Массив одночленов
    virtual void allocateMembers(unsigned degree);    //Расширяет/сужает массив одночленов c потерей значений
                                            //для использования при чтении бинарного файла
    virtual void reallocateMembers(unsigned degree);  //Расширяет/сужает массив одночленов без потери значений

public:
    Polynomial(unsigned degree = 0);    //Конструктор по умолчанию
    Polynomial(const Polynomial &other);    //Констркутор копирования

    // Перегрузки опреаторов присваивания, сложения, инермента, декремента
    Polynomial& operator=(const Polynomial &other);
    Polynomial& operator+=(const Polynomial &other);
    Polynomial operator+(const Polynomial &other) const;
    Polynomial& operator-=(const Polynomial &other);
    Polynomial& operator++();
    Polynomial operator++(int);
    Polynomial& operator--();
    Polynomial operator--(int);

    int& operator[](unsigned degree);  //Перегрузка операции индексирования
    const int& operator[](unsigned degree) const;

    friend std::ostream& operator<<(std::ostream& fout,const Polynomial& object);

    // Проверка на наличие переменных с ненулевой степенью
    explicit operator bool() const;  //true, если есть ненулевая степень

    virtual ~Polynomial();

    virtual void setCoefficient(unsigned degree, int coefficient);  //изменение коэф-та одночлена
    inline unsigned membersQuantity() const            //вычисление размерности динамического массива одночленов
        {return degree+1;}
    virtual void fillPolynomial();      //Запись/перезапись значений коэф-тов одночленов
    int getResult(int param);   //Вычисление многочлена по известному параметру
    virtual void print(std::ostream& fout = std::cout) const;     //Отображение многочлена в удобной форме

    virtual void writeToBinFile(const char* filename) const;    //Запись в бинарный файл
    virtual void readFromBinFile(const char* filename);         //Чтение из бинарного файла

    friend Polynomial subtraction(const Polynomial &first, const Polynomial &second); // Вычитание

    const unsigned& getDegree() const 
        { return degree; }   //Геттер degree
    const Member* getMembers() const 
        { return members;}   //Геттер одночленов

    virtual double* getRoots()      //Геттеры для подкласса уравнений
        { return 0;      }
    virtual int getRootsQuantity()
        { return 0;      }
    virtual const char* makeSound()
    {
        return "0";
    }
};

#endif