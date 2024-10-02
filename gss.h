#ifndef GSS_H
#define GSS_H

#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>
#include <memory>
#include <algorithm>

template<typename T, typename Alloc = std::allocator<T>>
class GraphStructuredStack {
    public:
        using value_type = T;
        using size_type = size_t;
        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = value_type*;
        using const_pointer = const value_type*;
        using allocator_type = Alloc;
        using const_iterator = typename std::unordered_map<value_type, std::vector<value_type>>::const_iterator;
        using iterator = typename std::unordered_map<value_type, std::vector<value_type>>::iterator;
    public:
        GraphStructuredStack(const Alloc& alloc = Alloc()); 
    public:
        void push(const_reference value, const std::vector<iterator>& parents = {}); 
        void pop(iterator parent); 
        reference top(); 
        const_reference top() const; 
        bool empty() const; 
        void printGraph() const; 
        iterator find(const_reference nodeToFind); 
        iterator insert(iterator parentIt, const_reference newValue); 
        allocator_type get_allocator() const; 
        void addEdge(iterator parentIt, iterator childIt);
    private:
        void del(value_type val, std::vector<value_type>& vec);
    private:
        std::unordered_map<value_type, std::vector<value_type>> adjList;
        std::stack<value_type, std::vector<value_type, allocator_type>> stack;
        Alloc allocator;
};

#include "gss.hpp"

#endif