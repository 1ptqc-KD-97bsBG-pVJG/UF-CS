#include "MemoryManager.h"
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

// allocator functions, do not belong to MemoryManager class:

int bestFit(int sizeInWords, void* list) {
    uint16_t* holeList = static_cast<uint16_t*>(list);
    uint16_t numHoles = holeList[0];
    // move to first hole entry
    holeList += 1;
    int bestOffset = -1;
    uint16_t minSize = UINT16_MAX;

    // iterate through hole list
    for (uint16_t i = 0; i < numHoles * 2; i += 2) {
        uint16_t offset = holeList[i];
        uint16_t length = holeList[i + 1];
        if (length >= sizeInWords && length < minSize) {
            minSize = length;
            bestOffset = offset;
        }
    }
    return bestOffset;
}

int worstFit(int sizeInWords, void* list) {
    uint16_t* holeList = static_cast<uint16_t*>(list);
    uint16_t numHoles = holeList[0];
    holeList += 1;
    int worstOffset = -1;
    uint16_t maxSize = 0;

    // iterate through hole list
    for (uint16_t i = 0; i < numHoles * 2; i += 2) {
        uint16_t offset = holeList[i];
        uint16_t length = holeList[i + 1];
        if (length >= sizeInWords && length > maxSize) {
            maxSize = length;
            worstOffset = offset;
        }
    }
    return worstOffset;
}

// MEMORY MANAGER CLASS:

// constructor
MemoryManager::MemoryManager(unsigned wordSize, function<int(int, void*)> allocator)
  : wordSize(wordSize), allocatorFunction(allocator), memoryStart(nullptr), memoryLimit(0) {}

// destructor
MemoryManager::~MemoryManager(){
  shutdown();
}

void MemoryManager::setAllocator(std::function<int(int, void*)> allocator){
  allocatorFunction = allocator;
}

// allocate(!!!):
void* MemoryManager::allocate(size_t sizeInBytes){
  if (memoryStart == nullptr || sizeInBytes <= 0) {
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
    // split hole into allocated block and (smaller) hole
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

  // merge with previous block if free
  if (it != blocks.begin()) {
    auto prevIt = prev(it);
    if (prevIt->isFree) {
      prevIt->length += it->length;
      it = blocks.erase(it);
      it = prevIt;
    }
  }

  // merge with next block if free
  if (it + 1 != blocks.end()) {
    auto nextIt = it + 1;
    if (nextIt->isFree) {
      it->length += nextIt->length;
      blocks.erase(nextIt);
    }
  }


}

void MemoryManager::initialize(size_t sizeInWords){
  // return error if greater than 65536 (given in slides or discussion)
  if (memoryStart != nullptr) {
    shutdown();
  }

  if(sizeInWords > 65536){
    return;
  }
  
  memoryLimit = sizeInWords * wordSize;
  // allocate memory (!!!)
  memoryStart = new uint8_t[memoryLimit];
  if (memoryStart == nullptr) {
    return;
  }

  blocks.clear();
  Block initialBlock = {0, sizeInWords, true};
  blocks.push_back(initialBlock);
}

void MemoryManager::shutdown(){
  if (memoryStart != nullptr) {
    free(memoryStart);
    memoryStart = nullptr;
    memoryLimit = 0;
    blocks.clear();
  }
}

// return list of holes
void *MemoryManager::getList(){
  if (memoryStart == nullptr) {
    return nullptr;
  }

  size_t numHoles = 0;
  for (const auto& block : blocks) {
    if (block.isFree) {
      numHoles++;
    }
  }

  if (numHoles == 0) {
    return nullptr;
  }

  size_t arraySize = 1 + numHoles * 2;
  uint16_t* holeList = new uint16_t[arraySize];
  holeList[0] = static_cast<uint16_t>(numHoles);
  
  size_t i = 1;
  for (const auto& block : blocks) {
    if (block.isFree) {
      holeList[i++] = static_cast<uint16_t>(block.offset);
      holeList[i++] = static_cast<uint16_t>(block.length);
    }
  }
  return holeList;
}

unsigned MemoryManager::getWordSize(){
  return wordSize;
}

void* MemoryManager::getMemoryStart(){
  return memoryStart;
}

// return memory limit (in bytes)
unsigned MemoryManager::getMemoryLimit(){
  return static_cast<unsigned>(memoryLimit);;
}





// do last:
int MemoryManager::dumpMemoryMap(char *filename){
  if (memoryStart == nullptr || filename == nullptr) {
    return -1;
  }
  int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
  if (fd < 0) {
    return -1;
  }
  string output;
  bool first = true;
  for (const auto& block : blocks) {
    if (block.isFree) {
      if (!first) {
        output += " - ";
      }
      output += "[" + to_string(block.offset) + ", " + to_string(block.length) + "]";
      first = false;
    }
  }
  ssize_t result = write(fd, output.c_str(), output.size());
  close(fd);
  if (result < 0) {
    return -1;
  }
  return 0;
}

void* MemoryManager::getBitmap(){
    if (memoryStart == nullptr) {
        return nullptr;
    }
    size_t totalWords = memoryLimit / wordSize;
    size_t numBytes = (totalWords + 7) / 8;
    size_t arraySize = 2 + numBytes;
    uint8_t* bitmap = new uint8_t[arraySize];
    // lower byte
    bitmap[0] = static_cast<uint8_t>(numBytes & 0xFF);
    // higher byte
    bitmap[1] = static_cast<uint8_t>((numBytes >> 8) & 0xFF);
    memset(bitmap + 2, 0, numBytes);
    size_t bitIndex = 0;
    for (const auto& block : blocks) {
        for (size_t i = 0; i < block.length; ++i) {
            size_t byteIndex = bitIndex / 8;
            // start from LSB
            size_t bitInByte = bitIndex % 8;
            if (!block.isFree) {
                bitmap[2 + byteIndex] |= (1 << bitInByte);
            }
            bitIndex++;
        }
    }
  return bitmap;
}

