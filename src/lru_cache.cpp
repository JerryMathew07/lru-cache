#include "lru_cache.h"
#include <iostream>

LRUCache::LRUCache(int cap): capacity(cap){
    if (cap <= 0){
        throw std::invalid_argument("Capacity must be positive");
    }
    head = new Node(0, 0);
    tail = new Node(0, 0);
    head->next = tail;
    tail->prev = head;
}

LRUCache::~LRUCache(){
    Node* curr = head;
    while(curr != nullptr){
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
}

void LRUCache::detach(Node* node){
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void LRUCache::insertFront(Node* node){
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;
    head->next = node;
}

void LRUCache::moveToFront(Node* node){
    detach(node);
    insertFront(node);
}

LRUCache::Node* LRUCache::removeLRU(){
    Node* lru = tail->prev;
    detach(lru);
    return lru;
}

int LRUCache::get(int key){
    auto it = map.find(key);

    if(it == map.end()){
        return -1;
    }
    moveToFront(it->second);
    return it->second->value;
}

void LRUCache::put(int key, int value){
    auto it = map.find(key);

    if(it != map.end()){
        it->second->value = value;
        moveToFront(it->second);
        return;
    }

    Node* node = new Node(key, value);
    map[key] = node;
    insertFront(node);

    if((int)map.size() > capacity){
        Node* lru = removeLRU();
        map.erase(lru->key);
        delete lru;
    }
}

void LRUCache::print() const{
    Node* curr = head->next;
    std::cout << "Cache (MRU to LRU) :";
    while(curr != tail){
        std::cout << "[" << curr->key << ":" << curr->value << "]";
        curr = curr->next;
    }
    std::cout << std::endl;
}

int LRUCache::size() const {
    return (int) map.size();
}