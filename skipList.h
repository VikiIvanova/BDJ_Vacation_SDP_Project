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

       Box(const T& data, Box* next, Box* skip);
    }
    

};


#endif