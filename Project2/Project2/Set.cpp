#include "Set.h"

//Create a node pointed by m_head and a node pointed by m_tail
//m_previous of the m_head-pointing node and m_next of the m_tail-pointing node are null pointers
//m_next of the m_head-pointing node points to the m_tail-pointing node
//m_previous of the m_tail-pointing node points to the m_head-pointing node
Set::Set()
:m_size(0)
{
    m_head = new Node;
    m_tail = new Node;
    m_head->m_previous = nullptr;
    m_tail->m_next = nullptr;
    m_head->m_next = m_tail;
    m_tail->m_previous = m_head;
}

//Copy the size
Set::Set(const Set& other)
:m_size(other.m_size)
{
    m_head = new Node;
    m_tail = new Node;
    m_head->m_previous = nullptr;
    m_tail->m_next = nullptr;
    //If other is an empty set, operate as a default constructor
    m_head->m_next = m_tail;
    m_tail->m_previous = m_head;
    
    //If other is not empty, use a pointer p to get each node in other
    //Create a new node with the same value of the node pointed by p
    //Insert the node into the set

    Node* p = other.m_head->m_next;
    Node* index = m_head;
    for (; p->m_next != nullptr; p = p->m_next)
    {
        Node* q = new Node;
        q->m_value = p->m_value;
        index->m_next->m_previous = q;
        q->m_next = index->m_next;
        index->m_next = q;
        q->m_previous = index;
        index = q;
    }
}

Set& Set::operator=(const Set &rhs)
{
    if (this != &rhs)
    {
        Set temp(rhs);
        swap(temp);
    }
    return *this;
}

Set::~Set()
{
    delete m_head;
    delete m_tail;
}

int Set::size() const
{
    return m_size;
}

bool Set::empty() const
{
    return m_head->m_next == m_tail && m_tail->m_previous == m_head;
}

bool Set::contains(const ItemType &value) const
{
    return find(value)->m_next != nullptr;
}

//If this set already contains value, return false
//Otherwise, create a new node and link it with the node before it and the node after it
//If this set is empty before inserting the value, link the new node with the dummy nodes pointed by m_head and m_tail
//Adjust the size of the set
bool Set::insert(const ItemType& value)
{
    Node* newNode = new Node;
    if (!contains(value))
    {
        newNode->m_value = value;
        m_head->m_next->m_previous = newNode;
        newNode->m_next = m_head->m_next;
        m_head->m_next = newNode;
        newNode->m_previous = m_head;
        m_size++;
        return true;
    }
    return false;
}

//Use the find function to get a pointer pointing to the node containing the intended value
//If not found, return false
//If found, adjust the size, link the node before the erased and the node after it
bool Set::erase(const ItemType& value)
{
    Node* p = find(value);
    if (p->m_next == nullptr)
    {
        return false;
    }
    m_size--;
    p->m_previous->m_next = p->m_next;
    p->m_next->m_previous = p->m_previous;
    delete p;
    return true;
    
}

//Return false if empty
//Otherwise, get the value of the node by a pointer from 0th to posth
bool Set::get(int pos, ItemType& value) const
{
    if (pos >= 0 && pos < size())
    {
        Node* p = m_head->m_next;
        while (pos > 0)
        {
            p = p->m_next;
            pos--;
        }
        value = p->m_value;
        return true;
    }
    return false;
}

//Swapping two doubly-linked list means swapping their m_head, m_tail and m_size
void Set::swap(Set& other)
{
    //Swap m_head and m_tail
    Node* tempHead = m_head;
    Node* tempTail = m_tail;
    m_head = other.m_head;
    m_tail = other.m_tail;
    other.m_head = tempHead;
    other.m_tail = tempTail;
    
    
    //Swap m_size
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
    
}

//Find the position of the node with m_value == value
//this function returns nullptr if the set is an empty set or if the set does not contain that value
Set::Node* Set::find(const ItemType &value) const
{
    Node* p = m_head->m_next;
    for (; p->m_next != nullptr && p->m_value != value; p = p->m_next)
    {
        ;
    }
    return p;
}



void unite(const Set& s1, const Set& s2, Set& result)
{
    ItemType value;
    int n = result.size();
    int eraseTime = 0;
    int pos = 0;
    while (pos < n - eraseTime)
    {
       if (result.get(pos, value))
        {
            if (!s1.contains(value) && !s2.contains(value))
            {
                result.erase(value);
                eraseTime++;
                pos = 0;
                continue;
            }
            pos++;
            continue;
        }
    }
    //If s1 and s2 do not contain the value in result, erase that value from result
    ItemType value_s1;
    for (int pos_s1 = 0; pos_s1 < s1.size(); pos_s1++)
    {
        if (s1.get(pos_s1, value_s1))
            if (!result.contains(value_s1))
            {
                result.insert(value_s1);
            }
    }
    //If s1 contains a value not contained by result, insert that value into result
    ItemType value_s2;
    for (int pos_s2 = 0; pos_s2 < s2.size(); pos_s2++)
    {
        if (s2.get(pos_s2, value_s2))
            if (!result.contains(value_s2))
            {
                result.insert(value_s2);
            }
    }
    //If s2 contains a value not contained by result, insert that value int result
}

void subtract(const Set& s1, const Set& s2, Set& result)
{
    ItemType value;
    int n = result.size();
    int eraseTime = 0;
    int pos = 0;
    while (pos < n - eraseTime)
    {
        if (result.get(pos, value))
        {
            if (!s1.contains(value) || s2.contains(value))
            {
                result.erase(value);
                eraseTime++;
                pos = 0;
                continue;
            }
            pos++;
            continue;
        }
    }
    //If a value in result is contained by s2 or not contained by s2, erase that value from result
    ItemType value_s1;
    for (int pos_s1 = 0; pos_s1 < s1.size(); pos_s1++)
    {
        if (s1.get(pos_s1, value_s1))
            if (!s2.contains(value_s1) && !result.contains(value_s1))
            {
                result.insert(value_s1);
            }
    }
    //If s2 and result both do not contain the value in s1, insert that value into result
}