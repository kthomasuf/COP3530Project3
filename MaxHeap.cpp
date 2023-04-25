#include "MaxHeap.h"
#include <iterator>

MaxHeap::MaxHeap(std::unordered_map<std::string, int> wordData) {
    heapSize = 0;
    for (auto iter = wordData.begin(); iter != wordData.end(); iter++) {
        std::pair<std::string, int> tempPair;
        tempPair.first = iter->first;
        tempPair.second = iter->second;
        insertValue(tempPair);
    }
}
int MaxHeap::parent(int index) {
    if (index == 0) {
        return 0;
    }
    int parent = ((index - 1) / 2);
    return parent;
}
int MaxHeap::left(int index) {
    int left = ((2 * index) + 1);
    return left;
}
int MaxHeap::right(int index) {
    int right = ((2 * index) + 2);
    return right;
}
void MaxHeap::insertValue(std::pair<std::string, int> data) {
    heapSize++;
    heapVector.push_back(data);
    heapifyUp(heapSize - 1);
}
void MaxHeap::heapifyUp(int index) {
    // Inspired by Lecture Slides
    int parentNode = parent(index);
    if (parentNode == 0 && heapVector[parentNode].second < heapVector[index].second) {
        std::pair<std::string, int> tempPair = heapVector[index];
        heapVector[index] = heapVector[parentNode];
        heapVector[parentNode] = tempPair;
        return;
    }
    if (heapVector[parentNode].second < heapVector[index].second) {
        std::pair<std::string, int> tempPair = heapVector[index];
        heapVector[index] = heapVector[parentNode];
        heapVector[parentNode] = tempPair;
        heapifyUp(parentNode);
    }
}
void MaxHeap::heapifyDown(int index) {
    int largerValue = index;
    int leftChild = left(index);
    int rightChild = right(index);

    // These three if statements were inspired by: https://www.geeksforgeeks.org/building-heap-from-array/
    if (leftChild < heapSize && heapVector[leftChild].second > heapVector[largerValue].second) {
        if (rightChild < heapSize) {
            if (heapVector[leftChild].second > heapVector[rightChild].second) {
                largerValue = leftChild;
            }
            else {
                largerValue = rightChild;
            }
        }
        else {
            largerValue = leftChild;
        }
    }
    else if (rightChild < heapSize && heapVector[rightChild].second > heapVector[rightChild].second) {
        if (leftChild < heapSize) {
            if (heapVector[rightChild].second > heapVector[leftChild].second) {
                largerValue = rightChild;
            }
            else {
                largerValue = leftChild;
            }
        }
        else {
            largerValue = rightChild;
        }
    }
    if (largerValue != index) {
        std::pair<std::string, int> tempPair = heapVector[index];
        heapVector[index] = heapVector[largerValue];
        heapVector[largerValue] = tempPair;
        heapifyDown(largerValue);
    }
}
std::pair<std::string, int> MaxHeap::extractMax() {
    std::pair<std::string, int> temp = heapVector[0];
    heapVector[0] = heapVector[--heapSize];
    if (heapSize != 0) {
        heapifyDown(0);
    }
    return temp;
}