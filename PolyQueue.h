#ifndef POLY_QUEUE_H
#define POLY_QUEUE_H

#include <iostream>
#include "Polynomial.h"
#include "PolyError.h"

struct Node
{
private:
    Polynomial &object;
    unsigned indexNumber;
    Node* prev;
    Node* next;
    
public:
    Node(Polynomial& obj, unsigned indexNumber = 0, Node* prev = nullptr, Node* next = nullptr)
        : object(obj),
          indexNumber(indexNumber),
          prev(prev ? prev : this),
          next(next ? next : this)
        {                 }

    void setNext(Node* newNext)
        { next = newNext; }
    void setPrev(Node* newPrev)
        { prev = newPrev; }
    void setIndexNumber(int index)
        { indexNumber = index; }

    Node* getPrev() const
        { return prev;    }
    Node* getNext() const
        { return next;    }
    Polynomial& getPolynomial() const
        { return object;  }
    unsigned getIndexNumber() const
        { return indexNumber;  }
};

struct PolyQueue
{
private:
    Node* head;
    Node* tail;

    unsigned capacity = 0;

public:
    PolyQueue(): head(nullptr), tail(nullptr)
        {   }
    ~PolyQueue();

    void createQueue(Polynomial& object);

    void addObject(Polynomial& object);

    Polynomial& extractObject();

    void printQueue(std::ostream& fout = std::cout) const;

    friend std::ostream& operator<<(std::ostream& fout, const PolyQueue& object);

    const Polynomial& operator[](unsigned index);

    void numerate();

    //Далее не характерные для очереди функции, но пристуствующие в задании
   
    void removeNode(unsigned index);        //Удаление из очереди по индексу
    void insertNode(unsigned index, Polynomial& object);        //Вставка на следующую за index позицию
    
};


#endif