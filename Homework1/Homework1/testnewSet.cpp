#include "newSet.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Set a(1000);   // a can hold at most 1000 distinct items
    Set b(5);      // b can hold at most 5 distinct items
    Set c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
    ItemType v[6] = {1234, 4455, 6677, 8899, 4231, 2313};
    
    // No failures inserting 5 distinct items into b
    for (int k = 0; k < 5; k++)
        assert(b.insert(v[k]));
    
    Set d = b;
    Set e(b);
    assert(d.size() == e.size());
    e.erase(1234);
    assert(e.size() == 4);
    e.erase(2132);
    assert(e.size() == 4);
    // Failure if we try to insert a sixth distinct item into b
    assert(!b.insert(v[5]));
    
    // When two Sets' contents are swapped, their capacities are swapped
    // as well:
    a.swap(b);
    assert(!a.insert(v[5]));
    cout << "Passed All Tests" << endl;
}