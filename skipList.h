#ifndef __SKIPLIST_H
#define __SKIPLIST_H

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
    ~skipList();

    skipList& operator= (const skipList& other);

    size_t getSize() const;
    size_t getNumSkipElemensts() const;
    
    Box* locate(const T& element) const;
    bool member (const T& element) const;
    void optimize();
    void addElementAt(const T& element, Box*& at);
    void addElement(const T& element);

    void printSkipList() const;
    void printSkipping() const;

};


#endif