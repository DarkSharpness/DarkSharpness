void print(const dynamic_bitset &a) {
    std::cout << "Size: " << a.size() << " | ";
    for (std::size_t i = 0 ; i != a.size() ; ++i) std::cout << a[i];
    std::cout << '\n';
}


template <class T>
void print_detail(const T &a) {
    std::cout
        << "Size: " << a.size() << " | "
                    << a.none() << " | " 
                    << a.all()  << " | ";
    for (std::size_t i = 0 ; i != a.size() ; ++i) std::cout << a[i];
    std::cout << '\n';
}

/**
 * @brief This is intended to avoid hack in the contest.
 * Because in ACMOJ, if CE, the compiler output will be shown.
 * Therefore, some bad guys may use this to hack data.
 * We use concept to protect the safety.
 * 
 * If CE, the compiler will output the concept definition.
 * No information shall be leaked.
 */
template <typename T>
concept check = requires(T a) {
    { a.size() }    -> std::same_as <std::size_t>;
    { a.none() }    -> std::same_as <bool>;
    { a.all()  }    -> std::same_as <bool>;

    { a.set() }     -> std::same_as <dynamic_bitset &>;
    { a.flip()  }   -> std::same_as <dynamic_bitset &>;
    { a.reset() }   -> std::same_as <dynamic_bitset &>;

    { a |= a }      -> std::same_as <dynamic_bitset &>;
    { a &= a }      -> std::same_as <dynamic_bitset &>;
    { a ^= a }      -> std::same_as <dynamic_bitset &>;

    { a <<= 1 }     -> std::same_as <dynamic_bitset &>;
    { a >>= 1 }     -> std::same_as <dynamic_bitset &>;

    { a[0] }            -> std::same_as <bool>;
    { a.set(0) }        -> std::same_as <dynamic_bitset &>;
    { a.set(0, 0) }     -> std::same_as <dynamic_bitset &>;
    { a.push_back(0) }  -> std::same_as <dynamic_bitset &>;
} && std::constructible_from <dynamic_bitset, T>
  && std::constructible_from <dynamic_bitset, std::size_t>
  && std::is_copy_constructible_v <T>
  && std::is_default_constructible_v <T>
  && std::is_copy_assignable_v <T>;


static_assert(sizeof(std::size_t) == 8);
std::size_t my_rand() {
    static std::size_t seed = 1919810 ^ 114514;
    return seed = ((seed ^ std::size_t{1919810}) * std::size_t{415}) ^ (seed >> 14) ^ std::size_t{1};
}
