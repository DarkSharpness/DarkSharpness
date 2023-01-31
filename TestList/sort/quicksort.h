#ifndef _QUICKSORT_
#define _QUICKSORT_

#include "bubblesort.h"
#include <stdlib.h>


namespace dark {


constexpr size_t FIXED_LEN = 32;

template <class RandomIt, class Compare>
void quick_sort(RandomIt first, RandomIt last, Compare comp) {
    size_t len = last - first;
    if(len <= FIXED_LEN) return bubble_sort(first,len,comp);
    RandomIt mid = first + rand() % len;
    swap(*first,*mid);
    const auto value = *first;
    RandomIt l = first,r = last - 1;
    while(l != r) {
        while(l != r && !comp(*r,value)) --r;
        if(l != r) *l = *r;
        while(l != r && !comp(value,*l)) ++l;
        if(l != r) *r = *l;
    } // now l == r
    *l = value; 
    quick_sort(first, l  ,comp);
    quick_sort(l + 1,last,comp);
}



}

#endif
