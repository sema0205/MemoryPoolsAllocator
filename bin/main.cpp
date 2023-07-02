
#include "../lib/MemoryPool.h"

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <chrono>

int main(int argc, char** argv) {

    int max_elements = 0;
    int per_write = 0;

    max_elements = atoi(argv[1]);
    per_write = atoi(argv[2]);

    std::vector<int> vec_std;
    std::vector<int, MemoryPool<int>> vec_pool(MemoryPool<int>({1000000},{64}));

    auto begin = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();


    for (int i = 0; i < max_elements; i += per_write) {
        begin = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < i; j++) {
            vec_std.emplace_back(j);
        }
        end = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "\n";
        vec_std.clear();

        begin = std::chrono::high_resolution_clock::now();
        for (int j = 0; j < i; j++) {
            vec_pool.emplace_back(j);
        }
        end = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "\n";
        vec_pool.clear();
    }


//    // map
//    std::cout << "\n";
//
//
//    std::map<int, int> map_std;
//    begin = std::chrono::high_resolution_clock::now();
//    for (int i = 0; i < 400000; i += 2) {
//        map_std.insert({i, i+1});
//    }
////    for (auto temp : map_std) {
////        std::cout << temp.first << " " << temp.second << "\n";
////    }
//
//    std::cout << "Map \"insert\" Result for STD Default Allocator: ";
//    end = std::chrono::high_resolution_clock::now();
//    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms\n";
//
//
//
//
//    std::map<int, int, std::less<>, MemoryPool<std::pair<const int, int>>> map_pool(MemoryPool<std::pair<const int, int>>({500000}, {128}));
//    begin = std::chrono::high_resolution_clock::now();
//    for (int i = 0; i < 400000; i += 2) {
//        map_pool.insert({i, i+1});
//    }
////    for (auto temp : map_pool) {
////        std::cout << temp.first << " " << temp.second << "\n";
////    }
//
//    std::cout << "Map \"insert\" Result for Custom Memory Allocator: ";
//    end = std::chrono::high_resolution_clock::now();
//    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "ms\n";
//
//    // set
//    std::cout << "\n";
//
//
//
//    std::set<int> set_std;
//    begin = std::chrono::high_resolution_clock::now();
//    for (int i = 0; i < 200000; i++) {
//        set_std.insert(i);
//    }
//
////    for (auto temp : map_std) {
////        std::cout << temp.first << " " << temp.second << "\n";
////    }
//
//    std::cout << "Set \"insert\" Result for STD Default Allocator: ";
//    end = std::chrono::high_resolution_clock::now();
//    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds\n";
//
//
//
//
//    std::set<int, std::less<>, MemoryPool<int>> set_pool(MemoryPool<int>({500000},{128}));
//    begin = std::chrono::high_resolution_clock::now();
//    for (int i = 0; i < 200000; i++) {
//        set_pool.insert(i);
//    }
//
////    for (auto temp : set_pool) {
////        std::cout << temp << "\n";
////    }
//
//    std::cout << "Set \"insert\" Result for Custom Memory Allocator: ";
//    end = std::chrono::high_resolution_clock::now();
//    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds\n";


    return 0;
}