#ifndef __SKIPLIST_H
#define __SKIPLIST_H

#include <cmath>
#include <vector>
#include <string>
#include <stack>
#include <utility>

template<typename T>
class skipList
{
    private:
    struct Node
    {
       T data;
       Node* next;
       Node* skip;

       Node(const T& _data, Node* _next):
           data {_data}, next {_next}, skip {nullptr} {}
    };

    Node* start;
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
    std::stack<std::string> shortestPathWithPriorityTowns(std::vector<std::string>& listOfTownsPriority);

    Node* locate(const T& element) const;
    bool member (const T& element) const;
    void optimize();
    void addElementAt(const T& element, Node*& at);
    void addElement(const T& element);
    
    void printSkipList() const;
    void printSkipping() const;

};

template<typename T>
void skipList<T>::addElementAt(const T& element, Node*& at)
{
    if(!at)
    {
        start = new Node(element, start);
    }
    else
    {
        at->next = new Node(element, at->next);
    }

    size++;
}

template<typename T>
void skipList<T>::copy(const skipList& other)
{
    if(!other.start)
    {
        return;
    }

    start = new Node (other.start->data, nullptr);
    Node* prev = start;
    size = 1;

    Node* temp = other.start->next;
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
        Node* prev = start;
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
void skipList<T>::printSkipList() const
{
    Node* temp = start;
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
    Node* temp = start;
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


template<typename T>
void skipList<T>::pushElementInList(T element)
{
    Node* node = new Node(element, nullptr);
    if(start == nullptr)
    {
        start = node;
        return;
    }   

    Node *current = start;
    while(current->next)
    {
        current = current->next;
    }
    current-> next = node;
}

template<typename T>
void skipList<T>::addSkipRelation(T currentTown, T skipTown)
{
    Node* tempCurrentTown = start;
    while(tempCurrentTown->data != currentTown)
    {
       tempCurrentTown = tempCurrentTown->next;
    }
    Node* tempSkipTown = start;
    while(tempSkipTown->data != skipTown)
    {
        tempSkipTown = tempSkipTown->next;
    }
    tempCurrentTown->skip = tempSkipTown;
}

template<typename T>
std::stack<std::string> skipList<T>::shortestPathWithPriorityTowns(std::vector<std::string>& listOfTownsPriority)
{
    std::stack<std::string> path;
    std::vector<std::pair<std::string, std::string>> skips;

    Node* current = start;
    while(current)
    {
        for(std::pair<std::string, std::string> element : skips)
        {
            if(element.second == current->data)
            {
               while(path.top() != element.first)
               {
                  path.pop();
               }
            }
        }
        for(std::string town : listOfTownsPriority)
        {
            if(town == current->data)
            {
                skips.clear();
                break;
            }
        }
        //възможна е оптимизация като трием ненужните скип връзки
        if(current->skip)
        {
            skips.push_back({current->data, current->skip->data});
        }
        path.push(current->data);
        current = current->next;
    }          
    return path;
}

#endif