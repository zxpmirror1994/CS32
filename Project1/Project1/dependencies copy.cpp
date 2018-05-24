#if 0
....
....
....
#endif

//include guard
#ifndef POINT_INCLUDED
#define POINT_INCLUDED
....
....
....
#endif   //POINT_INCLUDED

//it's harmless to declare functions more than once
void f();
void f();
void f();

//it's illegal to declare classes more than once within the same file
struct Blah
{
    int x;
};

struct Blah
{
    int x;
};

//Don't implement non-inline functions in .h files

//Don't #include .cpp files

//Every header should be protected with include guards
