// https://www.zhihu.com/question/450367735/answer/1791072270
#include <iostream>
#include <type_traits>

template<size_t N>
class Stream {
public:
    constexpr void push(char c) { data_[idx_++] = c; }
    constexpr operator const char*() const { return data_; }
    constexpr size_t size() { return idx_; }
private:
    size_t idx_{};
    char data_[N]{};
};

template<typename STREAM>
constexpr auto parse(const char* input, bool skip, char* cells,
        size_t& pc, STREAM&& output) -> size_t {
    const char* c = input;
    while(*c) {
        switch(*c) {
            case '+': if (!skip) ++cells[pc]; break;
            case '-': if (!skip) --cells[pc]; break;
            case '.': if (!skip) output.push(cells[pc]); break;
            case '>': if (!skip) ++pc; break;
            case '<': if (!skip) --pc; break;
            case '[': {
                while (!skip && cells[pc] != 0)
                    parse(c + 1, false, cells, pc, output);
                c += parse(c + 1, true, cells, pc, output) + 1;
            } break;
            case ']': return c - input;
            default: break;
        }
        ++c;
    }
    return c - input;
}

constexpr size_t CELL_SIZE = 16;
template<typename STREAM>
constexpr auto parse(const char* input, STREAM&& output) -> STREAM&& {
    char cells[CELL_SIZE]{};
    size_t pc{};
    parse(input, false, cells, pc, output);
    return output;
}

template<size_t OUTPUT_SIZE = 15>
constexpr auto brain_fuck(const char* input) {
    Stream<OUTPUT_SIZE> output;
    return parse(input, output);
}

constexpr auto brain_fuck_output_size(const char* input) -> size_t {
    struct {
        size_t sz{};
        constexpr void push(...) { ++sz; }
    } dummy;
    return parse(input, dummy).sz + 1;
}

#define BRAIN_FUCK(in) brain_fuck<brain_fuck_output_size(in)>(in)

int main() {
    puts(BRAIN_FUCK(
        "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>."
        ">---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++."
    ));
    return 0;
}