#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <functional>
#include <vector>
using namespace std;


int bestFit(int sizeInWords, void* list);
int worstFit(int sizeInWords, void* list);

class MemoryManager {
  public:

    MemoryManager(unsigned wordSize, function<int(int, void *)> allocator);
    ~MemoryManager();

    void initialize(size_t sizeInWords);
    void shutdown();

    void *allocate(size_t sizeInBytes);

    void free(void *address);

    void setAllocator(function<int(int, void*)> allocator);

    void *getList();

    void *getBitmap();

    unsigned getWordSize();
    void *getMemoryStart();
    unsigned getMemoryLimit();

    int dumpMemoryMap(char *filename);

  private:
    unsigned wordSize;
    function<int(int, void*)> allocatorFunction;
    uint8_t* memoryStart;
    size_t memoryLimit;

    // structure to represent memory block
    struct Block {
      size_t offset;
      size_t length;
      bool isFree;
    };

    vector<Block> blocks;

};

#endif