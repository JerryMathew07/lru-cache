#include "lru_cache.h"
#include <cassert>
#include <iostream>

void test_basic_put_get(){
    LRUCache cache(3);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);

    assert(cache.get(1) == 10);
    assert(cache.get(2) == 20);
    assert(cache.get(3) == 30);

    std::cout << "test_basic_put_get passed\n";
}

void test_eviction(){
    LRUCache cache(3);
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);

    // Access 1 - makes 2 the least recently used
    cache.get(1);

    // Insert 4 - should evict 2
    cache.put(4, 40);

    assert(cache.get(2) == -1); //evicted
    assert(cache.get(1) == 10);
    assert(cache.get(3) == 30);
    assert(cache.get(4) == 40);

    std::cout << "Test_eviction passed\n";
}

void test_update_existing_key(){
    LRUCache cache(2);
    cache.put(1, 10);
    cache.put(2, 20);

    //Update key 1
    cache.put(1, 100);
    assert(cache.get(1) == 100);

    //Insert 3 - should evict 2 not 1
    // because 1 was just updated
    cache.put(3, 30);
    assert(cache.get(2) == -1); // evicted
    assert(cache.get(1) == 100);
    
    std::cout << "test_update_existing_key passed\n";
} 

void test_capacity_one(){
    LRUCache cache(1);
    cache.put(1, 10);
    assert(cache.get(1) == 10);

    cache.put(2, 20);
    assert(cache.get(1) == -1); //evicted
    assert(cache.get(2) == 20);

    std::cout << "test_capacity_one passed\n";
}

void test_get_nonexistent(){
    LRUCache cache(3);
    assert(cache.get(99) == -1);

    std::cout << "test_get_nonexistent passed\n";
}

void test_invalid_capacity(){
    bool threw = false;
    try
    {
        LRUCache cache(0);
    }
    catch(const std::invalid_argument&)
    {
        threw = true;
    }
    assert(threw);
    
    std::cout << "test_invalid_capacity passed\n";
}

int main(){
    test_basic_put_get();
    test_eviction();
    test_update_existing_key();
    test_capacity_one();
    test_get_nonexistent();
    test_invalid_capacity();

    std::cout << "All tests passed.\n";
    return 0;
}