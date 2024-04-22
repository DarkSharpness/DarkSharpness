#include <iostream>
#include <atomic>

std::atomic <std::size_t> count {0};

struct proxy_set {
  private:
    std::size_t mask {};
  public:
    proxy_set() = default;
    proxy_set(const proxy_set &) = delete;
    proxy_set &operator=(const proxy_set &) = delete;
    proxy_set(proxy_set &&) = default;
    proxy_set &operator=(proxy_set &&) = delete;

    proxy_set &set(int i) {
        mask |= 1uz << i;
        return *this;
    }
    ~proxy_set() { count.fetch_or(mask); }

    static proxy_set make_set(int i) {
        proxy_set ret;
        ret.set(i);
        return ret;
    }
};

struct proxy_clr {
  private:
    std::size_t mask {};
  public:
    proxy_clr() = default;
    proxy_clr(const proxy_clr &) = delete;
    proxy_clr &operator=(const proxy_clr &) = delete;
    proxy_clr(proxy_clr &&) = default;
    proxy_clr &operator=(proxy_clr &&) = delete;

    proxy_clr &clr(int i) {
        mask |= 1uz << i;
        return *this;
    }

    ~proxy_clr() { count.fetch_and(~mask); }

    static proxy_clr make_clr(int i) {
        proxy_clr ret;
        ret.clr(i);
        return ret;
    }
};

struct proxy {
    proxy_set set(int i) {
        return proxy_set::make_set(i);
    }
    proxy_clr clr(int i) {
        return proxy_clr::make_clr(i);
    }
};

signed main() {
    count = 0b011110;

    proxy p;
    p.clr(1);
    p.set(0);

    std::cout << count << std::endl;
    return 0;
}
