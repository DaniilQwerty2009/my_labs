#include "Equations.h"

using std::cout;
using std::endl;


//Конструкоры вызываются через LineralEquation и QuadraticEauation
Equations::Equations(unsigned const degree) : Polynomial(degree), rootsQuantity(0)   
    { roots = new double[degree]; }

Equations::Equations(const Equations& other): Polynomial(other)
{
     if(other.isActualRoots)                    //Если корни актуальны, копируем их
    {
        rootsQuantity = other.rootsQuantity;
        isActualRoots = true;
        roots = new double[rootsQuantity];

        for(int i = 0; i < rootsQuantity; ++i)
            roots[i] = other.roots[i];
    }
}

Equations& Equations::operator=(const Equations& other)
{
    if(typeid(*this) != typeid(other))       //Нет преобразования одного типа ур-ия к другому,
        throw PolynomialMiscastError();         
        

    Polynomial::operator=(other);
    isActualRoots = false;
    return *this;
}

Equations& Equations::operator+=(const Equations& other)
{
    if(typeid(*this) != typeid(other))       //Нет преобразования одного типа ур-ия к другому,
        throw PolynomialMiscastError();                   

    Polynomial::operator+=(other);
    isActualRoots = false;
    return *this;
}

Equations& Equations::operator-=(const Equations& other)
{
    //Нет преобразования одного типа ур-ия к другому,
    if(typeid(*this) != typeid(other))         
        throw PolynomialMiscastError(); 

    Polynomial::operator-=(other);
    isActualRoots = false;
    return *this;
}

void Equations::allocateRoots(unsigned rootsQnty)   //Переопределяем размер памяти для корней
{
    enum quantityOfRoots{no_roots, one_root, two_roots};

    delete[] roots;
    if(rootsQnty == no_roots)
        roots = nullptr;
    else
        roots = new double[rootsQnty];

    this->rootsQuantity = rootsQnty;
}

void Equations::fillPolynomial()
{
    Polynomial::fillPolynomial();           //Перезаполняем кэф-ты
    isActualRoots = false;                  //Актуальность корней
}

void Equations::print(std::ostream& fout) const
{
    if(!(*this))                //Не печатаем пустоту или ур-ие без переменных
        return;                 //(bool(*this) - проверка на наличие переменных со степенью)

    Polynomial::print(fout);
    fout << " = 0";
}

double* Equations::getRoots()
{
    if( !isActualRoots )    //Проверка на актуальность корней
    try
    {
        solve();
    }           
    catch(...)
    {
        cout << "Ошибка метода solve:" << endl;
        throw;
    }        
        
    return roots;
}

int Equations::getRootsQuantity()
{
    if(isActualRoots)
        return rootsQuantity;
    
    try
    {
        solve();
    }           
    catch(...)
    {
        cout << "Ошибка метода solve:" << endl;
        throw;
    }   
    return rootsQuantity;   
}

void Equations::setCoefficient(unsigned degree, int coefficient)
{
    Polynomial::setCoefficient(degree, coefficient);   //Меняем коэф-т и статус корней
    isActualRoots = false;
}

std::ostream& operator<<(std::ostream& fout, const Equations& object)
{
    object.print(fout);

    return fout;
}

void Equations::allocateMembers(unsigned degree)
{
    if(this->getDegree() != degree)
    {
        cout << "Попытка изменить вид уравнения! Операция с объектом не выпонена!" << endl;
        return;
    }

    Polynomial::allocateMembers(degree);
    isActualRoots = false;
}

void Equations::reallocateMembers(unsigned degree)
{
    if(this->getDegree() != degree)
    {
        cout << "Попытка изменить вид уравнения! Операция с объектом не выпонена!" << endl;
        return;
    }

    Polynomial::reallocateMembers(degree);
    isActualRoots = false;
}

void Equations::writeToBinFile(const char* filename) const
{
    std::ofstream fout;
    fout.exceptions(std::ios::failbit);

    try
    {
        //Открвыаем выходной поток в бинарном режиме
        fout.open(filename, std::ios::binary);
    }
    catch(const std::exception& e)
    {
        fout.close();
        throw;
    }
    fout.exceptions(std::ios::goodbit);   

    fout.write((char*)&getDegree(), sizeof(getDegree())); //Побайтно записываем степень многочлена     
    
    for(unsigned i = 0; i <= getDegree(); ++i)       //Побайтно записываем массив ондночленов
        fout.write((char*)&members[i], sizeof(Member));

    fout.write((char*)&isActualRoots, sizeof(bool));

    fout.write((char*)&rootsQuantity, sizeof(int));

    fout.write((char*)roots, sizeof(double) * rootsQuantity);
}

void Equations::readFromBinFile(const char* filename)
{
        //Отурываем входной поток в бинарном режиме
    std::ifstream fin;
    fin.exceptions(std::ios::failbit);

    try
    {
        fin.open(filename, std::ios::binary);
    }
    catch(...)
    {
        fin.close();
        throw;
    }
    // fin.exceptions(std::ios::goodbit);    

    unsigned oldDegree = getDegree();                     //Изначальная степень многочлена

    try
    {
    fin.read((char*)&getDegree(), sizeof(getDegree()));   //Побайтно считываем степень многочлена

    if(getDegree() != oldDegree)                     //Если из файла пишем другую степень, переопределяем память
        this->allocateMembers(getDegree());

    for(unsigned i = 0; i <= getDegree(); ++i)       //и массив одночленов
        fin.read((char*)&members[i], sizeof(Member));

    fin.read((char*)&isActualRoots, sizeof(bool));

    fin.read((char*)&rootsQuantity, sizeof(int));

    fin.read((char*)roots, sizeof(double) * rootsQuantity);
    }
    catch(...)
    {
        fin.close();
        throw;
    }
}