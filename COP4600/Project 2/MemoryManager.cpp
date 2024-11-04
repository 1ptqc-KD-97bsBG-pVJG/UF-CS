#include "MemoryManager.h"

using namespace std;

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
void* MemoryManager::allocate(size_t sizeInBytes){
  if (memoryStart == nullptr || sizeInBytes == 0) {
    return nullptr;
  }

  size_t sizeInWords = (sizeInBytes + wordSize - 1) / wordSize;
  uint16_t* holeList = static_cast<uint16_t*>(getList());
  
  if (holeList == nullptr) {
    return nullptr;
  }

  int offset = allocatorFunction(static_cast<int>(sizeInWords), holeList);
  delete[] holeList;

  if (offset == -1) {
    return nullptr;
  }

  size_t offsetWords = static_cast<size_t>(offset);
  auto it = find_if(blocks.begin(), blocks.end(), [offsetWords](const Block& block) {
    return block.offset == offsetWords && block.isFree;
  });

  if (it == blocks.end()) {
    return nullptr;
  }

  Block& hole = *it;
  if (hole.length < sizeInWords) {
    return nullptr;
  }

  if (hole.length == sizeInWords) {
    hole.isFree = false;
  } else {
    Block allocatedBlock = {hole.offset, sizeInWords, false};
    hole.offset += sizeInWords;
    hole.length -= sizeInWords;
    blocks.insert(it, allocatedBlock);
  }

  return static_cast<void*>(static_cast<uint8_t*>(memoryStart) + offsetWords * wordSize);
}

// free:
void MemoryManager::free(void *address){
  if (memoryStart == nullptr || address == nullptr) {
    return;
  }

  size_t offsetBytes = static_cast<uint8_t*>(address) - static_cast<uint8_t*>(memoryStart);
  if (offsetBytes % wordSize != 0) {
    return;
  }

  size_t offsetWords = offsetBytes / wordSize;
  auto it = find_if(blocks.begin(), blocks.end(), [offsetWords](const Block& block) {
    return block.offset == offsetWords && !block.isFree;
  });

  if (it == blocks.end()) {
    return;
  }

  it->isFree = true;

  // Merge with previous block if it is free
  if (it != blocks.begin()) {
    auto prevIt = prev(it);
    if (prevIt->isFree) {
      prevIt->length += it->length;
      it = blocks.erase(it);
      it = prevIt;
    }
  }

  // Merge with next block if it is free
  if (it + 1 != blocks.end()) {
    auto nextIt = it + 1;
    if (nextIt->isFree) {
      it->length += nextIt->length;
      blocks.erase(nextIt);
    }
  }

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

