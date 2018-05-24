#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Set s;
    Set d = s;
    assert(d.empty());
    assert(s.empty());
    unsigned long x = 9876543;
    assert( !s.get(42,x)  &&  x == 9876543); // x unchanged by get failure
    s.insert(123456789);
    assert(s.size() == 1);
    assert(s.get(0,x)  &&  x == 123456789);
    assert(s.contains(x));
    assert(s.erase(x) && s.size() == 0);
    Set e(s);
    assert(e.empty());
    
    cout << "Passed all tests" << endl;
}