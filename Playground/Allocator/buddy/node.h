#pragma once
#include <cstdint>
#include <cstddef>
#include <exception>

namespace dark {

inline static constexpr std::size_t kBit    = 13;   // Bits in total
inline static constexpr std::size_t kAlign  = 4;    // Page bits
inline static constexpr std::size_t kLen    = 8192; // Page length

static_assert((1 << kBit) == kLen);

struct node {
    void *addr; // Pointer to the memory block
    node *next; // Pointer to the next node
};

struct forward_list {
    node *head {};

    /* Push a new node to the front. */
    auto push_front(node *) -> void;
    /* Pop and return the first element. */
    auto pop_front()        -> node *;
    /**
     * @brief Pop and recycle the first element.
     * @return void * Address of the memory block.
     */
    auto pop_remove()       -> void *;
    /* Return whether the list is empty. */
    bool empty() const { return head == nullptr; }
    /* Debug the list, print out its inner info. */
    void debug();
};

/**
 * @return Create a node with given data.
 */
inline auto create_node(void *) -> node *;

} // namespace dark

namespace dark {

using rank_t   = std::size_t;
using number_t = std::size_t;
using offset_t = std::size_t;

/**
 * @return void * Start address of the block.
 * @param number Index of the block.
 * @param rank   Rank of the block.
 * @note Rank must be the highest bit of the block.
 */
inline void *set_index(number_t, rank_t);

/**
 * @return number_t Index of the block.
 * @param ptr   Start address of the block.
 * @param rank  Rank of the block.
 */
inline number_t get_index(void *, rank_t);

using storage_t = std::byte[kLen];
/* Memory pool aligned. */
alignas(kLen) inline static storage_t memory_pool;


inline void *malloc(std::size_t);
inline void free(void *, std::size_t);


} // namespace dark

