#include "StudentSet.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    StudentSet s;
    assert(s.size() == 0);
    unsigned long x = 1234567;
    s.add(x);
    assert(s.size() == 1);
    unsigned long y = 456789;
    s.add(y);
    s.print();
    StudentSet d = s;
    d.print();
    StudentSet e(d);
    e.print();
}
