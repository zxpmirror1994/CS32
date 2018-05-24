#include "Set.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
    Set<int> si;
    Set<string> ss;
    assert(si.empty());
    assert(ss.size() == 0);
    assert(si.insert(10));
    assert(ss.insert("hello"));
    assert(si.contains(10));
    assert(si.erase(10));
    string s;
    assert(ss.get(0, s)  &&  s == "hello");
    Set<string> ss2(ss);
    ss.swap(ss2);
    ss = ss2;
    unite(si,si,si);
    unite(ss,ss2,ss);
    subtract(si,si,si);
    subtract(ss,ss2,ss);
    cout << "Passed";
}
