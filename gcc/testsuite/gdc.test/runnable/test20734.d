/*
REQUIRED_ARGS: -betterC -preview=dip1000
*/

__gshared int numDtor;

struct S
{
    int a;
    ~this() nothrow @nogc @trusted { ++numDtor; }
}

void takeScopeSlice(const scope S[] slice) nothrow @nogc @safe {}

extern(C) int main() nothrow @nogc @safe
{
    takeScopeSlice([ S(1), S(2) ]); // @nogc => no GC allocation
    (() @trusted { assert(numDtor == 2); })(); // stack-allocated array literal properly destructed
    return 0;
}

// https://issues.dlang.org/show_bug.cgi?id=23098
void f23098(scope inout(int)[] d) @safe {}

void test23098() @safe
{
    f23098([10, 20]);
}
