#include "memory_pool.h"

int main()
{
	memory_pool mp;
	ptr pointer = mp.alloc(size_t(12));
	ptr pointer2 = mp.alloc(size_t(6));
	mp.free(pointer);
	ptr pointer3 = mp.alloc(size_t(12));
	ptr pointer4 = mp.alloc(size_t(12));
	return 0;
}