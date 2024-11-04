#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <functional>
#include <vector>


int bestFit(int sizeInWords, void* list);
int worstFit(int sizeInWords, void* list);

class MemoryManager {
  public:

    // Constructor; sets native word size (in bytes, for alignment) and default allocator for finding a memory hole.
      // ● Store wordSize and the passed in default allocator function as member variables.
    MemoryManager(unsigned wordSize, std::function<int(int, void *)> allocator);
    
    // Releases all memory allocated by this object without leaking memory.
      // ● Deletes all heap memory when the object falls out of scope. Never call the destructor directly.
    ~MemoryManager();

    // Instantiates block of requested size, no larger than 65536 words; cleans up previous block if applicable.
      // ● Instantiates contiguous array of size (sizeInWords * wordSize) amount of bytes.
      // ● If initialize is called on an already initialized object, call shutdown then reinitialize.
      // ● Most of your other functions should not work before this is called.
      // They should return the relevant error for the data type, such as void, -1, nullptr, etc.
    void initialize(size_t sizeInWords);
    
    // Releases memory block acquired during initialization, if any. This should only include memory created for long term use not those that returned such as getList() or getBitmap() as whatever is calling those should delete it instead.
      // ● If block is initialized, clear all data. Free any heap memory, clear any relevant data structures, reset member variables.
    void shutdown();

    // Allocates a memory using the allocator function. If no memory is available or size is invalid, returns nullptr.
      // ● sizeInBytes is the amount of bytes to be allocated. May not always be a multiple of wordSize.
      // Ex: wordSize = 8, and sizeInBytes = 26. 8 * 3 = 24, meaning that you need at least 4 words to store 26 bytes. That 4th word is considered to be populated, meaning it is not considered to have a hole.
      // ● Will call your allocator function to find out where best to allocate the memory, meaning you will need to call getList too.
      // ● Returns a pointer somewhere in your memory block to the starting location of the newly allocated space.
    // Very important function
    void *allocate(size_t sizeInBytes);

    // Frees the memory block within the memory manager so that it can be reused.
      // ● address is a pointer somewhere in your memory block to the starting location of the allocated space to be freed. It will be an address that you previously returned from allocate.
      // ● Allocated space is getting freed, so remember to either extend your existing holes, or account for new ones.
    // Very important function
    void free(void *address);

    void setAllocator(std::function<int(int, void*)> allocator);

    // Returns an array of information (in decimal) about holes for use by the allocator function (little-Endian). Offset and length are in words. If no memory has been allocated, the function should return a NULL pointer. Example: [3, 0, 10, 12, 2, 20, 6]
      // ● Returns a pointer to the start of a 2-byte array containing the list of holes in [offset, length] format. The first array element is the number of holes in the list.
      // ● For example, given the following holes: [0, 10] - [12, 2] - [20, 6]
      // ● You would return [3, 0, 10, 12, 2, 20, 6]
      // Heap memory
    void *getList();

    // Returns a bit-stream of bits in terms of an array representing whether words are used (1) or free (0). The first two bytes are the size of the bitmap (little-Endian); the rest is the bitmap, word-wise.
    // Note : In the following example B0, B2, and B4 are holes, B1 and B3 are allocated memory.
    // Hole-0 Hole-1 Hole-2 ┌─B4─┐ ┌ B2┐ ┌───B0 ──┐ ┌─Size (4)─┐┌This is Bitmap in Hex┐ Example: [0,10]-[12,2]-[20,6] [00 00001111 11001100 00000000] [0x04,0x00,0x00,0xCC,0x0F,0x00]
    // ┕─B3─┙ ┕B1┙
    // ReturnedArray: [0x04,0x00,0x00,0xCC,0x0F,0x00] or [4,0,0,204,15,0]
      // ● Returns a pointer to the start of an array of a 1-byte type that represents the current blocks and holes, using 1’s and 0’s for each word. 0 represents a hole, 1 represents an allocated block. The first two bytes in the bit stream represents the size of the array, in little-Endian.
      // ● Given the following list of holes: [0,10]-[12,2]-[20,6]
      // ● In words, using 1’s and 0’s, it will look like: 00000000 00110011 11110000 00
      // ● There are 26 words in this example, but each byte only stores 8 bits, so you need an extra byte to cover those last 2 bits. 00000000 00110011 11110000 00000000
      // ● You must now mirror each byte individually. 00000000 11001100 00001111 00000000
      // ● Now you add the two size bytes to the front. In this case, we have four bytes above, meaning that the size is 4.
      // ● Representing 4 with two bytes looks like:
      // 00000000 00000100
      // ● However, because it is in little-Endian, we must flip the order of the two bytes, yielding: 00000010 00000000
      // ● Now, we can complete the array.
      // 00000100 00000000 00000000 11001100 00001111 00000000
      // ● In integer form, it looks like: [4, 0, 0, 204, 15, 0]. You will return a pointer to the beginning of this array.
    void *getBitmap();

    unsigned getWordSize();
    void *getMemoryStart();
    unsigned getMemoryLimit();



    // do last:

    // Uses standard POSIX calls to write hole list to filename as text, returning -1 on error and 0 if successful.
    // Format: "[START, LENGTH] - [START, LENGTH] ...", e.g., "[0, 10] - [12, 2] - [20, 6]"
      // ● Prints out current list of holes to a file. You must use POSIX calls, you cannot use fstream objects.
      // ● Use open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777) to create, enable read-write, and truncate
      // the file on creation. Remember to call close on the file descriptor before ending the function, or your changes may not save. For further reading: 1, 2.
    int dumpMemoryMap(char *filename);

  private:
    unsigned wordSize;
    std::function<int(int, void*)> allocatorFunction;
    void* memoryStart;
    size_t memoryLimit;

    // Structure to represent memory block
    struct Block {
      size_t offset;
      size_t length;
      bool isFree;
    };

    std::vector<Block> blocks;

};

#endif