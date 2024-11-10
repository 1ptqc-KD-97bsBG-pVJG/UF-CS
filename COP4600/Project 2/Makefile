all:
		g++ -g -std=c++17 -c MemoryManager.cpp -o MemoryManager.o 
		ar cr libMemoryManager.a MemoryManager.o
		g++ -g -std=c++17 -o CommandLineTest CommandLineTest.cpp -L. -lMemoryManager

clean:
		rm -f *.o MemoryManager *.a *.txt