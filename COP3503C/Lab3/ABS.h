#ifndef ABS_H
#define ABS_H
#include <iostream>
#include <string>
using namespace std;

template <class T>
class ABS
{
    private:
    T *data;
    int size;
    int maxCapacity;
    int capacity;
    int scaleFactor = 2;

    public:
    // Default constructor. Maximum capacity should be set to 1, and current size set to 0; 
    ABS()
    {
        data = new T[1];
        size = 0;
        maxCapacity = 1;
    };

    // Constructor for an ABS with the specified starting maximum capacity.
    ABS(int capacity){
        data = new T[capacity];
        size = 0;
        maxCapacity = capacity;
    };

    // Copy constructor
    ABS(const ABS &d);

    // Assignment operator
    ABS &operator=(const ABS &d);

    // Destructor
    ~ABS()
    {
        delete [] data;
    };


    // Add a new item to the top of the stack and resize if necessary
    void push(T data)
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

    // Remove the item at the top of the stack, resize if necessary, and return the value removed. Throws a runtime_error if the stack is empty.
    T pop()
    {
        if (size == 0){
            throw runtime_error("Stack is empty");
        }
        else{
            T tempValue = data[size-1];
            size--;
            // convert scale factor to double to avoid integer division
            if (size < maxCapacity/static_cast<double>(scaleFactor)){
                T *tempPointer = new T[maxCapacity/scaleFactor];
                for (int i = 0; i < size; i++){
                    tempPointer[i] = this->data[i];
                }
                delete [] this->data;
                this->data = tempPointer;
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
            return data[size-1];
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