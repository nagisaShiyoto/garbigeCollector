#include "memory_pool.h"

memory_pool::memory_pool()
{
	this->memory = new unsigned char(this->EMOUNT_OF_MEMORY);
	//the offset in the start is always 0
	this->free_place.push_back(std::pair<int, size_t>(0, this->EMOUNT_OF_MEMORY));
}

memory_pool::~memory_pool()
{
	//free the pool
	delete this->memory;
}

int memory_pool::malloc(const size_t& size)
{
	int offset = 0;
	auto smallest = this->free_place.begin();
	//find the smallest place he can fit in
	for (auto it = this->free_place.begin(); it != this->free_place.end(); it++)
	{
		if (smallest->second<it->second && it->second>size)
		{
			smallest = it;
		}
	}
	offset = smallest->first;
	//put it in place
	smallest->first += size;
	smallest->second -= size;

	return offset;
}
