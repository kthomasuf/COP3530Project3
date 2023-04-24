#include "MinHeap.h"
#include <iterator>

MinHeap::MinHeap(std::unordered_map<std::string, int> wordData) {
    heapSize = 0;
    for (auto iter = wordData.begin(); iter != wordData.end(); iter++) {
        std::pair<std::string, int> tempPair;
        tempPair.first = iter->first;
        tempPair.second = iter->second;
        insertValue(tempPair);
    }
}
int MinHeap::parent(int index) {
    if (index == 0) {
        return 0;
    }
    int parent = ((index - 1) / 2);
    return parent;
}
int MinHeap::left(int index) {
    int left = ((2 * index) + 1);
    return left;
}
int MinHeap::right(int index) {
    int right = ((2 * index) + 2);
    return right;
}
void MinHeap::insertValue(std::pair<std::string, int> data) {
    heapSize++;
    heapVector.push_back(data);
    heapifyUp(heapSize - 1);
}
void MinHeap::heapifyUp(int index) {
    // Inspired by Lecture Slides
    int parentNode = parent(index);
    if (parentNode == 0 && heapVector[parentNode].second > heapVector[index].second) {
        std::pair<std::string, int> tempPair = heapVector[index];
        heapVector[index] = heapVector[parentNode];
        heapVector[parentNode] = tempPair;
        return;
    }
    if (heapVector[parentNode].second > heapVector[index].second) {
        std::pair<std::string, int> tempPair = heapVector[index];
        heapVector[index] = heapVector[parentNode];
        heapVector[parentNode] = tempPair;
        heapifyUp(parentNode);
    }
}
void MinHeap::heapifyDown(int index) {
    int smallerValue = index;
    int leftChild = left(index);
    int rightChild = right(index);

    // These three if statements were inspired by: https://www.geeksforgeeks.org/building-heap-from-array/
    if (leftChild < heapSize && heapVector[leftChild].second < heapVector[smallerValue].second) {
        if (rightChild < heapSize) {
            if (heapVector[leftChild].second < heapVector[rightChild].second) {
                smallerValue = leftChild;
            }
            else {
                smallerValue = rightChild;
            }
        }
        else {
            smallerValue = leftChild;
        }
    }
    else if (rightChild < heapSize && heapVector[rightChild].second < heapVector[rightChild].second) {
        if (leftChild < heapSize) {
            if (heapVector[rightChild].second < heapVector[leftChild].second) {
                smallerValue = rightChild;
            }
            else {
                smallerValue = leftChild;
            }
        }
        else {
            smallerValue = rightChild;
        }
    }
    if (smallerValue != index) {
        std::pair<std::string, int> tempPair = heapVector[index];
        heapVector[index] = heapVector[smallerValue];
        heapVector[smallerValue] = tempPair;
        heapifyDown(smallerValue);
    }
}
std::pair<std::string, int> MinHeap::extractMin() {
    std::pair<std::string, int> temp = heapVector[0];
    heapVector[0] = heapVector[--heapSize];
    heapifyDown(0);
    return temp;
}