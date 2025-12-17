#include "PolyQueue.h"

PolyQueue::~PolyQueue()
{
    Node* current = head;
    Node* next;
    
    unsigned step = 0;
    size_t maxPosibleSteps = capacity;
    
    do
    {
        if(++step > maxPosibleSteps || current == nullptr)
        {
            std::cout << "Предупреждение: деструктору не удалось корректно освободить память!" << std::endl;
            break;
        }
            
        next = current->getNext();
        delete current;
        current = next;

    } while(current != head);
}

void PolyQueue::createQueue(Polynomial& object)
{
    if(!head)
    {
        head = new Node(object);
        tail = head;
        capacity++;
    }
    else
        addObject(object);
}

void PolyQueue::addObject(Polynomial& object)
{
    if(head == nullptr)
    {
        createQueue(object);
        return;
    }

    Node* oldTail = tail;

    tail = new Node(object, capacity++, oldTail, head);
    
    oldTail->setNext(tail);

    head->setPrev(tail);
}

Polynomial& PolyQueue::extractObject()
{
    if(capacity == 0)
        throw EmptyQueueError();

    Polynomial& tempRef = head->getPolynomial(); //Извлекаем многочлен первого узла,
                                                 //его будем возвращать из функции

    if(capacity == 1)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        --capacity;
        return tempRef;
    }

    Node* oldHead = head;   //Запоминаем адрес извлекаемого узла для освобождения памяти

    head = oldHead->getNext();  //Второй теперь первый
    
    head->setPrev(oldHead->getPrev()); //Новый предыдущий элемент для новой головы - хвост 
    tail->setNext(oldHead->getNext()); //Новый следующий элемент для хвоста - новая голова (цекличная очередь)

    delete oldHead;

    --capacity;
    numerate();                         //Обновляем нумерацию

    return tempRef;
}

void PolyQueue::printQueue(std::ostream& fout) const
{
    if(capacity == 0)
        return;
    

    Node* ptrNode = head;   //Указатель для прохода по структуре данных

    unsigned step = 0;
    do
    {   
        if(++step > capacity)
            throw QueueStructureError();
            
        fout << ptrNode->getIndexNumber() << ") ";
        fout << ptrNode->getPolynomial() << std::endl;                  //operator<< для Polynomial/Equations
        
        ptrNode = ptrNode->getNext();                                   //Следующий элемент
    } while (ptrNode != head);
    
}

std::ostream& operator<<(std::ostream& fout, const PolyQueue& object)
{
    object.printQueue(fout);
    return fout;
}

const Polynomial& PolyQueue::operator[](unsigned index)
{
    if(capacity == 0)
        throw EmptyQueueError();

    if(index >= capacity)
        throw OutOfQueueError(index);

    Node* ptrNode = head;

    unsigned step = 0;
    while(ptrNode->getIndexNumber() != index)
    {
        if(++step > capacity)
            throw QueueStructureError();

        ptrNode = ptrNode->getNext();
    }

    return ptrNode->getPolynomial();
}

void PolyQueue::removeNode(unsigned index)
{
    if(index >= capacity)
        throw OutOfQueueError(index);
    
    if(capacity == 0)
        throw EmptyQueueError();

    if(capacity == 1 && index == 0)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        --capacity;
    }


    Node* ptrNode = head;

    unsigned step = 0;
    while(ptrNode->getIndexNumber() != index)
    {
        if(++step > capacity)
            throw QueueStructureError();

        ptrNode = ptrNode->getNext();
    }

    ptrNode->getPrev()->setNext(ptrNode->getNext());    //Игнорируем узел в последовательности
    ptrNode->getNext()->setPrev(ptrNode->getPrev());

    delete ptrNode;

    capacity--;
    numerate();
}

void PolyQueue::numerate()
{    
    if(capacity != 0)         //Если не извлекли все,
    {                           //переписываем нумерацию узлов
        Node* tempPtr = head;   //Указатель для хода по структуре данных
        unsigned index = 0;          //Индекс-нумерация
        do
        {
            if(index >= capacity)
                throw QueueStructureError();

            tempPtr->setIndexNumber(index++);   //Нумеруем
            tempPtr = tempPtr->getNext();       //Переходим к следущему

        } while(tempPtr != head);    
    }
}

void PolyQueue::insertNode(unsigned index, Polynomial& object)
{
    if(index >= capacity)
        throw OutOfQueueError(index);

    if(capacity == 0)
        createQueue(object);
    
    if(index == capacity - 1)   //Вставляем в конец
        addObject(object);

    Node* ptrNode = head;

    unsigned step = 0;
    while(ptrNode->getIndexNumber() != index)
    {
        if(++step > capacity)
            throw QueueStructureError();

        ptrNode = ptrNode->getNext();
    }
    
    Node* newNode = new Node(object, index + 1);

    ptrNode->getNext()->setPrev(newNode);

    newNode->setNext(ptrNode->getNext());
    newNode->setPrev(ptrNode);
    
    ptrNode->setNext(newNode);
    
    capacity++;
    numerate();
}