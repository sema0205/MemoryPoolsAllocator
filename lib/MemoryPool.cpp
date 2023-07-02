
#include "MemoryPool.h"

Pool::Pool(size_t amount, size_t size): ChunksAmount(amount), ChunkSize(size) {
    data = static_cast<std::byte*>(malloc(ChunksAmount * ChunkSize));
    is_free = static_cast<bool*>(malloc(ChunksAmount));
    first_free = 0;
    std::memset(is_free, false, ChunksAmount);
    std::memset(data, 0, ChunksAmount * ChunkSize);
};

Pool::~Pool() {
    free(data);
    free(is_free);
}

bool Pool::is_owned(void* pointer) {

    if (pointer >= data && pointer <= data + (ChunkSize * ChunksAmount)) {
        return true;
    }

    return false;
}

std::byte* Pool::allocate(size_t amount) {

    auto pos = find_free_sequence(1 + ((amount - 1) / ChunkSize));
    if (pos == ChunksAmount) {
        return nullptr;
    }

    fill_chunks(pos, 1 + ((amount - 1) / ChunkSize));

    return data + (pos * ChunkSize);
}

void Pool::deallocate(void* pointer, size_t amount) {
    auto byte = static_cast<std::byte*>(pointer);
    auto pos = (byte - data) / ChunkSize;
    if (pos < first_free) {
        first_free = pos;
    }
    clear_chunks(pos, 1 + ((amount - 1) / ChunkSize));
}

size_t Pool::find_free_sequence(size_t amount) {

    int counter = 0;

    for (size_t i = first_free; i < ChunksAmount; ++i) {
        if (!is_free[i]) {
            counter++;
        } else {
            counter = 0;
        }

        if (counter == amount) {
            return i + 1 - counter;
        }
    }

    return ChunksAmount;
}

void Pool::fill_chunks(size_t pos, size_t amount) {
    for (auto i = pos; i < pos + amount; i++) {
        is_free[i] = true;
    }
}

void Pool::clear_chunks(size_t pos, size_t amount) {
    for (auto i = pos; i < pos + amount; i++) {
        is_free[i] = false;
    }
}
