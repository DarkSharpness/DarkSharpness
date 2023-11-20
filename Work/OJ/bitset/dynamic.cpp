#include <bitset>
#include <vector>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <algorithm>

struct dynamic_bitset {
    using ull = unsigned long long;

    inline static constexpr std::size_t _Bits = sizeof(ull) * CHAR_BIT;

    std::vector <ull> data;
    std::size_t length  {};

    struct reference {
        ull *ptr {}; ull pos {};
        explicit reference(ull *__ptr, ull __pos) noexcept {
            ptr = __ptr + __pos / _Bits;
            pos = __pos % _Bits;
        }

        void set(bool __val) noexcept {
            if (__val) *ptr |=  (ull {1} << pos);
            else       *ptr &= ~(ull {1} << pos);
        }

        void flip() noexcept { *ptr ^= (ull {1} << pos); }

        operator bool () const noexcept { return (*ptr >> pos) & 1; }
    };

    reference at(std::size_t __n) noexcept { return reference(data.data(), __n); }

    dynamic_bitset &validate() {
        const std::size_t __mod = length % _Bits;
        if (__mod) data.back() &= (ull {1} << __mod) - 1;
        return *this;
    }

    // Constructors
    dynamic_bitset() noexcept = default;
    dynamic_bitset(const dynamic_bitset &) = default;
    dynamic_bitset(dynamic_bitset &&) noexcept = default;
    dynamic_bitset &operator = (const dynamic_bitset &) = default;
    dynamic_bitset &operator = (dynamic_bitset &&) noexcept = default;

    dynamic_bitset(std::size_t __n, bool __val = false) {
        this->resize(__n);
        if (__val) this->set();
    }

    dynamic_bitset(std::string_view __str) {
        data.reserve((__str.size() + _Bits - 1) / _Bits);
        for (auto __ch : __str) this->push_back(__ch == '1');
    }

    dynamic_bitset &operator |= (const dynamic_bitset &rhs) {
        const std::size_t __len = std::min(length, rhs.length);
        const std::size_t __div = __len / _Bits;
        const std::size_t __mod = __len % _Bits;

        for (std::size_t i = 0 ; i != __div ; ++i) data[i] |= rhs.data[i];
        if (__mod) {
            const ull __mask = (ull {1} << (__mod)) - 1;
            data[__div] |= (rhs.data[__div] & __mask);
        }

        return *this;
    }

    dynamic_bitset &operator &= (const dynamic_bitset &rhs) {
        const std::size_t __len = std::min(length, rhs.length);
        const std::size_t __div = __len / _Bits;
        const std::size_t __mod = __len % _Bits;

        for (std::size_t i = 0 ; i != __div ; ++i) data[i] &= rhs.data[i];
        if (__mod) {
            const ull __mask = ull(-1) << __mod;
            data[__div] &= (rhs.data[__div] | __mask);
        }

        return *this;
    }

    dynamic_bitset &operator ^= (const dynamic_bitset &rhs) {
        const std::size_t __len = std::min(length, rhs.length);
        const std::size_t __div = __len / _Bits;
        const std::size_t __mod = __len % _Bits;

        for (std::size_t i = 0 ; i != __div ; ++i) data[i] ^= rhs.data[i];
        if (__mod) {
            const ull __mask = (ull(1) << (__mod)) - 1;
            data[__div] ^= (rhs.data[__div] & __mask);
        }

        return *this;
    }

    dynamic_bitset &operator <<= (std::size_t __n) {
        length += __n;
        const std::size_t __div = __n / _Bits;
        const std::size_t __mod = __n % _Bits;

        if (__div) data.insert(data.begin(), __div, 0);
        if (__mod) {
            const ull __mask = (ull(-1) << (__mod));
            ull __carry {};

            for (std::size_t i = __div ; i != data.size() ; ++i) {
                ull &__ref  = data[i];
                ull  __tmp  = __ref & __mask;
                __ref   = (__ref << __mod) | __carry;
                __carry = __tmp >> __mod;
            }

            if (length / _Bits != data.size()) data.push_back(__carry);
        }

        return *this;
    }

    dynamic_bitset operator ~ () const {
        dynamic_bitset __ret = *this;
        __ret.flip();
        return __ret;
    }

    bool operator [] (std::size_t __n) const { return this->test(__n); }

    bool test(std::size_t __n) const {
        const std::size_t __div = __n / _Bits;
        const std::size_t __mod = __n % _Bits;
        return (data[__div] >> __mod) & 1;
    }

    dynamic_bitset &set() noexcept {
        std::memset(data.data(), -1, data.size() * sizeof(ull));
        return this->validate();
    }

    dynamic_bitset &flip() noexcept {
        for (auto &__ref : data) __ref = ~__ref;
        return this->validate();
    }

    dynamic_bitset &reset() noexcept {
        std::memset(data.data(), 0, data.size() * sizeof(ull));
        return *this;
    }

    dynamic_bitset &set(std::size_t __n, bool __val = true) noexcept {
        this->at(__n).set(__val); return *this;
    }

    dynamic_bitset &flip(std::size_t __n) noexcept {
        this->at(__n).flip(); return *this;
    }

    dynamic_bitset &reset(std::size_t __n) noexcept {
        this->at(__n).set(false); return *this;
    }

    dynamic_bitset &resize(std::size_t __n) noexcept {
        length = __n;
        data.resize((__n + _Bits - 1) / _Bits);
        return *this;
    }

    dynamic_bitset &push_back(bool __val) noexcept {
        length % _Bits == 0 ?
            data.push_back(__val) : this->at(length).set(__val);
        ++length;
        return *this;
    }

    std::size_t size() const { return length; }

    std::string to_string() const {
        std::string __ret {};
        __ret.reserve(data.size() * _Bits);
        for (auto __val : data) {
            auto __tmp = std::bitset <_Bits> (__val).to_string();
            std::reverse(__tmp.begin(), __tmp.end());
            __ret += __tmp;
        }
        __ret.resize(length);
        return __ret;
    }
};



signed main() {
    dynamic_bitset x(100,1);    
    std::cout << x.to_string();
    x <<= 1;
    std::cout << "\nDone\n";
    return 0;
}
