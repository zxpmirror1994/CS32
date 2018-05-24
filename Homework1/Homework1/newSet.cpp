#include "newSet.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Set::Set(int size)
:m_size(0), m_capacity(size), sp(nullptr)
{
    if (size < 0)
    {
        cerr << "The size of array should be positive" << endl;
        exit(1);
    }
    sp = new ItemType[size];
}

Set::Set(const Set& other)
:m_size(other.m_size), m_capacity(other.m_capacity)
{
    sp = new ItemType[other.m_capacity];
    for (int i = 0; i < m_capacity; i++)
    {
        *(sp + i) = *(other.sp + i);
    }
}

Set::Set()
:m_size(0), m_capacity(DEFAULT_MAX_ITEMS), sp(nullptr)
{
    sp = new ItemType[DEFAULT_MAX_ITEMS];
}

Set::~Set()
{
    cerr << "Destructor" << endl;
    delete [] sp;
}

Set& Set::operator = (const Set &rhs)
{
    if (this != &rhs)
    {
        delete sp;
        sp = new ItemType[rhs.m_capacity];
        for (int i = 0; i < m_capacity; i++)
        {
            *(sp + i) = *(rhs.sp + i);
        }
        m_capacity = rhs.m_capacity;
        m_size = rhs.m_size;
    }
    return *this;
}

bool Set::empty() const
{
    if (m_size == 0)
    {
        return true;
    }
    return false;
}

int Set::size() const
{
    return m_size;
}

bool Set::insert(const ItemType &value)
{
    if (contains(value))
    {
        return false;
    }
    else
    {
        if (size() < m_capacity)
        {
            *(sp + size()) = value;
            m_size++;
            return true;
        }
        return false;
    }
}

bool Set::erase(const ItemType &value)
{
    for (int i = 0; i < size(); i++)
    {
        if (*(sp + i) == value)
        {
            for (int j = i; j < m_capacity; j++)
            {
                *(sp + j) = *(sp + j + 1);
            }
            m_size--;
            return true;
        }
    }
    return false;
}

bool Set::contains(const ItemType &value) const
{
    if (empty())
    {
        return false;
    }
    else
    {
        for (int i = 0; i < size(); i++)
        {
            if (*(sp + i) == value)
            {
                return true;
            }
        }
    }
    return false;
}

bool Set::get(int i, ItemType &value) const
{
    if (i >= 0 && i < size())
    {
        value = *(sp + i);
        return true;
    }
    return false;
}

void Set::swap(Set& other)
{
    Set tempSet(other);
    other = *this;
    *this = tempSet;
}