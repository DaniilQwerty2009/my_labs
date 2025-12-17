#include <iostream>
#include <stdexcept>
#include <iomanip>
#include "LineralEquation.h"
#include "QuadraticEquation.h"
#include "PolyQueue.h"
#include "PolyError.h"

#include <windows.h>

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




// ==================== GIT ШПАРГАЛКА ====================

// 0) Один раз на каждом компе (настройка личности Git):
//    git config --global user.name "Твоё Имя"
//    git config --global user.email "you@mail.com"
//    git config --global core.autocrlf true        # если Windows

// -----------------------------------------------------------------------
// A) Первый запуск на НОВОМ компьютере (когда репо ещё нет локально)

// 1) Клонируем проект:
//    cd C:\Code   (или куда надо)
//    git clone <URL_репозитория>
//    cd <папка_репозитория>

// 2) Проверяем, что всё ок:
//    git status
//    git remote -v

// -----------------------------------------------------------------------
// B) Начинаю работать на ЛЮБОМ компе (каждый раз перед кодингом)

// 1) Перейти в папку проекта
// 2) Забрать свежие изменения:
//    git pull

//    Если ругается на конфликты:
//    - открываешь конфликтующие файлы
//    - правишь вручную (оставляешь правильный вариант)
//    - потом:
//      git add .
//      git commit -m "Resolve merge conflict"
//      git push

// -----------------------------------------------------------------------
// C) В процессе работы (сохраняю прогресс)

// 1) Посмотреть, что изменилось:
//    git status

// 2) Зафиксировать изменения:
//    git add .
//    git commit -m "Коротко что сделал"

// git commit --amend --no-edit
// --amend → «переделай последний коммит»
// --no-edit → «оставь сообщение таким же, не трогай его»

//    Примеры сообщений:
//    - "Lab6: fix input parsing"
//    - "Add Polynomial::operator+"
//    - "Refactor queue memory management"

// 3) Отправить на удалённый репозиторий (чтобы на другом компе было):
//    git push

// -----------------------------------------------------------------------
// D) Перехожу на второй комп

// 1) В папке проекта:
//    git pull

// И всё. Код на месте.

// -----------------------------------------------------------------------
// E) Если забыл закоммитить и надо срочно уйти (временное сохранение)

//    git stash
//    git pull          # если нужно обновиться
//    git stash pop     # вернуть изменения обратно

// (Старайся не жить на stash. Это временный карман.)

// -----------------------------------------------------------------------
// F) Откаты (самое частое)

// 1) Отменить незакоммиченные правки:
//    git restore .

// 2) Убрать файлы из staged (после git add):
//    git restore --staged .

// 3) Убрать последний коммит, НО оставить изменения в файлах:
//    git reset --soft HEAD~1

// 4) Убрать последний коммит И выкинуть изменения:
//    git reset --hard HEAD~1

// 5) Если уже запушил и нужно отменить безопасно:
//    git revert <hash>
//    git push

// -----------------------------------------------------------------------
// G) Быстрые проверки

// - Где я? (корень репо)
//   git rev-parse --show-toplevel

// - Что я изменил?
//   git status

// - Какие коммиты последние?
//   git log --oneline --max-count=10

// -----------------------------------------------------------------------
// H) Золотое правило (чтобы не страдать)

// Перед началом работы: git pull
// После завершения работы: git add . && git commit && git push

// =======================================================================
