// SymbolTable.cpp

// This is a correct but inefficient implementation of
// the SymbolTable functionality.

#include "SymbolTable.h"
#include <iostream>
#include <string>
#include <list>
using namespace std;

const int MAX_NUM_BUCKETS = 500;



// This class does the real work of the implementation.

class SymbolTableImpl
{
public:
    void enterScope();
    bool exitScope();
    bool declare(const string& id, int lineNum);
    int find(const string& id);
private:
    struct Node
    {
        Node(string iden, int num, int currentDepth): id(iden), lineNum(num),depth(currentDepth){}
        
        string id;
        int lineNum;
        int depth;
    };
    
    unsigned int hash(const string& key) const;
    
    list<Node> m_array[MAX_NUM_BUCKETS];
    int currentDepth = 0;
};

unsigned int SymbolTableImpl::hash(const string& key) const
{
    unsigned int h = 2166136261u;
    
    for (int k = 0; k != key.size(); k++)
    {
        h += key[k];
        h *= 16777619;
    }
    return (h % MAX_NUM_BUCKETS);
}

void SymbolTableImpl::enterScope()
{
    currentDepth++;
    return;
}

bool SymbolTableImpl::exitScope()
{
    if (currentDepth == 0)
    {
        return false;
    }
    // Remove ids back to the last scope entry.
    
    for (int k = 0; k < MAX_NUM_BUCKETS; k++)
    {
        if (m_array[k].size() == 0)
        {
            continue;
        }
        while (m_array[k].back().depth == currentDepth)
        {
            m_array[k].pop_back();
        }
    }
    
    currentDepth--;
    return true;
}

bool SymbolTableImpl::declare(const string& id, int lineNum)
{
    if (id.empty())
    {
        return false;
    }
    
    // Check for another declaration in the same scope.
    // Return if found, break out if encounter the scope
    // entry marker.
    
    
    unsigned int k = hash(id);
    if (m_array[k].size() == 0)
    {
        m_array[k].push_back(Node(id, lineNum, currentDepth));
        return true;
    }
    
    list<Node>::iterator p = m_array[k].end();
    while (p != m_array[k].begin())
    {
        p--;
        if (p->depth != currentDepth)
        {
            break;
        }
        if (currentDepth == p->depth && p->id == id)
        {
            return false;
        }
    }
    
    // Save the declaration
    
    m_array[k].push_back(Node(id, lineNum, currentDepth));
    return true;
}

int SymbolTableImpl::find(const string& id)
{
    if (id.empty())
    {
        return -1;
    }
    
    // Search back for the most recent declaration still
    // available.
    
    unsigned int k = hash(id);
    
    list<Node>::iterator p = m_array[k].end();
    while (p != m_array[k].begin())
    {
        p--;
        if (p->id == id)
            return p->lineNum;
    }
    return -1;
}


//*********** SymbolTable functions **************

// For the most part, these functions simply delegate to SymbolTableImpl's
// functions.

SymbolTable::SymbolTable()
{
    m_impl = new SymbolTableImpl;
}

SymbolTable::~SymbolTable()
{
    delete m_impl;
}

void SymbolTable::enterScope()
{
    m_impl->enterScope();
}

bool SymbolTable::exitScope()
{
    return m_impl->exitScope();
}

bool SymbolTable::declare(const string& id, int lineNum)
{
    return m_impl->declare(id, lineNum);
}

int SymbolTable::find(const string& id) const
{
    return m_impl->find(id);
}
