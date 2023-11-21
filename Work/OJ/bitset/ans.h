#include <vector>       // std::vector
#include <cstring>      // std::memset
#include <climits>      // CHAR_BIT
#include <cstdint>      // std::uint64_t
#include <iostream>     // std::string && debug use
#include <algorithm>    // std::min

struct dynamic_bitset {
  private:
    using ll = std::uint64_t;
    inline static constexpr std::size_t Bits = sizeof(ll) * CHAR_BIT;

    std::vector <ll> data   {}; // 初始化为空
    std::size_t length      {}; // 初始化为 0

    // 最低 n 位为 1 ，其余为 0
    static ll mask_low (std::size_t n) { return (ll(1) << n) - 1; }
    // 最低 n 位为 0 ，其余为 1
    static ll mask_high(std::size_t n) { return ll(-1) << n ; }

    // 向上取整
    static ll round_up(std::size_t n) { return (n + Bits - 1) / Bits; }

    // 把最高位的 1 之后的位全部置 0
    dynamic_bitset &check() {
        const std::size_t mod = length % Bits;
        if (mod) data.back() &= mask_low(mod);
        return *this;
    }

  public:
    dynamic_bitset() noexcept = default;
    ~dynamic_bitset() noexcept = default;

    dynamic_bitset(const dynamic_bitset &) = default;
    dynamic_bitset &operator = (const dynamic_bitset &) = default;

    dynamic_bitset(dynamic_bitset &&) noexcept = default;
    dynamic_bitset &operator = (dynamic_bitset &&) noexcept = default;

    dynamic_bitset(std::size_t n) : data(round_up(n)), length(n) {}

    // string_view 几乎就是 const std::string & 的替代品，更加灵活
    dynamic_bitset(std::string_view str) : dynamic_bitset(str.size()) {
        for (std::size_t i = 0 ; i != str.size() ; ++i)
            data[i / Bits] |= ll(str[i] - '0') << (i % Bits);
    }

    bool none() const {
        for (std::size_t i = 0 ; i != data.size() ; ++i)
            if (data[i] != 0) return false;
        return true;
    }

    bool all() const {
        if (data.empty()) return true;
        for (std::size_t i = 0 ; i != data.size() - 1 ; ++i)
            if (data[i] != ll(-1)) return false;
        const std::size_t mod = length % Bits;
        return mod ? (data.back() == mask_low(mod)) : (data.back() == ll(-1));
    }

    bool operator [] (std::size_t n) const {
        const std::size_t div = n / Bits;
        const std::size_t mod = n % Bits;
        return (data[div] >> mod) & 1;
    }

    std::size_t size() const { return length; }

    dynamic_bitset &operator |= (const dynamic_bitset &rhs) {
        const std::size_t len = std::min(length, rhs.length);
        const std::size_t div = len / Bits;
        const std::size_t mod = len % Bits;
        for (std::size_t i = 0 ; i != div ; ++i) data[i] |= rhs.data[i];
        if (mod) data[div] |= rhs.data[div] & mask_low(mod);
        return *this;
    }

    dynamic_bitset &operator &= (const dynamic_bitset &rhs) {
        const std::size_t len = std::min(length, rhs.length);
        const std::size_t div = len / Bits;
        const std::size_t mod = len % Bits;
        for (std::size_t i = 0 ; i != div ; ++i) data[i] &= rhs.data[i];
        if (mod) data[div] &= rhs.data[div] | mask_high(mod);
        return *this;
    }

    dynamic_bitset &operator ^= (const dynamic_bitset &rhs) {
        const std::size_t len = std::min(length, rhs.length);
        const std::size_t div = len / Bits;
        const std::size_t mod = len % Bits;
        for (std::size_t i = 0 ; i != div ; ++i) data[i] ^= rhs.data[i];
        if (mod) data[div] ^= rhs.data[div] & mask_low(mod);
        return *this;
    }

    dynamic_bitset &operator <<= (std::size_t n) {
        length += n;
        const std::size_t div = n / Bits;
        const std::size_t mod = n % Bits;
        data.insert(data.begin(), div, 0);
        if (mod) {
            ll  carry   = 0;
            for (std::size_t i = div ; i != data.size() ; ++i) {
                ll &dat = data[i];
                ll  tmp = dat >> (Bits - mod);
                dat     = (dat << mod) | carry;
                carry   = tmp;
            }
            if (round_up(length) != data.size()) data.push_back(carry);
        } return *this;
    }

    dynamic_bitset &operator >>= (std::size_t n) {
        if (n >= length) { length = 0; data.clear(); return *this; }
        length -= n;
        const std::size_t div = n / Bits;
        const std::size_t mod = n % Bits;
        data.erase(data.begin(), data.begin() + div);
        if (mod) {
            ll  carry   = 0;
            for (std::size_t i = data.size() ; i != 0 ; --i) {
                ll &dat = data[i - 1];
                ll  tmp = dat << (Bits - mod);
                dat     = (dat >> mod) | carry;
                carry   = tmp;
            }
            if (round_up(length) != data.size()) data.pop_back();
        } return *this;
    }

    dynamic_bitset &set() {
        std::memset(data.data(), -1, data.size() * sizeof(ll));
        return check();
    }

    dynamic_bitset &flip() {
        for (std::size_t i = 0 ; i != data.size() ; ++i) data[i] = ~data[i];
        return check();
    }

    dynamic_bitset &reset() {
        std::memset(data.data(), 0, data.size() * sizeof(ll));
        return *this;
    }

    dynamic_bitset &set(std::size_t n, bool val = true) {
        const std::size_t div = n / Bits;
        const std::size_t mod = n % Bits;
        if (val) data[div] |=   ll(1) << mod;
        else     data[div] &= ~(ll(1) << mod);
        return *this;
    }

    dynamic_bitset &push_back(bool val) {
        if (length % Bits == 0) data.push_back(val);
        else data.back() |= ll(val) << (length % Bits);
        ++length;
        return *this;
    }
};
