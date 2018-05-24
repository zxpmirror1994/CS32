#include "Set.h"
#include "StudentSet.h"
#include <iostream>
using namespace std;

StudentSet::StudentSet()       // Create an empty student set.
{
}

bool StudentSet::add(unsigned long id)
// Add a student id to the StudentSet.  Return true if and only if the
// id was actually added.
{
    if (m_studentSet.contains(id) || size() == DEFAULT_MAX_ITEMS)
    {
        return false;
    }
    m_studentSet.insert(id);
    return true;
}
int StudentSet::size() const  // Return the number of ids in the StudentSet.
{
    return m_studentSet.size();
}

void StudentSet::print() const
// Print every student id in the StudentSet exactly once, one per line.
{
    for (int i = 0; i < m_studentSet.size(); i++)
    {
        unsigned long dummy;
        if (m_studentSet.get(i, dummy))
        {
            cout << dummy << endl;
        }
    }
}