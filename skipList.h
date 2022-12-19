#ifndef __SKIPLIST_H
#define __SKIPLIST_H

#include <cmath>

template<typename T>
class skipList
{
    private:
    struct Box
    {
       T data;
       Box* next;
       Box* skip;

       Box(const T& _data, Box* _next):
           data {_data}, next {_next}, skip {nullptr} {}
    };

    Box* start;
    size_t size;

    void clear();
    void copy(const skipList& other);

    public:
    skipList();
    skipList(const skipList& other);
    skipList& operator= (const skipList& other);
    ~skipList();

     size_t getSize() const;
    size_t getNumSkipElemensts() const;
    
    void pushElementInList(T element);
    void addSkipRelation(T currentTown, T skipTown);

    Box* locate(const T& element) const;
    bool member (const T& element) const;
    void optimize();
    void addElementAt(const T& element, Box*& at);
    void addElement(const T& element);
    
    void printSkipList() const;
    void printSkipping() const;

};

template<typename T>
void skipList<T>::pushElementInList(T element)
{
    Box* box = new Box(element, nullptr);
    if(start == nullptr)
    {
        start = box;
        return;
    }   

    Box *current = start;
    while(current->next)
    {
        current = current->next;
    }
    current-> next = box;
}

template<typename T>
void skipList<T>::addSkipRelation(T currentTown, T skipTown)
{
    Box* tempCurrentTown = start;
    while(tempCurrentTown->data != currentTown)
    {
       tempCurrentTown = tempCurrentTown->next;
    }
    Box* tempSkipTown = start;
    while(tempSkipTown->data != skipTown)
    {
        tempSkipTown = tempSkipTown->next;
    }
    tempCurrentTown->skip = tempSkipTown;
}

template<typename T>
void skipList<T>::copy(const skipList& other)
{
    if(!other.start)
    {
        return;
    }

    start = new Box (other.start->data, nullptr);
    Box* prev = start;
    size = 1;

    Box* temp = other.start->next;
    while(temp)
    {
        addElementAt(temp->data, prev);
        prev = prev->next;
        temp = temp->next;
    }
    optimize();
}

template<typename T>
void skipList<T>::clear()
{
    while(start)
    {
        Box* prev = start;
        start = start->next;
        delete prev;
        size--;
    }
}

template<typename T>
skipList<T>::skipList():start{nullptr}, size{0} {}

template<typename T>
skipList<T>::skipList(const skipList& other): start{nullptr}, size{0}
{
   this->copy(other);
}

template<typename T>
skipList<T>::~skipList()
{
    this->clear();
}

template<typename T>
skipList<T>& skipList<T>::operator=(const skipList<T>& other)
{
    if(this != &other)
    {
        this->clear();
        this->copy(other);
    }
    return *this;
}

template<typename T>
size_t skipList<T>::getSize() const
{
    return size;
}

template<typename T>
size_t skipList<T>::getNumSkipElemensts() const
{
    size_t numSkips = 0;
    Box* temp = start;
    while(temp)
    {
        temp = temp->data;
        numSkips++;
    }
    return numSkips;
}

template<typename T>
typename skipList<T>::Box* skipList<T>::locate(const T& element) const
{
    if(!start || start->data > element)
    {
        return nullptr;
    }

    Box* temp = start;
    while(start->skip && temp->skip->data <= element)
    {
        temp = temp->skip;
    }
    
    while(temp->next && temp->next->data <= element)
    {
        temp = temp->next;
    }

    return temp;
}

template<typename T>
bool skipList<T>::member(const T& element) const
{
    Box* locateAt = locate(element);
    return locateAt && locateAt->data == element;
}

template<typename T>
void skipList<T>::optimize()
{
    size_t skipNum = sqrt(size), curNum = 0;
    Box* temp = start->next;
    Box* prevToSkip = start;

    while(temp)
    {
        temp->skip = nullptr;
        curNum++;
        if(curNum % skipNum == 0 || curNum+1 == size)
        {
            prevToSkip->skip = temp;
            prevToSkip = temp;
        }

        temp = temp->next;
    }
}

template<typename T>
void skipList<T>::addElementAt(const T& element, Box*& at)
{
    if(!at)
    {
        start = new Box(element, start);
    }
    else
    {
        at->next = new Box(element, at->next);
    }

    size++;
}

template<typename T>
void skipList<T>::addElement(const T& element)
{
    Box* at = locate(element);
    addElement(element);
    optimize();
}

template<typename T>
void skipList<T>::printSkipList() const
{
    Box* temp = start;
    while(temp)
    {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

template<typename T>
void skipList<T>::printSkipping() const
{
    Box* temp = start;
    while(temp)
    {
        std::cout << temp->data << " ";
        if(temp->skip)
        {
            std::cout << temp->skip->data << " ";
        }
        std::cout << std::endl;
        temp = temp->next;
    }
    std::cout << std::endl;
}



#endif