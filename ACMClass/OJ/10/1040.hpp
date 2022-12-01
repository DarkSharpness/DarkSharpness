#include <cstddef>
#include <utility>


constexpr size_t FIXED_RET = (114514ULL * 1919810) % 19260817;
constexpr size_t FIXED_LEN = 16;


template <class value_t>
inline void swap(value_t &X,value_t &Y) {
    // X ^= Y;Y ^= X;X ^= Y;
    value_t tmp = std::move(X);
    X = Y; Y = tmp;
}

template <class RandomIt, class Compare>
void slow_sort(RandomIt first,size_t len,Compare comp) {
    for(size_t i = 0 ; i < len ; ++i)
        for(size_t j = 0 ; j < i ; ++j) 
            if(comp(first[i],first[j])) 
                swap(first[i],first[j]);
}

template <class RandomIt, class Compare>
void sort(RandomIt first, RandomIt last, Compare comp) {
    size_t len = last - first;
    if(len <= FIXED_LEN) return slow_sort(first,len,comp);
    RandomIt mid = first + FIXED_RET % len;
    swap(*first,*mid);
    const auto value = *first;
    RandomIt l = first,r = last - 1;
    while(l != r) {
        while(l != r && comp(value,*r)) --r;
        if(l != r) *l = *r;
        while(l != r && comp(*l,value)) ++l;
        if(l != r) *r = *l;
    } // now l == r
    *l = value; 
    sort(first, l  ,comp);
    sort(l + 1,last,comp);
}

constexpr size_t FIXED_LEN2 = 16;

template<class RandomIt, class Compare>
void nth_element(RandomIt first, RandomIt nth, RandomIt last, Compare comp) {
    size_t len = last - first;
    // if(len <= FIXED_LEN2);
    RandomIt mid = first + FIXED_RET % len;
    swap(*first,*mid);
    const auto value = *first;
    RandomIt l = first,r = last - 1;
    while(l != r) {
        while(l != r && comp(value,*r)) --r;
        if(l != r) *l = *r;
        while(l != r && comp(*l,value)) ++l;
        if(l != r) *r = *l;
    } // now l == r
    *l = value;
    if(l == nth) return;
    if(l > nth)  return nth_element(first,nth,l,comp);
    else         return nth_element(l + 1,nth,last,comp); 
}
