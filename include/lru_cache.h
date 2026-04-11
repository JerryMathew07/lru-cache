#pragma once

#include <unordered_map>
#include <stdexcept>

struct Node {
    int key;
    int value;
    Node* prev;
    Node* next;

    Node(int k, int v)
        : key(k), value(v), prev(nullptr), next(nullptr){}
};

class LRUCache {
    private:
        int capacity;
        std::unordered_map<int, Node*> map;
        Node* head; // dummy head - most recently used side
        Node* tail; // dummy tail - least recently used side

        void detach(Node* node);
        void insertFront(Node* node);
        void moveToFront(Node* node);
        Node* removeLRU();
    
    public:
        explicit LRUCache(int cap);
        ~LRUCache();

        //Non-copyable
        LRUCache(const LRUCache&) = delete;
        LRUCache& operator=(const LRUCache&) = delete;

        int get(int key);
        void put(int key, int value);
        void print() const;
        int size() const;
};