#include <iostream>
#include <algorithm>
using namespace std;

void heapify(int arr[], int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Left child is larger than root
    if (left < size && arr[left] > arr[largest]) {
        largest = left;
    }

    // Right child is larger than largest so far
    if (right < size && arr[right] > arr[largest]) {
        largest = right;
    }

    // Iargest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected subtree
        heapify(arr, size, largest);
    }
}

int* extractMax(int arr[], int& size) {
    if (size <= 0) {
        return nullptr;
    }
    if (size == 1) {
        size--;
        return arr;
    }

    // Store the maximum value and remove it from heap
    swap(arr[0], arr[size - 1]);
    size--;

    // Heapify root to maintain max heap property
    heapify(arr, size, 0);

    return arr;
}