#pragma once
#include <iostream>
#include <vector>
#include <utility>

class memory_pool
{
public:
	memory_pool();
	~memory_pool();
	int malloc(const size_t& size);
	void free(int ptr);
private:
	int const EMOUNT_OF_MEMORY= 4056;
	//first int for the place second size_t for the amount of place
	std::vector<std::pair<int, size_t>> free_place;
	unsigned char* memory;
};

