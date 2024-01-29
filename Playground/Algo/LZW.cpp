#include <span>
#include <format>
#include <vector>
#include <cstdint>
#include <iostream>
#include <unordered_map>

/* LZW compression */
struct LZW_encoder {
  private:
    std::unordered_map <std::string, std::size_t> dict;
  public:
    LZW_encoder() {
        std::string str = "-";
        for (int i = 0 ; i < 256 ; ++i) {
            str[0] = char(i);
            dict.try_emplace(str, i);
        }
    }

    template <typename _Send_fn>
    void encode(std::string_view __msg, _Send_fn &&__send) {
        std::string __prefix;
        for (char __c : __msg) {
            __prefix += __c;
            auto __success = dict.try_emplace(__prefix, dict.size()).second;
            if (dict.size() > 65535) throw std::runtime_error("LZW: dictionary overflow");            
            if (!__success) continue;
            __prefix.pop_back();
            __send(dict.at(__prefix));
            __prefix = __c;
        }
        if (__prefix.size()) __send(dict.at(__prefix));
        __send(0); // EOF
    }

    std::size_t size() const noexcept { return dict.size(); }
};


struct LZW_decoder {
  private:
    std::vector <std::string> dict;
    using _View_t = std::span <std::uint16_t>;
  public:
    LZW_decoder() {
        std::string str = "-";
        for (int i = 0 ; i < 256 ; ++i) {
            str[0] = char(i);
            dict.push_back(str);
        }
    }

    template <typename _Print_fn>
    void decode(_View_t __msg, _Print_fn &&__print) {
        std::string __prefix {};
        for (std::uint16_t __num : __msg) {
            if (__num == 0) break;  // EOF
            std::string __str = dict[__num];
            __print(__str);
            if (__prefix.size())
                dict.push_back(__prefix + __str[0]);
            __prefix = __str;
        }
    }
};

void unit_test(std::string_view __input) {
    std::vector <std::uint16_t> __msg;

    LZW_encoder __sender;
    __sender.encode(__input, [&](std::uint16_t __val) { __msg.push_back(__val); });

    LZW_decoder __receiver;
    __receiver.decode(__msg, [](std::string_view __str) { std::cout << __str; });
}

std::string generate(std::size_t __len) {
    std::string __str(__len, ' ');
    for (std::size_t i = 0 ; i < __len ; ++i)
        __str[i] = char(rand() % 10 + 1);
    return __str;
}

void compress_rate() {
    constexpr std::size_t __len = 261500;
    std::string __str = generate(__len);
    std::vector <std::uint16_t> __msg;

    LZW_encoder __sender;
    __sender.encode(__str, [&](std::uint16_t __val) { __msg.push_back(__val); });
    // std::cout << __sender.size() << '\n';
    std::cout << std::format("New space: {:.4}%\n", __msg.size() * (200.0  / __len));
}

signed main() {
    // std::string str;
    // std::getline(std::cin, str);
    // unit_test(str);

    srand(time(NULL));
    compress_rate();

    return 0;
}
