#include "memory_pool.h"

int main()
{
	memory_pool mp;
	ptr pointer = mp.malloc(size_t(12));
	ptr pointer2 = mp.malloc(size_t(6));
	ptr pointer3 = mp.malloc(size_t(12));
	ptr pointer4 = mp.malloc(size_t(12));
	std::cout << pointer.offset << std::endl << pointer2.size;
	mp.free(pointer3);
	pointer3 = mp.malloc(size_t(12));
	mp.free(pointer4);
	pointer4 = mp.malloc(size_t(12));
	return 0;
}