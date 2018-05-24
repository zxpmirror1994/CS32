#ifndef STUDENTSET_INCLUDED
#define STUDENTSET_INCLUDED
#include "Set.h"

class StudentSet
{
public:
    StudentSet();       // Create an empty student set.
    
    bool add(unsigned long id);
    // Add a student id to the StudentSet.  Return true if and only if the
    // id was actually added.
    
    int size() const;  // Return the number of ids in the StudentSet.
    
    void print() const;
    // Print every student id in the StudentSet exactly once, one per line.
    
private:
    // Some of your code goes here.
    Set m_studentSet;
};

#endif   //STUDENTSET_INCLUDED