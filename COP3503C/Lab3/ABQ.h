#ifndef ABQ_H
#define ABQ_H
#include <iostream>
#include <string>
using namespace std;

template <class T>
class ABQ
{
    private:
    T *data;
    int size;
    int maxCapacity;
    int capacity;
    int scaleFactor = 2;
    int front;
    int end;

    public:
    // Default constructor. Maximum capacity should be set to 1, and current size set to 0; 
    ABQ()
    {
        data = new T[1];
        size = 0;
        maxCapacity = 1;
    };

    // Constructor for an ABQ with the specified starting maximum capacity.
    ABQ(int capacity){
        data = new T[capacity];
        size = 0;
        maxCapacity = capacity;
    };

    // Copy constructor
    ABQ(const ABQ &d);

    // Assignment operator
    ABQ &operator=(const ABQ &d);

    // Destructor
    ~ABQ()
    {
        delete [] data;
    };

    // Add a new item to the back of the queue and resize if necessary.
    void enqueue(T data)
    {
        if (size == maxCapacity){
            T *temp = new T[maxCapacity*scaleFactor];
            for (int i = 0; i < maxCapacity; i++){
                temp[i] = this->data[i];
            }
            delete [] this->data;
            this->data = temp;
            maxCapacity *= 2;
        }
        this->data[size] = data;
        size++;
    };

    // Remove the item at the front of the queue, resize if necessary, and return the value removed. Throws a runtime_error if the queue is empty.
    T dequeue()
    {
        if (size == 0){
            throw runtime_error("Queue is empty");
        }
        else{
            T tempValue = data[0];
            for (int i = 1; i < size; i++){
                data[i-1] = data[i];
            }
            size--;
            // convert scale factor to double to avoid integer division
            if (size < maxCapacity/static_cast<double>(scaleFactor)){
                T *tempPointer = new T[maxCapacity/scaleFactor];
                for (int i = 0; i < size; i++){
                    tempPointer[i] = data[i];
                }
                delete [] data;
                data = tempPointer;
                maxCapacity /= 2;
            }
            return tempValue;
        }
    };
    // Return the value of the item at the top of the stack, without removing it. Throws a runtime_error if the stack is empty
    T peek()
    {
        if (size == 0){
            throw runtime_error("Stack is empty");
        }
        else{
            return data[0];
        }
    };

    // Returns the current number of items in the ABS
    unsigned int getSize()
    {
        return size;
    };

    // Returns the maximum capacity of the ABS
    unsigned int getMaxCapacity()
    {
        return maxCapacity;
    };

    // Returns the array representing the stack
    T* getData()
    {
        return data;
    };
};
#endif
