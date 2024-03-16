#ifndef _BUBBLESORT_
#define _BUBBLESORT_


#include "header.h"

namespace dark {

template <class RandomIt, class Compare>
void bubble_sort(RandomIt first,size_t len,Compare comp) {
    for(size_t i = 0 ; i < len ; ++i)
        for(size_t j = 0 ; j < i ; ++j) 
            if(comp(first[i],first[j])) 
                swap(first[i],first[j]);
}


}

#endif
