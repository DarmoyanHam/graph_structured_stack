#ifndef GSS_HPP
#define GSS_HPP

#include "gss.h"

template<typename T, typename Alloc>
GraphStructuredStack<T, Alloc>::GraphStructuredStack(const Alloc& alloc)
    : stack(std::vector<T, Alloc>(alloc))
    , allocator(alloc) 
    {}

template<typename T, typename Alloc>
void GraphStructuredStack<T, Alloc>::push(const_reference value, const std::vector<iterator>& parents) 
{
    if(!adjList.contains(value))
    {
        stack.push(value);
        adjList[value] = {};
    }
    for(const auto& parent : parents) 
    {
        parent->second.push_back(value);
    }
}

template<typename T, typename Alloc>
void GraphStructuredStack<T, Alloc>::pop(iterator parent) 
{
    if (stack.empty()) {
        throw std::out_of_range("graph is empty");
    }

    if (parent->second.empty()) {
        throw std::out_of_range("No child nodes to pop");
    }

    auto tmp = parent->second.end() - 1;

    while (!adjList[*tmp].empty()) {
        tmp = adjList[*tmp].end() - 1;
    }

    value_type toBeDel = *tmp;
    del(toBeDel, parent->second);

    bool foundInOtherPaths = false;
    for (const auto& i : adjList) {
        if (std::find(i.second.begin(), i.second.end(), toBeDel) != i.second.end()) {
            foundInOtherPaths = true;
            break;
        }
    }

    if (!foundInOtherPaths) {
        adjList.erase(toBeDel);
    }
}

template<typename T, typename Alloc>
void GraphStructuredStack<T, Alloc>::del(value_type val, std::vector<value_type>& vec)
{
    if (vec.empty()) {
        return;
    }

    vec.erase(std::remove(vec.begin(), vec.end(), val), vec.end());

    for (const auto& i : vec) {
        del(val, adjList[i]);
    }
}




template<typename T, typename Alloc>
typename GraphStructuredStack<T, Alloc>::reference GraphStructuredStack<T, Alloc>::top() 
{
    if (stack.empty()) {
        throw std::out_of_range("Stack is empty");
    }
    return stack.top();
}

template<typename T, typename Alloc>
typename GraphStructuredStack<T, Alloc>::const_reference GraphStructuredStack<T, Alloc>::top() const
{
    if (stack.empty()) {
        throw std::out_of_range("Stack is empty");
    }
    return stack.top();
}

template<typename T, typename Alloc>
bool GraphStructuredStack<T, Alloc>::empty() const
{
    return stack.empty();
}


template<typename T, typename Alloc>
void GraphStructuredStack<T, Alloc>::printGraph() const
{
    for (const auto& node : adjList) 
    {
        std::cout << node.first << ": ";
        for (const auto& neighbor : node.second) 
        {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
} 

template<typename T, typename Alloc>
typename GraphStructuredStack<T, Alloc>::iterator GraphStructuredStack<T, Alloc>::find(const_reference nodeToFind) 
{
    auto it = adjList.find(nodeToFind);
    if (it == adjList.end()) {
        throw std::invalid_argument("Node not found");
    }
    return it;
}

template<typename T, typename Alloc>
typename GraphStructuredStack<T, Alloc>::iterator GraphStructuredStack<T, Alloc>::insert(iterator parentIt, const_reference newValue) 
{
    if(std::find(parentIt->second.begin(), parentIt->second.end(), newValue) == parentIt->second.end())
    {
        parentIt->second.push_back(newValue);
    }
    if(!adjList.contains(newValue))
    {
        adjList[newValue] = {};
        stack.push(newValue);
    }
    return adjList.find(newValue);
}

template<typename T, typename Alloc>
typename GraphStructuredStack<T, Alloc>::allocator_type GraphStructuredStack<T, Alloc>::get_allocator() const 
{
    return allocator;
}

template<typename T, typename Alloc>
void GraphStructuredStack<T, Alloc>::addEdge(iterator parentIt, iterator childIt)
{
    if(std::find(parentIt->second.begin(), parentIt->second.end(), childIt->first) == parentIt->second.end())
    {
        parentIt->second.push_back(childIt->first);
    }
}

#endif