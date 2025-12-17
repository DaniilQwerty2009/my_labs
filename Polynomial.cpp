#include "Polynomial.h"

using std::cout;
using std::cin;
using std::endl;


Polynomial::Polynomial(unsigned d): degree(d)
{
    members = new Member[membersQuantity()];   

    for(int i = degree, j = 0; i >= 0; i--, j++)
    {
        members[j].degree = i;
        members[j].coefficient = 0;
    }

}

Polynomial::Polynomial(const Polynomial &other): degree(other.degree)
{
    members = new Member[membersQuantity()];

    for(unsigned i = 0; i < membersQuantity(); ++i)
    {
        members[i].degree = other.members[i].degree;
        members[i].coefficient = other.members[i].coefficient;
    }    
}

Polynomial::~Polynomial() 
{
    delete[] members;
}

Polynomial& Polynomial::operator=(const Polynomial &other)
{
    if(typeid(*this) != typeid(other))
        throw PolynomialMiscastError();

    if(degree != other.degree)  //Если степени многочленов отличаются, то:
    {
        degree = other.degree;  //1)Корректно обновляем память под нужный размер
        if(members != nullptr) 
            delete [] members;
        members = new Member[membersQuantity()];

        for(unsigned i = 0; i < membersQuantity(); ++i)    //2)Копируем значения
        {
            members[i].degree = other.members[i].degree;
            members[i].coefficient = other.members[i].coefficient;
        }  
    }
    else                        //Если степени равны, переписываем сушествующие коэф-ты
    {
    for(unsigned i = 0; i < membersQuantity(); ++i)
        members[i].coefficient = other.members[i].coefficient;
    }  
    
    return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial &other)
{
    if(typeid(*this) != typeid(other))
        throw PolynomialMiscastError();

    // К большему (по степени) прибавляем меньший - без доп. выделения памяти д
    if(degree >= other.degree)
    {
        for(int o = other.degree, t = this->degree; o >= 0; --t, --o)
        {
            members[t].coefficient += other.members[o].coefficient;     // Сложение одночленов с олинаковыми степенями
        }
    return *this;
    }
    // - с доп. выделением памяти для отсутвующих степеней 
    else
    {
        // Создаем временный блок и копируем туда значение большего многочлена
        // (расширяем вызывающий метод многочлен)
        Member* temp_members = new Member[other.membersQuantity()];
        for(unsigned i = 0; i < other.membersQuantity(); ++i)
        {
            temp_members[i] = other.members[i];
        }

        for(int t = this->degree, temp = other.degree; t >= 0; --t, --temp)
        {
            temp_members[temp].coefficient += members[t].coefficient;   // Сложение одночленов
        }

        delete [] this->members;        // Временный блок памяти теперь основной 
                                        // для вызывающего многочлена
        this->members = temp_members;
        this->degree = other.degree;
    }
    return *this;
}

Polynomial Polynomial::operator+(const Polynomial &other) const
{
    Polynomial result = *this; // Увеличиваем копию
    result += other;
    return result;
}

Polynomial& Polynomial::operator++()
{   
    // Увеличиваем вызывающий многочлен, его же возвращаем
    for(unsigned i = 0; i < membersQuantity(); ++i)
        members[i].coefficient++;
    return *this;
}

Polynomial Polynomial::operator++(int)
{   
    Polynomial temp = *this;   // Увеличиваем вызывающий многочлен, возвращаем копию
    ++(*this);                 // Так инкремент не повлияет на результат выражения
    return temp;
}

// Операторы декремента вспомогательные, для демонстрации в лабораторной номер 2
Polynomial& Polynomial::operator--()
{
    for(unsigned i = 0; i < membersQuantity(); ++i)
        members[i].coefficient--;
    return *this;
}

Polynomial Polynomial::operator--(int)
{
    Polynomial temp = *this;
    --(*this);
    return temp;
}

Polynomial& Polynomial::operator-=(const Polynomial &other)
{   
    if(typeid(*this) != typeid(other))
        throw PolynomialMiscastError();

    // Вычитание из большего (по степени) меьшего - без выделения доп.памяти
    if(degree >= other.degree)
    {
        for(int o = other.degree, t = this->degree; o >= 0; --t, --o)
        {
            members[t].coefficient -= other.members[o].coefficient;
        }
    return *this;
    }
    // - с выделением доп.памяти для недостающих высших степеней
    else
    {
        Member* temp_members = new Member[other.membersQuantity()];
        
        // Новый (временный) блок - больший (по степени) операнд с противоположнм знаком
        for(unsigned i = 0; i < other.membersQuantity(); ++i)
        {
            temp_members[i].coefficient = -other.members[i].coefficient;
            temp_members[i].degree = other.members[i].degree;
        }
        // К новому с противоположным знаком прибавляем меньший: x - (y) = -y + x
        for(int t = this->degree, temp = other.degree; t >= 0; --t, --temp)
        {
            temp_members[temp].coefficient += members[t].coefficient;
        }

        delete [] this->members;    // Переопределяем на новое значение

        this->members = temp_members;
        this->degree = other.degree;
    }
    return *this;
}

int& Polynomial::operator[](unsigned degree)
{

    if(this->degree < degree)
        throw OutOfPolynomial();

    return members[this->degree - degree].coefficient;    //Нулевой индекс = старшая степень и т.д.
}

const int& Polynomial::operator[](unsigned degree) const
{
    if(this->degree < degree)
        throw OutOfPolynomial();

    return members[this->degree - degree].coefficient;
}

std::ostream& operator<<(std::ostream& fout, const Polynomial& object)
{
    object.print(fout);
    return fout;
}

Polynomial::operator bool() const
{
    bool haveDegree = false;    // Флаг поиска переменной со степенью
    for(unsigned i = 0; i < degree && !haveDegree; ++i)
    {
        if(members[i].coefficient != 0)   // Поиск переменной со степенью
        return haveDegree = true;
    }

    return haveDegree;
}

void Polynomial::setCoefficient(unsigned degree, int coefficient)   
{
    if(degree > this->degree)
        throw OutOfPolynomial();

    members[this->degree - degree].coefficient = coefficient;
}

void Polynomial::fillPolynomial()
{
    cout << "Ввод коэффицентов многочлена:" << endl;

    int val;
    for(int i = 0, d = degree; d >= 0; d--, i++)
    {

        if(d != 0)
            cout << "коэффицент при переменной "<< d << "-й степени: ";
        else
            cout << "свободный коэффицент: ";

        while(true)
        {
            if(cin >> val)
            {
                members[i].coefficient = val;
                break;
            }
            else
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Неверный формат повтроите ввод: ";
            }
        }
    }
}

void Polynomial::print(std::ostream& fout) const
{
    bool first = true;  //Флаг первого элемента (для прбуска знака +)
    int coef;           //Коеффициент переменной
    unsigned absCoef;   //Коеффициент переменной без знака
    int deg;            //Степень переменной

    for(unsigned i = 0; i < this->membersQuantity(); ++i)
    {  
        coef = this->members[i].coefficient; 
        absCoef = abs(coef);
        deg = this->members[i].degree;

        //Пропуск одночленов с нулевым коэф-том (равны нулю)
        if(coef == 0)
                continue;

        if(first)
        {
            // Корректный вывод первого одночлена (без +)
            first = false;
            if(coef != 1 && coef != -1)   // Нужно ли печатать коэф-т
            {    
                fout << coef << ((deg != 0)? ((deg == 1)? "x":"x^"):""); 
                if(deg != 1 && deg != 0)
                    fout << deg; 
            } 
            else            
            {
                if(coef == -1)
                    fout << '-';        //Оставляем знак коэф-та
                if(deg == 0)
                    fout << absCoef;       // Если единичный коэф-т при x^0, печатаем его
                else
                    fout << ((deg == 1)? "x":"x^"); 
                if(deg > 1)
                    fout << deg;
            }
            continue;
        }
        
        // Вывод остальных одночленов
        fout << ((coef > 0)? " + ":" - ");  // знак перед одночленом

        if(coef != 1  || deg == 0) // коэф-т, если он не 1 или 1 без переменной
            fout << absCoef;              

        fout << ((deg != 0)? ((deg == 1)? "x":"x^"):"");

        if(deg != 1 && deg != 0)    //степень
            fout << deg;
    }
}

int Polynomial::getResult(int param)    //Принимает параметр
{
    int result = 0;     //Переменная-накопитель 
    for(unsigned i = 0; i < membersQuantity(); ++i)
    {
        result += (members[i].coefficient * pow(param, members[i].degree)); // +=value*(x^degree)
    }
    return result;
}

Polynomial subtraction(const Polynomial& first, const Polynomial& second)
{
    if(typeid(first) != typeid(second))
        throw PolynomialMiscastError();

    Polynomial result = first;
    result -= second;
    return result;
}

void Polynomial::writeToBinFile(const char* filename) const
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

    fout.write((char*)&degree, sizeof(degree)); //Побайтно записываем степень многочлена     
    
    for(unsigned i = 0; i <= degree; ++i)       //Побайтно записываем массив ондночленов
        fout.write((char*)&members[i], sizeof(Member));
}

void Polynomial::readFromBinFile(const char* filename)
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

    unsigned oldDegree = degree;                     //Изначальная степень многочлена

    try
    {
    fin.read((char*)&degree, sizeof(degree));   //Побайтно считываем степень многочлена

    if(degree != oldDegree)                     //Если из файла пишем другую степень, переопределяем память
        this->allocateMembers(degree);

    for(unsigned i = 0; i <= degree; ++i)       //и массив одночленов
        fin.read((char*)&members[i], sizeof(Member));
    }
    catch(...)
    {
        fin.close();
        throw;
    }
}

void Polynomial::allocateMembers(unsigned degree)
{
    delete[] members;

    this->degree = degree;
    members = new Member[membersQuantity()];   

    for(int i = degree, j = 0; i >= 0; i--, j++)
    {
        members[j].degree = i;
        members[j].coefficient = 0;
    }
}

void Polynomial::reallocateMembers(unsigned degree)
{
    unsigned i = 0;  //счетчкик до нового degree

    Member* newMembers = new Member[degree+1];      //Новый массив

    for(; i <= this->degree && i <= degree; ++i)    //Копируем пока не дойдем до конца одного из массивов
    {
        newMembers[i].coefficient = members[i].coefficient;
        newMembers[i].degree = (degree-i);
    }


    if(i < degree)                                //Если новый больше, заполняем его значениями по умолчанию
    {
        for(; i <= degree; ++i)
        {
            newMembers[i].coefficient = 0;
            newMembers[i].degree = (degree-i);
        }
    }

    this->degree = degree;
    delete[] members;
    members = newMembers;
}
