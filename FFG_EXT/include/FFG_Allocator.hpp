#ifndef FFG_ALLOCATOR_H_INCLUDED
#define FFG_ALLOCATOR_H_INCLUDED

#include <algorithm>    // std::max
#include <cstddef>      // std::size_t
#include <cstring>      // std::memcpy
#include <iostream>

class FFG_Allocator;

/***************************************************************************//**
 * A pointer to a block of memory managed by FFG_Allocator. Can be resized.
 * 
 * @warning Resizing using FFG_MemBlock::resize() will cause all memory managed
 * by the FFG_Allocator used to create this FFG_MemBlock to be reallocated. See
 * FFG_Allocator for more details.
 * 
 * @warning The beginning of the memory block, return by
 * FFG_MemBlock::get_ptr(), is not stored. Rather, it is resolved. It will be
 * valid until the next time FFG_MemBlock::resize() is called.
 * 
 * Example usage:
 * -----------------------------------------------------------------------------
 * TODO: Add example usage.
 * -----------------------------------------------------------------------------
 ******************************************************************************/
class FFG_MemBlock {
private:
    friend class FFG_Allocator;
private:
    FFG_Allocator* const allocator;
    const std::size_t index;
private:
    FFG_MemBlock(FFG_Allocator* const allocator, const std::size_t index);
public:
    void resize(const std::size_t bytes);
    void* get_ptr() const;
    std::size_t get_capacity() const;
    void debug_print();
};

/***************************************************************************//**
 * A custom memory manager / allocator. Memory allocation and deallocation is not
 * particularly efficient, rather this allocator is optimized for runtime
 * access speeds by minimizing cache misses through data concurrency.
 * 
 * @warning All FFG_MemBlocks created by FFG_Allocator::create_block() must
 * only be used while the FFG_Allocator used to create them is in scope. When an
 * FFG_Allocator's destructor is called, all memory associated with it is
 * deallocated and thus all FFG_MemBlocks it created are invalid.
 * 
 * @warning Whenever an FFG_MemBlock is resized using FFG_MemBlock::resize(),
 * ALL memory amanaged by the FFG_Allocator will need to be reallocated. Because
 * of this, these FFG_MemBlocks should either never be resized during runtime,
 * or the memory managed by the allocator should be kept reasonably small.
 * 
 * Example usage:
 * -----------------------------------------------------------------------------
 * TODO: Add example usage.
 * -----------------------------------------------------------------------------
 ******************************************************************************/
class FFG_Allocator {
private:
    friend class FFG_MemBlock;
private:
    class FFG_MemBlockMeta {
    public:
        FFG_MemBlockMeta();
    public:
        void* ptr;
        std::size_t capacity;
    };
private:
    void* start;
    void* middle;
    void* end;
    std::size_t num_blocks;
    std::size_t num_blocks_max;
private:
    void* get_block_ptr(const std::size_t index) const;
    std::size_t get_block_capacity(const std::size_t index) const;
    void set_num_blocks_max(const std::size_t new_num_blocks_max);
    void resize(const std::size_t index, const std::size_t bytes);
    void fix_meta_data(void* const new_start, void* const new_middle);
public:
    FFG_Allocator(const std::size_t num_blocks_hint = 32);
    ~FFG_Allocator();
    FFG_MemBlock create_block(const std::size_t bytes);
    void debug_print();
};

#endif // FFG_ALLOCATOR_H_INCLUDED
