#pragma once
#include <vector>
#include <map>
#include <unordered_map>
#include <string>

class MaxHeap {
private:
    int heapSize;
    std::vector<std::pair<std::string, int>> heapVector;
    int parent(int index);
    int left(int index);
    int right(int index);
    void insertValue(std::pair<std::string, int> data);
    void heapifyUp(int index);
    void heapifyDown(int index);
public:
    MaxHeap(std::unordered_map<std::string, int> wordData);
    std::pair<std::string, int> extractMax();
};