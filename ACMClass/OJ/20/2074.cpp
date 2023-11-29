#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <vector>
#include <array>

namespace dark {

inline constexpr
std::size_t my_hash(const char *__str) noexcept {
    std::size_t __val = 0;
    while (*__str) __val = __val * 131 + *__str++;
    return __val;
}

using Key_type = std::size_t;
using Val_type = long long;

template <bool _Find, typename _Tp>
[[nodiscard]] inline constexpr
_Tp *binary_search(_Tp *__beg, std::size_t __cnt, _Tp __val) {
    while (__cnt) {
        const auto __mid = __cnt >> 1;
        const auto __cmp = __beg[__mid] <=> __val;
        if (__cmp == 0) { return _Find ? __beg + __mid : nullptr; }
        if (__cmp <  0) { __beg += __mid + 1; __cnt -= __mid + 1; }
        else            { __cnt = __mid; }
    } return _Find ? nullptr : __beg;
}

template <typename _Tp>
inline constexpr
void insert_at(_Tp *__beg, _Tp *__end, _Tp __val) {
    std::memmove(__beg + 1, __beg, (__end - __beg) * sizeof(_Tp));
    *__beg = __val;
}



struct block_list {
  private:
    struct Node_type {
        Key_type key;
        Val_type val;
        auto operator <=> (const Node_type &__rhs) const noexcept = default;
    };

    inline static constexpr std::size_t BLOCK_SIZE = 4096 / sizeof(Node_type);
    struct block { Node_type data[BLOCK_SIZE]; };

    struct header {
        uint32_t    count;
        uint32_t    index;
        Node_type   first;
    };

    inline static std::size_t locate(std::size_t __pos, std::size_t __off = 0) {
        return (__pos * sizeof(block)) | (__off * sizeof(Node_type));
    }

  private:
    // Storage part.

    std::vector  <header>   data_list;
    std::vector <uint32_t>  free_list;
    std::fstream            file;       // File of real data.
    std::array  <char, 32>  free_name;  // Path for cached data.

    using _Iterator = decltype(data_list.begin());

    // Cache part.

    uint32_t cache_index;
    block cache; // Cache one block!
    block temp;  // Temporary block for insertion.

    // End of storage part.
  private:

    /**
     * @brief Generate file for free and data list.
     */
    void init_free(std::string_view __path) {
        for (std::size_t i = 0; i < __path.size(); ++i) free_name[i] = __path[i];
        std::fstream __file(free_name.data(), std::ios::binary | std::ios::in | std::ios::out);
        if (!__file.is_open()) {
            __file.open(free_name.data(), std::ios::binary | std::ios::out);
        } else { // Initialize the list.
            std::pair <std::size_t, std::size_t> __pair;
            __file.read((char *)(&__pair), sizeof(__pair));
            auto [__data_size, __free_size] = __pair;

            data_list.resize(__data_size);
            __file.read((char *)(data_list.data()), sizeof(header) * __data_size);

            if (__free_size == 0) return; // No free list!

            free_list.resize(__free_size);
            __file.read((char *)(free_list.data()), sizeof(uint32_t) * __free_size);
        }
    }

    /**
     * @brief Generate the file for main data.
     */
    void init_data(std::string_view __path) {
        file.open(__path.data(), std::ios::binary | std::ios::in | std::ios::out);
        if (!file.is_open()) {
            file.open(__path.data(), std::ios::binary | std::ios::out);
            file.close();
            file.open(__path.data(), std::ios::binary | std::ios::in | std::ios::out);
        } else { /* Do nothing. */ }
    }

    void flush_free() {
        std::fstream free_file(free_name.data(), std::ios::binary | std::ios::out);
        if (data_list.empty()) return; // No data to flush.

        std::pair <std::size_t, std::size_t> __pair {data_list.size(), free_list.size()};
        free_file.write((char *)(&__pair), sizeof(__pair));
        free_file.write((char *)(data_list.data()), sizeof(header)   * data_list.size());

        if (free_list.empty()) return; // No free list to flush.
        free_file.write((char *)(free_list.data()), sizeof(uint32_t) * free_list.size());
    }

    void flush_file() { return this->flush_cache(); }

    void flush_cache() {
        if (~cache_index) { // Flush the cache.
            file.seekp(cache_index * sizeof(block), std::ios::beg);
            file.write((char *)(&cache), sizeof(block));
        }
    }

    void read_block(void *__buf, std::size_t __pos, std::size_t __len) {
        file.seekg(__pos, std::ios::beg);
        file.read((char *)(__buf), __len * sizeof(Node_type));
    }

    void write_block(void *__buf, std::size_t __pos, std::size_t  __len) {
        file.seekp(__pos, std::ios::beg);
        file.write((char *)(__buf), __len * sizeof(Node_type));
    }

    void fill_cache(uint32_t __pos, uint32_t __len) {
        if (__pos == cache_index) return;   // Already cached.
        this->flush_cache();                // Flush the cache.
        this->read_block(&cache, locate(__pos), __len);
    }

    void void_cache() { cache_index = ~0u; }

    uint32_t allocate() {
        if (free_list.empty()) return data_list.size();
        const auto __pos = free_list.back();
        return free_list.pop_back(), __pos;
    }

  public:

    block_list(std::string_view __file, std::string_view __free)
    { init_free(__free); init_data(__file); void_cache(); }

    ~block_list() { flush_file(); flush_free(); }

    bool insert_empty(Key_type __key, Val_type __val) {
        free_list.clear(); // Free list becomes meaningless.
        cache_index     = 0;
        cache.data[0]   = {__key, __val};
        return data_list.push_back({1, 0, {__key, __val}}), true;
    }

    bool insert_front(Key_type __key, Val_type __val) {
        auto __pos = data_list.begin();
        this->fill_cache(__pos->index, __pos->count);
        insert_at(cache.data, cache.data + __pos->count, {__key, __val});
        __pos->first = cache.data[0];
        return insert_fix(__pos, 0);
    }

    bool insert_next(_Iterator __prev, _Iterator __next,[[maybe_unused]] std::size_t __off) {
        if (__next == data_list.begin())    return false; // No prev.
        if (__prev->count > BLOCK_SIZE / 2) return false; // Cannot ammortize.

        // Move half of the delta to the previous block.
        const std::size_t __half = (BLOCK_SIZE - __prev->count) / 2;

        std::memcpy(temp.data, cache.data, __half * sizeof(Node_type));
        this->write_block(&temp, locate(__prev->index, __prev->count), __half);

        __prev->count += __half;
        __next->count -= __half;
        __next->first  = cache.data[__half];

        std::memmove(cache.data, cache.data + __half, __next->count * sizeof(Node_type));
    }

    bool insert_prev(_Iterator __prev, _Iterator __next, std::size_t __off) {
        if (__next == data_list.end())      return false; // No next.
        if (__next->count > BLOCK_SIZE / 2) return false; // Cannot ammortize.

        // Move half of the delta to the next block.
        const std::size_t __half = (BLOCK_SIZE - __next->count) / 2;
        if (__off + __half < BLOCK_SIZE) {

        }

    }

    bool try_insert(_Iterator __pos, std::size_t __off) {
        if (++__pos->count == BLOCK_SIZE) return false;
        if (__off == 0) __pos->first = cache.data[0];
        return true;
    }

    bool insert_fix(_Iterator __pos, std::size_t __off) {
        if (try_insert (__pos, __off))              return true;
        if (insert_next(__pos - 1, __pos, __off))   return true;
        if (insert_prev(__pos, __pos + 1, __off))   return true;

        // Split!
        const auto __new_index = this->allocate();

    }

    inline static constexpr auto cmp_pair =
        [](Node_type rhs, header lhs) -> bool {
            return lhs.first < rhs;
        };

  public:
    bool insert(Key_type __key, Val_type __val) {
        if (data_list.empty()) return this->insert_empty(__key, __val);
        auto __pos = std::upper_bound( // Compare by pair.
            data_list.begin(), data_list.end(), Node_type {__key, __val}, cmp_pair
        );
        if (__pos-- == data_list.begin()) return this->insert_front(__key, __val);

        this->fill_cache(__pos->index, __pos->count);
        const Node_type __cur = { __key, __val };

        auto __ptr = // Pointer to the position to be inserted at.
            binary_search <false> (cache.data, __pos->count, __cur);
        if (!__ptr) return false; // Already existed.

        insert_at(__ptr, cache.data + __pos->count, __cur);
        return insert_fix(__pos, __ptr - cache.data);
    }
};

}


signed main() {
    std::ios::sync_with_stdio(false);
    std::size_t n;
    std::cin >> n;
    char buf[72];
    while (n--) {
        std::cin >> buf;
        std::string_view str(buf);
        switch(str[0]) {
            case 'i': // Insert
            case 'd': // Delete
            default: // Find
        }
    }

    return 0;
}
