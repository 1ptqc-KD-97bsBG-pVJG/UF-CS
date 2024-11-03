

public:

  // Constructor; sets native word size (in bytes, for alignment) and default allocator for finding a memory hole.
  MemoryManager(unsigned wordSize, std::function<int(int, void *)> allocator);
  // Releases all memory allocated by this object without leaking memory.
  ~MemoryManager();

  // Instantiates block of requested size, no larger than 65536 words; cleans up previous block if applicable.
  void initalize(size_t sizeInWords);
  
  // Releases memory block acquired during initialization, if any. This should only include memory created for long term use not those that returned such as getList() or getBitmap() as whatever is calling those should delete it instead.
  void shutdown();

  // Allocates a memory using the allocator function. If no memory is available or size is invalid, returns nullptr.
  void *allocate(size_t sizeInBytes);
  // Frees the memory block within the memory manager so that it can be reused.
  void free(void *address);
  // Returns an array of information (in decimal) about holes for use by the allocator function (little-Endian). Offset and length are in words. If no memory has been allocated, the function should return a NULL pointer. Example: [3, 0, 10, 12, 2, 20, 6]
  void *getList();