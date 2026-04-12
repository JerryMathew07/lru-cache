#include "lru_cache.h"
#include <thread>
#include <vector>
#include <iostream>
#include <cassert>

void test_concurrent_writes(){
    LRUCache cache(100);
    std::vector<std::thread> threads;
    for(int i = 0; i < 10; i++){
        threads.emplace_back([&cache, i](){
            for (int j = 0; j < 100; j++){
                cache.put(i*100 + j, j);
            }
        });
    }  
    for (auto& t : threads){
        t.join();
    }
    
    assert(cache.size() <= 100);
    std::cout << "test_concurrent_writes passed\n";
}

void test_concurrent_reads() {
    LRUCache cache(10);

    //Pre-populate
    for (int i = 0; i < 10; i++){
        cache.put(i, i*10);
    }

    std::vector<std::thread> threads;

    for (int i = 0; i< 10; i++){
        threads.emplace_back([&cache, i](){
            for(int j = 0; j < 10; j++){
                int val = cache.get(i);
                assert(val == i*10);
            }
        });
    }
    for (auto& t : threads){
        t.join();
    }
    std::cout << "test_concurrent_reads passed\n";
}

void test_concurrent_reads_and_writes(){
    LRUCache cache(50);
    std::vector<std::thread> threads;

    // 5 Writer threads
    for(int i = 0; i < 5; i++){
        threads.emplace_back([&cache, i](){
            for (int j = 0; j < 100; j++){
                cache.put(i * 100 + j, j);
            }
        });
    }

    // 5 Reader threads
    for (int i = 0; i < 5; i++){
        threads.emplace_back([&cache, i](){
            for (int j = 0; j < 100; j++){
                cache.get(j);
            }
        });
    }

    for (auto& t: threads) t.join();

    assert(cache.size() <= 50);
    std::cout << "test_concurrent_reads_and_writes passed\n";
}

// Hammer test - maximum contention
void test_hammer(){
    LRUCache cache(10);
    std::vector<std::thread> threads;

    for (int i = 0; i < 20; i++){
        threads.emplace_back([&cache, i](){
            for (int j = 0; j < 100; j++){
                if (j % 2 == 0){
                    cache.put(j, j);
                } else {
                    cache.get(j);
                }
            }
        });
    }   

    for (auto& t : threads) t.join();

    assert(cache.size() <= 10);
    std::cout << "test_hammer passed\n";
}

int main(){
    test_concurrent_writes();
    test_concurrent_reads();
    test_concurrent_reads_and_writes();
    test_hammer();
    std::cout << "All tests passed!\n";
    return 0;
}
