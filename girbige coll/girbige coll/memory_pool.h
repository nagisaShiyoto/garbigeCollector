#pragma once
#include <iostream>
#include <vector>
#include <utility>
struct ptr
{
	int offset;
	size_t size;
}; 
class memory_pool
{
public:
	memory_pool();
	~memory_pool();
	ptr malloc(const size_t& size);
	void free(ptr pointer);
private:
	int const EMOUNT_OF_MEMORY= 4056;
	//first int for the place second size_t for the amount of place
	std::vector<std::pair<int, size_t>> free_place;
	unsigned char* memory;
};

