

#ifndef LABWORK9_MEMORYPOOL_H
#define LABWORK9_MEMORYPOOL_H


#include <iostream>
#include <cstring>

class Pool {
public:

    Pool() = default;
    Pool(size_t amount, size_t size);
    ~Pool();

    bool is_owned(void* pointer);

    std::byte* allocate(size_t amount);
    void deallocate(void* pointer, size_t amount);

    size_t ChunksAmount = 0;
    size_t ChunkSize = 0;

private:

    size_t find_free_sequence(size_t amount);
    void fill_chunks(size_t pos, size_t amount);
    void clear_chunks(size_t pos, size_t amount);

    std::byte* data;
    size_t first_free;
    bool* is_free;
};


template<typename T>
class MemoryPool {
public:
    typedef T               value_type;
    typedef T*              pointer;
    typedef size_t          size_type;
    typedef std::ptrdiff_t  difference_type;

    template<typename U>
    struct rebind { typedef MemoryPool<U> other; };

    MemoryPool() = default;

    template<typename U>
    MemoryPool(const MemoryPool<U>& other);

    MemoryPool(std::initializer_list<size_t> list1, std::initializer_list<size_t> list2);

    ~MemoryPool() noexcept;

    void deallocate(void* ptr, size_type amount);
    pointer allocate(size_type amount);

    Pool** GetMas() const {
        return mas;
    }

    size_type GetAmount() const {
        return pools_amount;
    }

private:
    Pool** mas;
    size_type pools_amount;
};

template<typename T>
template<typename U>
MemoryPool<T>::MemoryPool(const MemoryPool<U>& other) {
    mas = other.GetMas();
    pools_amount = other.GetAmount();
}

template<typename T>
MemoryPool<T>::~MemoryPool() noexcept {
    std::destroy_n(mas, pools_amount);
}

template<typename T>
T* MemoryPool<T>::allocate(MemoryPool::size_type amount) {

    for (size_t it1 = 0; it1 < pools_amount; it1++) {
        if (mas[it1]->ChunkSize*mas[it1]->ChunksAmount >= sizeof(T)*amount) {
            auto ptr = reinterpret_cast<T*>(mas[it1]->allocate(sizeof(T)*amount));
            if (ptr != nullptr) {
                return ptr;
            }
        }
    }

    throw std::bad_alloc{};
}

template<typename T>
void MemoryPool<T>::deallocate(void* ptr, MemoryPool::size_type amount) {
    for (size_t it1 = 0; it1 < pools_amount; it1++) {
        if (mas[it1]->is_owned(ptr)) {
            mas[it1]->deallocate(ptr, amount);
            return;
        }
    }

}

template<typename T>
MemoryPool<T>::MemoryPool(std::initializer_list<size_t> list1, std::initializer_list<size_t> list2) {
    std::initializer_list<size_t>::iterator it1;
    std::initializer_list<size_t>::iterator it2;

    size_t counter = 0;
    pools_amount = list1.size();
    mas = static_cast<Pool**>(malloc(pools_amount));

    for (it1 = list1.begin(), it2 = list2.begin(); it1 != list1.end(); it1++, it2++) {
        mas[counter] = new Pool(*it1, *it2);
        counter++;
    }
}

#endif //LABWORK9_MEMORYPOOL_H
