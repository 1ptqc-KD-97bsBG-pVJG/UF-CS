#include "MemoryManager.h"

  // allocator functions, do not belong to MemoryManager class:

  // Returns word offset of hole selected by the best fit memory allocation algorithm, and -1 if there is no fit.
    // ● Allocator function, can be written inside MemoryManager.cpp but does not belong to MemoryManager class.
    // ● list will be structured like the output from getList.
    // ● Finds a hole in the list that best fits the given sizeInWords, meaning it selects the smallest possible hole that still fits
    // sizeInWords.
    // ● Returns word offset to the start of that hole.
  int bestFit(int sizeInWords, void *list){

  }

  // Returns word offset of hole selected by the worst fit memory allocation algorithm, and -1 if there is no fit.
    // ● Same as above, but finds largest possible hole instead.
  int worstFit(int sizeInWords, void *list){

  }



// allocate:
void* MemoryManager::allocate(size_t, sizeInBytes){
  // errenesto discusses more at 25:00
}

// free:
void MemoryManager::free(void *address){

}

void MemoryManager::initialize(size_t sizeInWords){
  // return error if greater than 65536
  if(sizeInWords > 65536){
    return;
  }
  // TODO: implement initialize
}

unsigned MemoryManager::getWordSize(){
  return wordSize;
}

void* MemoryManager::getMemoryStart(){
  return memoryStart;
}

unsigned MemoryManager::getMemoryLimit(){
  // TODO: convert sizeInWords to bytes
}





// do last:
int MemoryManager::dumpMemoryMap(char *filename){
  // TODO: implement dumpMemoryMap
  // temporary implementation for testing
  return -1;
}

void* MemoryManager::getBitmap(){
  // TODO: implement getBitmap
  // temporary implementation for testing
  return nullptr;
}

