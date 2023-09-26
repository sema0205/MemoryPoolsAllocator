# MemoryPoolsAllocator

The allocator operates on the basis of pre-allocated memory blocks and meets [requirements for allocators](https://en.cppreference.com/w/cpp/named_req/Allocator).

A comparison was made with the standard allocator when interacting with containers, the results obtained are shown in [graph](analysis/myplot.png) - the time spent adding an element to the vector, depending on the number of added elements.

## Principle of operation

- To allocate memory, the allocator uses pre-allocated memory areas
- Memory is initially allocated by [pools](https://en.wikipedia.org/wiki/Memory_pool)
- Pools break into pieces of the same size
- The pool can allocate and free memory only in pieces (one or more)
- The pool has information about free and occupied pieces
- The pool clears its memory only at the end of its “life”
- When allocating memory of size N bytes, the allocator searches among the pools for the most suitable one so as to allocate memory most optimally; if this is impossible, then the exception std::bad_alloc is thrown
- When freed through the allocator, pieces of memory are again usable

## Implementation
The sizes of the pools, their number, as well as the sizes of the pieces are parameterized.

## Restrictions

<memory_resource> is not used.
