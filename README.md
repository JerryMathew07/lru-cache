# LRU Cache - C++17

An O(1) Least Recently Used cache implemented in C++ using a doubly linked list and hash map, with thread safety via 'std::mutex'.

## What It Does

Maintains a fixed-capacity cache. When full, evicts the least recently used item to make room for new entries.

- get(key) - O(1) lookup, marks item as recently used.
- put(key, value) - O(1) insert or update with automatic eviction

## Design

Combines two data structures:
- **Doubly linked list** - maintains usage order.
Most recently used at front, least recently used at back.
- **unordered_map** - O(1) key to node lookup.

Dummy head and tail sentinel nodes eliminate edge cases in list manipulation.

## Thread Safety

All public methods are protected by a `std::mutex`. Notably, `get()` requires an exclusive lock despite being a read operation - it calls `moveToFront()` which mutates the list.

## Non-Copyable

The Cache manages raw pointers internally and is explicitly made non-copyable to prevent double-free bugs.

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Run Tests

```bash
# Correctness tests
./test_lru
# Thread safety stress tests
./test_lru_threaded
```
