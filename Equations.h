#ifndef EQUATIONS_H
#define EQUATIONS_H

#include "Polynomial.h"

class Equations: public Polynomial
{
protected:
    bool isActualRoots = false; //флаг-статус корней (чтобы каждый раз не искать корни при вызове функции, находящей их)
    int rootsQuantity = 0;                  //Кол-во действительных корней
    double* roots = nullptr;            //Массив корней (динамически, т.к. разное кол-во корней)
    
    void allocateRoots(unsigned rootsQnty);   //Переоперделение размера памяти под корни
    void allocateMembers(unsigned degree) override;
    void reallocateMembers(unsigned degree) override;

public:
    Equations(unsigned const degree);
    Equations(const Equations& other);

    virtual ~Equations()
    {
        delete[] roots;
    }
  
    Equations& operator+(const Equations& other) = delete;  //Явный запрет на опреации,
    Equations& operator-(const Equations& other) = delete;  //не используемые для уравнений
    
    Equations& operator=(const Equations& other);
    Equations& operator+=(const Equations& other);
    Equations& operator-=(const Equations& other);

    void fillPolynomial() override;                         //Презапись коэф-тов уравнения      

    virtual void solve() = 0;   //Нахождение корней
    
    double* getRoots();         //Обертка для solve() с проверкой на актуальность корней (если корни актуальны, вернет их без solve()
    
    int getRootsQuantity();     //Как getRoots(), но возврат кол-ва корней

    void print(std::ostream& fout = std::cout) const override;

    void setCoefficient(unsigned degree, int coefficient) override;

    friend std::ostream& operator<<(std::ostream& fout, const Equations& object);

    virtual void writeToBinFile(const char* filename) const override;    //Запись в бинарный файл
    virtual void readFromBinFile(const char* filename) override;         //Чтение из бинарного файла
};



#endif