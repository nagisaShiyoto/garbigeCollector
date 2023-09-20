#include "memory_pool.h"

int main()
{
	memory_pool mp;
	ptr* pointer = mp.alloc(size_t(12));
	ptr* pointer2 = mp.alloc(size_t(6));
	pointer=pointer->assigne(pointer2);
	ptr* pointer4 = mp.alloc(size_t(12));
	mp.free(*pointer4);

	return 0;
}