#include "memory_pool.h"

int main()
{
	memory_pool mp;
	int pointer = mp.malloc(12);
	int pointer2 = mp.malloc(6);
	std::cout << pointer << std::endl << pointer2;
	return 0;
}