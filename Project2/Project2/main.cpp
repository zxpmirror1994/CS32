#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

#define CHECKTYPE(f, t) { auto p = (t)(f); (void)p; }

void thisFunctionWillNeverBeCalled()
{
    Set();
    (Set(Set()));
    CHECKTYPE(&Set::operator=, Set& (Set::*)(const ItemType&));
    CHECKTYPE(&Set::empty,     bool (Set::*)() const);
    CHECKTYPE(&Set::size,      int  (Set::*)() const);
    CHECKTYPE(&Set::insert,    bool (Set::*)(const ItemType&));
    CHECKTYPE(&Set::erase,     bool (Set::*)(const ItemType&));
    CHECKTYPE(&Set::contains,  bool (Set::*)(const ItemType&) const);
    CHECKTYPE(&Set::get,       bool (Set::*)(int, ItemType&) const);
    CHECKTYPE(&Set::swap,      void (Set::*)(Set&));
    CHECKTYPE(unite,    void (*)(const Set&, const Set&, Set&));
    CHECKTYPE(subtract, void (*)(const Set&, const Set&, Set&));
}

void test()
{
    
}

int main()
{
    
    Set ss;
    assert(ss.insert("roti"));
    assert(ss.insert("pita"));
    assert(ss.size() == 2);
    assert(ss.contains("pita"));
    ItemType x = "focaccia";
    assert(ss.get(0, x)  &&  (x == "roti"  ||  x == "pita"));
    
    Set new_s1;
    Set new_s2;
    Set new_result;
    unite(new_s1, new_s2, new_result);
    assert(new_s1.size() == 0 && new_s2.size() == 0 && new_result.size() == 0);
    
    new_s1.insert("ucla");
    new_s1.insert("usc");
    new_s1.insert("ucb");
    new_s1.insert("ucsd");
    new_s1.insert("ucla");
    assert(new_s1.size() == 4);
    
    //unite function
    unite(new_s1, new_s2, new_result);
    assert(new_result.size() == 4 && new_result.contains("ucla") && new_result.contains("usc") && new_result.contains("ucb") && new_result.contains("ucsd"));
    
    new_result.erase("ucla");
    new_result.erase("usc");
    assert(new_result.size() == 2);
    new_result.insert("ucsb");
    
    //copy constructor
    Set new_copy1(new_result);
    assert(new_copy1.size() == 3);
    
    //assignment operator
    Set new_copy2 = new_result;
    
    //subtract function

    subtract(new_s1, new_copy1, new_result);
    assert(new_result.size() == 2 && new_result.contains("ucla") && new_result.contains("usc"));
    
    unite(new_copy2, new_s1, new_s2);
    assert(new_s2.size() == 5);
    
    subtract(new_copy2, new_s2, new_result);
    assert(new_result.empty());
    
    unite(new_s1, new_s1, new_result);
    assert(new_result.size() == 4);
    
    subtract(new_s1, new_s1, new_result);
    assert(new_result.empty());
    
    cout << "Passed all tests" << endl;
}