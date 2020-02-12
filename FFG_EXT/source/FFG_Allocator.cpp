#include "FFG_Allocator.hpp"

/***************************************************************************//**
 * Private. Constructor.
 * @param allocator The allocator managing this memory block's memory.
 * @param index The index of this memory block in the allocator.
 ******************************************************************************/
FFG_MemBlock::FFG_MemBlock(FFG_Allocator* const allocator, const std::size_t index) : allocator(allocator), index(index) {
    // DO NOTHING.
}

void FFG_MemBlock::resize(const std::size_t bytes) {
    this->allocator->resize(this->index, bytes);
}

/***************************************************************************//**
 * Gets this memory block's address. This is not stored in the FFG_MemBlock and
 * in fact needs to be resolved.
 * @return The address of the memory block.
 ******************************************************************************/
void* FFG_MemBlock::get_ptr() const {
    return this->allocator->get_block_ptr(this->index);
}

/***************************************************************************//**
 * Gets this memory block's capacity. This is not stored in the FFG_MemBlock and
 * in fact needs to be resolved.
 * @return The capacity in bytes.
 ******************************************************************************/
std::size_t FFG_MemBlock::get_capacity() const {
    return this->allocator->get_block_capacity(this->index);
}

void FFG_MemBlock::debug_print() {
    void* const end = (void*)((char*)this->get_ptr() + this->get_capacity());
    std::cout << "\tSTART " << this->get_ptr() << " SIZE " << this->get_capacity() << " END " << end << " SIZE CHECK " << (char*)end - (char*)this->get_ptr() << " INDEX " << this->index << std::endl;
}

/***************************************************************************//**
 * Constructor.
 ******************************************************************************/
FFG_Allocator::FFG_MemBlockMeta::FFG_MemBlockMeta() {
    this->ptr = nullptr;
    this->capacity = 0;
}

/***************************************************************************//**
 * Constructor.
 * @param num_blocks_hint The initial capacity for number of supported
 * FFG_MemoryBlocks.
 ******************************************************************************/
FFG_Allocator::FFG_Allocator(const std::size_t num_blocks_hint) {
    this->start = nullptr;
    this->middle = nullptr;
    this->end = nullptr;
    this->num_blocks = 0;
    this->num_blocks_max = 0;
    if (num_blocks_hint > 0) this->set_num_blocks_max(num_blocks_hint);
}

/***************************************************************************//**
 * Destructor. Deletes all managed memory.
 ******************************************************************************/
FFG_Allocator::~FFG_Allocator() {
    if (this->start) delete [] (char*)this->start;
}

/***************************************************************************//**
 * Private. Resolves the FFG_MemBlock's address using its index.
 * @param index The index of the FFG_MemBlock.
 * @return The address of the memory block.
 ******************************************************************************/
void* FFG_Allocator::get_block_ptr(const std::size_t index) const {
    // return (((FFG_MemBlockMeta*) this->start) + index)->ptr;
    return ((FFG_MemBlockMeta*)this->start)[index].ptr;
}

/***************************************************************************//**
 * Private. Resolves the FFG_MemBlock's capacity using its index.
 * @param index The index of the FFG_MemBlock.
 * @return The capacity in bytes.
 ******************************************************************************/
std::size_t FFG_Allocator::get_block_capacity(const std::size_t index) const {
    return (((FFG_MemBlockMeta*) this->start) + index)->capacity;
}

/***************************************************************************//**
 * Private. Sets the new FFG_MemBlockMeta capacity. Must be greater than the
 * current capacity, otherwise a no-op.
 * @param new_num_blocks_max The new FFG_MemBlockMeta capacity.
 ******************************************************************************/
void FFG_Allocator::set_num_blocks_max(const std::size_t new_num_blocks_max) {
    // No-op if the capacity requirement is already met.
    if (new_num_blocks_max <= this->num_blocks_max) return;
    if (this->start) {
        // Allocate a new super block, copy the memory over, and update attributes.
        const std::size_t data_size = (char*)this->end - (char*)this->middle;
        const std::size_t new_size = data_size + (new_num_blocks_max * sizeof(FFG_MemBlockMeta));
        char* const new_start = new char [new_size];
        char* const new_middle = (char *)(((FFG_MemBlockMeta *)new_start) + new_num_blocks_max);
        char* const new_end = new_start + new_size;
        std::memcpy(new_start, this->start, this->num_blocks * sizeof(FFG_MemBlockMeta));
        std::memcpy(new_middle, this->middle, data_size);
        this->fix_meta_data(new_start, new_middle);
        delete [] (char*)this->start;
        this->start = new_start;
        this->middle = new_middle;
        this->end = new_end;
        this->num_blocks_max = new_num_blocks_max;
    } else {
        // Allocate the first super block.
        const std::size_t new_size = new_num_blocks_max * sizeof(FFG_MemBlockMeta);
        this->start = new char [new_size];
        this->middle = ((char*)this->start) + new_size;
        this->end = this->middle;
        this->num_blocks_max = new_num_blocks_max;
    }
}

void FFG_Allocator::resize(const std::size_t index, const std::size_t bytes) {
    FFG_MemBlockMeta& mem_block_meta = *((FFG_MemBlockMeta*)this->start + index);
    if (mem_block_meta.capacity == bytes) return;
    int size_diff = (int)bytes - (int)mem_block_meta.capacity;
    std::cout << "size diff: " << size_diff << std::endl;
    const std::size_t new_size = ((char*)this->end - (char*)this->start) + size_diff;
    char* const new_start = new char [new_size];
    char* const new_middle = new_start + ((char*)this->middle - (char*)this->start);
    char* const new_end = new_start + new_size;
    std::cout << "new size: " << (char*)new_end - (char*)new_middle << std::endl;
    if (size_diff < 0) {
        // The new block is smaller.
        char* const new_split = new_start + (((char*)mem_block_meta.ptr + bytes) - (char*)this->start);
        std::size_t first_split_size = new_split - new_start;
        std::size_t second_split_size = new_size - first_split_size;
        char* const old_split = (char*)mem_block_meta.ptr + mem_block_meta.capacity;
        std::memcpy(new_start, this->start, first_split_size);
        std::memcpy(new_split, old_split, second_split_size);
    } else {
        // The new block is larger.
        char* const old_split = (char*)mem_block_meta.ptr + mem_block_meta.capacity;
        std::size_t first_split_size = old_split - (char*)this->start;
        std::size_t second_split_size = (char*)this->end - old_split;
        char* const new_split = new_start + first_split_size + size_diff;
        std::memcpy(new_start, this->start, first_split_size);
        std::memcpy(new_split, old_split, second_split_size);
    }
    FFG_MemBlockMeta* old_mem_block_metas = (FFG_MemBlockMeta*)this->start;
    FFG_MemBlockMeta* new_mem_block_metas = (FFG_MemBlockMeta*)new_start;
    for (std::size_t i = 0; i < this->num_blocks; i++) {
        char* new_ptr = (char*)new_middle + ((char*)old_mem_block_metas[i].ptr - (char*)this->middle);
        if (i > index) new_ptr += size_diff;
        new_mem_block_metas[i].ptr = new_ptr;
    }
    // TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
    // TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
    // TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
    // TODO: Don't use fix_meta_data. Need a custom method here. The ones
    // after the index point to the wrong address.
    // this->fix_meta_data(new_start, new_middle);
    delete [] (char*)this->start;
    this->start = new_start;
    this->middle = new_middle;
    this->end = new_end;
    ((FFG_MemBlockMeta*)this->start)[index].capacity = bytes;
}

/***************************************************************************//**
 * Private. Fixes the meta data by updating all of their pointers to point into
 * the new memory block. Assumes that the start, middle, and end attribute
 * pointers all point into the old memory block.
 * @param new_start The start of the new memory block.
 * @param new_middle The middle of the new memory block.
 ******************************************************************************/
void FFG_Allocator::fix_meta_data(void* const new_start, void* const new_middle) {
    FFG_MemBlockMeta* old_mem_block_metas = (FFG_MemBlockMeta*)this->start;
    FFG_MemBlockMeta* new_mem_block_metas = (FFG_MemBlockMeta*)new_start;
    for (std::size_t i = 0; i < this->num_blocks; i++) {
        char* new_ptr = (char*)new_middle + ((char*)old_mem_block_metas[i].ptr - (char*)this->middle);
        new_mem_block_metas[i].ptr = new_ptr;
    }
}

/***************************************************************************//**
 * Creates a new FFG_MemBlock pointing to data managed by this FFG_Allocator and
 * returns it.
 * @param bytes The size in bytes of the new memory.
 * @return The new FFG_MemBlock.
 ******************************************************************************/
FFG_MemBlock FFG_Allocator::create_block(const std::size_t bytes) {
    // Ensure that there is enough capacity for the new memory block meta.
    if (this->num_blocks >= this->num_blocks_max) this->set_num_blocks_max(std::max(this->num_blocks_max * 2, 1U));
    // Allocate a new super block, copy the memory over, and update attributes.
    const std::size_t old_size = (char*)this->end - (char*)this->start;
    const std::size_t new_size = old_size + bytes;
    char* const new_start = new char [new_size];
    char* const new_middle = new_start + ((char*)this->middle - (char*)this->start);
    char* const new_end = new_start + new_size;
    std::memcpy(new_start, this->start, old_size);
    this->fix_meta_data(new_start, new_middle);
    delete [] (char*)this->start;
    this->start = new_start;
    this->middle = new_middle;
    this->end = new_end;
    // Create the new memory block meta.
    FFG_MemBlockMeta* const new_mem_block_loc = ((FFG_MemBlockMeta*)this->start) + this->num_blocks;
    #ifndef __INTELLISENSE__
    // Conditioned on intellisense because the Vscode CPP tools are dumb.
    FFG_MemBlockMeta* const new_mem_block_ptr =  new (new_mem_block_loc) FFG_MemBlockMeta();
    new_mem_block_loc->ptr = (char*)this->end - bytes;
    new_mem_block_loc->capacity = bytes;
    #endif
    // Create new memory block.
    FFG_MemBlock new_mem_block(this, this->num_blocks);
    // Update attributes.
    this->num_blocks++;
    // Return the resulting memory block.
    return new_mem_block;
}

void FFG_Allocator::debug_print() {
    if(!this->start) return;
    std::cout << "START " << this->start << " MIDDLE " << this->middle << " END " << this->end << "." << std::endl;
    std::cout << "NUM BLOCKS " << this->num_blocks << " NUM BLOCKS MAX " << this->num_blocks_max << "." << std::endl;
    std::cout << "TOTAL SIZE " << ((char*)this->end - (char*)this->start) << "." << std::endl;
    std::cout << "META BLOCK SIZE " << ((char*)this->middle - (char*)this->start) << " CHECK " << sizeof(FFG_MemBlockMeta) * this->num_blocks_max << " SIZEOF " << sizeof(FFG_MemBlockMeta) << std::endl;
    std::cout << "DATA BLOCK SIZE " << ((char*)this->end - (char*)this->middle) << "." << std::endl;
    FFG_MemBlockMeta* mem_block_metas = (FFG_MemBlockMeta*)this->start;
    for (int i = 0; i < this->num_blocks; i++) {
        FFG_MemBlockMeta& meta = mem_block_metas[i];
        void* const end = (void*)((char*)meta.ptr + meta.capacity);
        std::cout << "\tSTART " << meta.ptr << " SIZE " << meta.capacity << " END " << end << " SIZE CHECK " << (char*)end - (char*)meta.ptr << "." << std::endl;
    }
    std::cout << std::endl;
}
