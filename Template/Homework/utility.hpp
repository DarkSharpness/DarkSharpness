#ifndef SJTU_UTILITY_HPP
#define SJTU_UTILITY_HPP

#include <utility>

namespace sjtu {

template<class T1, class T2>
class pair {
  public:
	T1 first;
	T2 second;

    /* Empty construction. */
	constexpr pair() : first() , second() {}
	pair(pair &&other) = default;
	pair(const pair &other) = default;

    pair(T1 &&x) : first(std::move(x)) , second() {}
    pair(const T1 &x) : first(x) , second() {}

    /* Directly copy. */
	pair(const T1 &x, const T2 &y) : first(x), second(y) {}
    /* Perfect forwarding. */
	template<class U1, class U2>
	pair(U1 &&x, U2 &&y) :
        first(std::forward <U1> (x)), second(std::forward <U2> (y)) {}

    /* Copy content. */
	template<class U1, class U2>
	pair(const pair <U1, U2> &other) : 
        first(other.first), second(other.second) {}
	template<class U1, class U2>
    /* Move content. */
	pair(pair <U1, U2> &&other) : 
        first(std::move(other.first)), second(std::move(other.second)) {}
    ~pair() noexcept = default;

    
};

}

#endif
