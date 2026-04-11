# LRU Cache - C++17

An O(1) Least Recently Used cache implemented in C++ using a doubly linked list and hash map.

## What It Does

Maintains a fixed-capacity cache. When full, evicts the least recently used item to make room for new entries.

- get(key) - O(1) lookup, marks item as recently used.
- put(key, value) - O(1) insert or update with automatic eviction

## Design

Combines two data structues:
- **Doubly linked list** - maintains usage order.
Most recently used at front, least recently used at back.
- **unordered_map** - O(1) key to node lookup.

Dummy head and tail sentinel nodes eliminate edge cases in list manipulation.

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Run Tests

```bash
./test_lru
```
