#pragma once
#include <cstdint>
#include <cstddef>
#include <exception>

namespace dark {

using rank_t   = std::size_t;
using number_t = std::size_t;
using offset_t = std::size_t;

inline static constexpr std::size_t kBit    = 13;   // Bits in total
inline static constexpr std::size_t kAlign  = 5;    // Page bits
inline static constexpr std::size_t kLen    = 8192; // Page length

struct node {
    node *next; // Pointer to the next node
    node *prev; // Pointer to the previous node
};

static_assert((1 << kBit) == kLen);
static_assert(sizeof(node) <= (1 << kAlign));

struct forward_list : node {
    /* Default constructor. */
    forward_list() : node({this, this}) {};
    /* Return whether the list is empty. */
    bool empty() const { return next == this; }

    /* Push a new node to the front. */
    auto push_front(node *) -> void;
    /* Pop the first node from the front. */
    auto pop_front()        -> node *;

    /* Debug the list, print out its inner info. */
    void debug(rank_t);
};

/* Cast any address to a node. */
inline node *cast_node(void *ptr) { return static_cast <node *> (ptr); }

} // namespace dark

namespace dark {

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

