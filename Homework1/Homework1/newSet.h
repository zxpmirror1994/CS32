#ifndef SET_INCLUDED
#define SET_INCLUDED

#include <iostream>


typedef unsigned long ItemType;
const int DEFAULT_MAX_ITEMS = 200;
class Set
{
public:
    Set(int size);
    
    Set(const Set& other);
    
    Set();
    
    ~Set();
    
    Set& operator = (const Set& other);
    
    bool empty() const;
    
    int size() const;
    
    bool insert(const ItemType& value);
    
    bool erase(const ItemType& value);
    
    bool contains(const ItemType& value) const;
    
    bool get(int i, ItemType& value) const;
    
    void swap(Set& other);
private:
    ItemType* sp;
    int m_size;
    int m_capacity;
};



#endif //  SET_INCLUDED
