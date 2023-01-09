#ifndef __SKIPLIST_H
#define __SKIPLIST_H

#include <cmath>
#include <vector>
#include <string>
#include <stack>
#include <utility>

template <typename T>
class skipList
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node *skip;

        Node(const T &_data, Node *_next) : data{_data}, next{_next}, skip{nullptr} {}
    };

    Node *start;
    size_t size;

    void clear();
    void copy(const skipList &other);

public:
    skipList();
    skipList(const skipList &other);
    skipList &operator=(const skipList &other);
    ~skipList();

    void pushElementInList(T element);
    void addSkipRelation(T currentTown, T skipTown);
    std::stack<std::string> shortestPathWithPriorityCities(std::vector<std::string> &listOfTownsPriority);

    void addElement(const T &element);

    void printSkipList() const;
    void printSkipping() const;
};

// helper function
template <typename T>
void skipList<T>::copy(const skipList &other)
{
    if (!other.start)
    {
        return;
    }

    start = new Node(other.start->data, nullptr);
    Node *prev = start;
    size = 1;

    Node *temp = other.start->next;
    while (temp)
    {
        if (!prev)
        {
            start = new Node(temp->data, start);
        }
        else
        {
            prev->next = new Node(temp->data, prev->next);
        }
        size++;
        prev = prev->next;
        temp = temp->next;
    }
}

// helper function
template <typename T>
void skipList<T>::clear()
{
    while (start)
    {
        Node *prev = start;
        start = start->next;
        delete prev;
        size--;
    }
}

// constructor
template <typename T>
skipList<T>::skipList() : start{nullptr}, size{0} {}

// copy constructor
template <typename T>
skipList<T>::skipList(const skipList &other) : start{nullptr}, size{0}
{
    this->copy(other);
}

// destructor
template <typename T>
skipList<T>::~skipList()
{
    this->clear();
}

// operator=
template <typename T>
skipList<T> &skipList<T>::operator=(const skipList<T> &other)
{
    if (this != &other)
    {
        this->clear();
        this->copy(other);
    }
    return *this;
}

// Print function for listing all cities
template <typename T>
void skipList<T>::printSkipList() const
{
    Node *temp = start;
    while (temp)
    {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

// Print function for the pairs of cities with skip relation
template <typename T>
void skipList<T>::printSkipping() const
{
    Node *temp = start;
    while (temp)
    {
        std::cout << temp->data << " ";
        if (temp->skip)
        {
            std::cout << temp->skip->data << " ";
        }
        std::cout << std::endl;
        temp = temp->next;
    }
    std::cout << std::endl;
}

// Add element in list
template <typename T>
void skipList<T>::pushElementInList(T element)
{
    Node *node = new Node(element, nullptr);
    if (start == nullptr)
    {
        start = node;
        return;
    }

    Node *current = start;
    while (current->next)
    {
        current = current->next;
    }
    current->next = node;
}

// Function for add skip relation
template <typename T>
void skipList<T>::addSkipRelation(T currentTown, T skipTown)
{
    Node *tempCurrentTown = start;
    while (tempCurrentTown->data != currentTown)
    {
        tempCurrentTown = tempCurrentTown->next;
    }
    Node *tempSkipTown = start;
    while (tempSkipTown->data != skipTown)
    {
        tempSkipTown = tempSkipTown->next;
    }
    tempCurrentTown->skip = tempSkipTown;
}

// Function to find the shortest path passing throught the cities from the list of Anq and Vankata
template <typename T>
std::stack<std::string> skipList<T>::shortestPathWithPriorityCities(std::vector<std::string> &listOfCitiesPriority)
{
    std::stack<std::string> path;
    // in the vector keep pair of the start and end cities of the skip relation
    std::vector<std::pair<std::string, std::string>> skips;

    Node *current = start;
    while (current)
    {
        // Remove unnecessary cities from the path if we found a link
        // that we can use without missing cities from Anya and Vanka's list
        for (std::pair<std::string, std::string> element : skips)
        {
            if (element.second == current->data)
            {
                while (path.top() != element.first)
                {
                    path.pop();
                }
            }
        }
        // If the current city is one of the list, delete the vector of links because we won't be able to use them
        for (std::string town : listOfCitiesPriority)
        {
            if (town == current->data)
            {
                skips.clear();
                break;
            }
        }
        // If the current city has a skip link, add it to the vector
        if (current->skip)
        {
            skips.push_back({current->data, current->skip->data});
        }
        path.push(current->data);
        current = current->next;
    }
    return path;
}

#endif