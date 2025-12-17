#include <iostream>
#include <stdexcept>
#include <iomanip>
#include "LineralEquation.h"
#include "QuadraticEquation.h"
#include "PolyQueue.h"
#include "PolyError.h"

using std::cout;
using std::cin;
using std::endl;


int main()
{
    //Методы с генерацией исключений:

    //Polynomial
        //writeToBinFile
    //Equations
        //operator=/+=/-=
    //Lineral/Quadratic
        //solve/getroots
    //PolyQueue   
       //const operator[]
       //extractObject

    cout << std::setfill('=') << std::setw(60) << '=' << endl;
    cout << "ЛАБОРАТОРНАЯ РАБОТА №6" << endl; 
    cout << "ОБРАБОТКА ИСКЛЮЧИТЕЛЬНЫХ СИТУАЦИЙ" << endl;
    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

    cout << "Создадим несколько объектов пользовательских классов для демонстрации." << endl;
    cout << "Объект №1- квадратное уравнение: ";
    Polynomial* quadratic = new QuadraticEquation(4, -6, 2);
    cout << *quadratic << endl;

    cout << "Объект №2- линейное уравнение: ";
    Polynomial* lineral = new LineralEquation(2, -12);
    cout << *lineral << endl;


    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

    cout << "Попытка открыть несуществующий файл для считывания." << endl;
    
    cout << "Результат: " << endl;
    try
    {
        quadratic->readFromBinFile("no_exist_file.txt");
    }
    catch(std::exception& err)
    {
        cout << err.what() << endl;
    }

    cout << std::setfill('-') <<std::setw(60) << '-' << endl;
    cout << "Попытка считать данные с пустого файла." << endl;
    
    cout << "Результат: " << endl;
    try
    {
        quadratic->readFromBinFile("exist_but_empty_file.txt");
    }
    catch(std::exception& err)
    {
        cout << err.what() << endl;
    }

    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

    cout << "Попытка приравнять, сложить, вычесть из линеного уравнения квадратное." << endl;

    cout << "Операция =" << endl;
        
    cout << "Результат: " << endl;
    try
    {
        *lineral = *quadratic;
    }
    catch(PolyError& err)
    {
        cout << err.what() << endl;
    }

    cout << std::setfill('-') <<std::setw(60) << '-' << endl;

    cout << "Операция +=" << endl;

    cout << "Результат: " << endl;
    try
    {
        *lineral += *quadratic;
    }
    catch(PolyError& err)
    {
        cout << err.what() << endl;
    }

    cout << std::setfill('-') <<std::setw(60) << '-' << endl;

    cout << "Операция -=" << endl;

    cout << "Результат: " << endl;
    try
    {
        *lineral -= *quadratic;
    }
    catch(PolyError& err)
    {
        cout << err.what() << endl;
    }

    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

    cout << "Попытка найти корни уравнения без переменных." << endl;
    cout << "Создадим уравнение формата 0*x^2 + 0*x + c = 0 и попытаемся найти его корни." << endl;

    Polynomial* emptyQuadratic = new QuadraticEquation(0,0,99);

    cout << "Результат: " << endl;

    try
    {
    double* roots = emptyQuadratic->getRoots();
    for(int i = 0; i < emptyQuadratic->getRootsQuantity(); ++i)
        cout << roots[i] << endl;
    }
    catch(PolyError& err)
    {
        cout << err.what() << endl;
    }

    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

    cout << "Попытка выхода за пределы очереди." << endl;
    cout << "Добавим два наших многочлена в очередь:" << endl;

    PolyQueue* ourQueue = new PolyQueue;
    ourQueue->createQueue(*lineral);
    ourQueue->addObject(*quadratic);
    cout << *ourQueue << endl;

    cout << "Обратимся к несуществующему третьему объекту." << endl;
    cout << "Результат: " << endl;
    
    try
    {
        cout << (*ourQueue)[2
        ] << endl;
    }
    catch(PolyError& err)
    {
        cout << err.what() << endl;
    }

    cout << std::setfill('=') <<std::setw(60) << '=' << endl;

    cout << "Попытка извлечь объект из пустой очереди." << endl;
    cout << "Результат: " << endl;

    try
    {
        for(int i = 0; i  < 3; ++i)
            ourQueue->extractObject();
    }
    catch(PolyError& err)
    {
        cout << err.what() << endl;
    }

    cout << std::setfill('=') <<std::setw(60) << '=' << endl;
    cout << "Завершение программы." << endl;
    return 0;
}