#include <iostream>
#include <vector>

constexpr bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

template <size_t _N>
struct field  {
  private:
    static_assert(is_prime(_N), "N must be prime number");
    size_t val {};

    /* Initialize with check for [0, 2 * _N) */
    constexpr field(size_t val, std::true_type) noexcept {
        this->val = val < _N ? val : val - _N;
    }
    /* Initialize without any check. */
    constexpr field(size_t val, std::false_type) noexcept {
        this->val = val; // Without check.
    }

  public:
    constexpr field() = default;
    constexpr field(size_t val) noexcept : val(val % _N) {}
    constexpr ~field() = default;


    constexpr field operator + () const noexcept {
        return { val ? _N - val : 0, std::false_type {} };
    }

    constexpr field operator - () const noexcept {
        return { _N - val, std::false_type {} };
    }

    /* Return inverse of current number. */
    constexpr field operator ~ () const noexcept {
        if constexpr (_N == 2) return *this;
        else { // Odd prime case.
            static_assert(_N > 2, "Odd primes must be greater than 2");
            field   __ret = 1;
            field   __tmp = *this;
            size_t  __cnt = _N - 2;
            do { // Fast pow.
                if (__cnt & 1) __ret *= __tmp;
                __tmp *= __tmp;
                __cnt >>= 1;
            } while(__cnt);
            return __ret;
        }
    }

    constexpr field operator + (const field &rhs) const noexcept { return { val + rhs.val,      std::true_type {} }; }
    constexpr field operator - (const field &rhs) const noexcept { return { val + _N - rhs.val, std::true_type {} }; }
    constexpr field operator * (const field &rhs) const noexcept { return { val * rhs.val }; }
    constexpr field operator / (const field &rhs) const noexcept { return *this * ~rhs; }

    constexpr field &operator += (const field &rhs) noexcept { return *this = *this + rhs; }
    constexpr field &operator -= (const field &rhs) noexcept { return *this = *this - rhs; }
    constexpr field &operator *= (const field &rhs) noexcept { return *this = *this * rhs; }
    constexpr field &operator /= (const field &rhs) noexcept { return *this = *this / rhs; }

    friend std::ostream &operator << (std::ostream &os, field __f) { return os << __f.val; }

    constexpr explicit operator double() const noexcept { return val; }
    constexpr explicit operator bool  () const noexcept { return val; }

    friend auto operator <=> (const field &lhs, const field &rhs) noexcept = default;
    friend bool operator ==  (const field &lhs, const field &rhs) noexcept = default;
};

template <typename _Tp>
struct poly_ring {
  private:
    std::vector <_Tp> coeff = { 0 };
    void adjust() { while (coeff.size() > 1 && !coeff.back()) coeff.pop_back(); }

  public:
    void set(std::vector <_Tp> __coeff) noexcept { coeff = std::move(__coeff); adjust(); }

    poly_ring() = default;
    poly_ring(size_t val) noexcept : coeff({ val }) {}

    friend std::ostream &operator << (std::ostream &os, const poly_ring &__r) {
        size_t __sz = __r.coeff.size();
        if (!__sz) return os << 0;
        while (__sz --> 1)
            os << __r.coeff[__sz] << "x^" << __sz << " + ";
        return os << __r.coeff[0];
    }

    poly_ring operator + () const noexcept { return *this; }
    poly_ring operator - () const noexcept {
        poly_ring __ret = *this;
        for (auto &__c : __ret.coeff) __c = -__c;
        return __ret;
    }


    poly_ring &operator += (const poly_ring &rhs) noexcept {
        if (auto __cmp = rhs.coeff.size() <=> coeff.size(); __cmp <= 0) {
            for (size_t i = 0; i < rhs.coeff.size(); ++i)
                coeff[i] += rhs.coeff[i];
            if (__cmp == 0) adjust();
        } else {
            for (size_t i = 0; i < coeff.size(); ++i)
                coeff[i] += rhs.coeff[i];
            for (size_t i = coeff.size(); i < rhs.coeff.size(); ++i)
                coeff.push_back(rhs.coeff[i]);
        } return *this;
    }

    poly_ring &operator -= (const poly_ring &rhs) noexcept {
        if (auto __cmp = rhs.coeff.size() <=> coeff.size(); __cmp <= 0) {
            for (size_t i = 0; i < rhs.coeff.size(); ++i)
                coeff[i] -= rhs.coeff[i];
            if (__cmp == 0) adjust();
        } else {
            for (size_t i = 0; i < coeff.size(); ++i)
                coeff[i] -= rhs.coeff[i];
            for (size_t i = coeff.size(); i < rhs.coeff.size(); ++i)
                coeff.push_back(-rhs.coeff[i]);
        } return *this;
    }

    poly_ring &operator *= (const poly_ring &rhs) noexcept {
        if (coeff.empty())      return *this;
        if (rhs.coeff.empty())  return *this = 0;
        std::vector <_Tp> __tmp(coeff.size() + rhs.coeff.size() - 1);
        for (size_t i = 0; i < coeff.size(); ++i)
            for (size_t j = 0; j < rhs.coeff.size(); ++j)
                __tmp[i + j] += coeff[i] * rhs.coeff[j];
        coeff = std::move(__tmp);
        return *this;
    }

    poly_ring &operator /= (const poly_ring &rhs) noexcept {
        if (coeff.size() < rhs.coeff.size()) return *this = 0;
        std::vector <_Tp> __tmp(coeff.size() - rhs.coeff.size() + 1);
        _Tp __inv = ~rhs.coeff.back();
        for (size_t i = __tmp.size() ; i --> 0; ) {
            __tmp[i] = coeff[i + rhs.coeff.size() - 1] * __inv;
            for (size_t j = 0; j < rhs.coeff.size(); ++j)
                coeff[i + j] -= __tmp[i] * rhs.coeff[j];
        }
        coeff = std::move(__tmp);
        return *this;
    }

    poly_ring &operator %= (const poly_ring &rhs) noexcept { return *this -= *this / rhs * rhs; }

    friend poly_ring operator + (const poly_ring &lhs, const poly_ring &rhs) noexcept { return poly_ring(lhs) += rhs; }
    friend poly_ring operator - (const poly_ring &lhs, const poly_ring &rhs) noexcept { return poly_ring(lhs) -= rhs; }
    friend poly_ring operator * (const poly_ring &lhs, const poly_ring &rhs) noexcept { return poly_ring(lhs) *= rhs; }
    friend poly_ring operator / (const poly_ring &lhs, const poly_ring &rhs) noexcept { return poly_ring(lhs) /= rhs; }
    friend poly_ring operator % (const poly_ring &lhs, const poly_ring &rhs) noexcept { return poly_ring(lhs) %= rhs; }

    friend bool operator ==     (const poly_ring &lhs, const poly_ring &rhs)  = default;
    friend auto operator <=>    (const poly_ring &lhs, const poly_ring &rhs) = default;
};

signed main() {
    poly_ring <field <11>> r, q;
    r.set({ 1, 2, 3});
    q.set({ 1, 2});
    std::cout << r << '\n';
    std::cout << (-r % -q) << '\n';
    return 0;
}
