#include <bits/stdc++.h>
#include <string>
#include <new>
#include <cstdio>
#include <cstdlib>

std::size_t allocated = 0;

void* operator new (size_t sz)
{
    void* p = std::malloc(sz);
    allocated += sz;
    return p;
}

void operator delete(void* p) noexcept
{
    return std::free(p);
}

signed main() {
    allocated = 0;
    std::string s("length is 15   ");
    std::printf("stack space = %zu, heap space = %zu, capacity = %zu, size = %zu\n",
     sizeof(s), allocated, s.capacity(), s.size());
}