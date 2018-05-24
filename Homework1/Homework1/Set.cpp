#include "Set.h"

Set::Set()
:m_size(0)
{
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

bool Set::insert(const ItemType& value)
{
    if (contains(value))
    {
        return false;
    }
    else
    {
        if (size() < 200)
        {
            m_set[size()] = value;
            m_size++;
            return true;
        }
        return false;
    }
}

bool Set::erase(const ItemType& value)
{
    for (int i = 0; i < size(); i++)
    {
        if (m_set[i] == value)
        {
            for (int j = i; j < size(); j++)
            {
                m_set[j] = m_set[j + 1];
            }
            m_size--;
            return true;
        }
    }
    return false;
}

bool Set::contains(const ItemType& value) const
{
    if (empty())
    {
        return false;
    }
    for (int i = 0; i < size(); i++)
    {
        if (m_set[i] == value)
        {
            return true;
        }
    }
    return false;
}

bool Set::get(int i, ItemType& value) const
{
    if (i >= 0 && i < size())
    {
        value = m_set[i];
        return true;
    }
    return false;
}

void Set::swap(Set& other)
{
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        ItemType tempElement = m_set[i];
        m_set[i] = other.m_set[i];
        other.m_set[i] = tempElement;
    }
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
    
}
