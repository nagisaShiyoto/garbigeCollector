#include "memory_pool.h"

memory_pool::memory_pool()
{
	this->memory = (unsigned char*) malloc(this->EMOUNT_OF_MEMORY);
	//the offset in the start is always 0
	this->free_place.push_back(std::pair<int, size_t>(0, this->EMOUNT_OF_MEMORY));
}

memory_pool::~memory_pool()
{
	//free the pool
	delete this->memory;
}

ptr memory_pool::alloc(const size_t& size)
{
	size_t newSize = size + 1;//gigve place to the refcounter
	ptr pointer;
	bool found = false;
	auto smallest = this->free_place.begin();
	//find the smallest place he can fit in
	for (auto it = this->free_place.begin(); it != this->free_place.end(); it++)
	{
		if (smallest->second > it->second && it->second>newSize)
		{
			found = true;
			smallest = it;
		}
	}
	if (found)
	{
		throw std::out_of_range("not enough space");
	}
	pointer.offset = smallest->first;
	pointer.size = newSize;
	//put it in place
	smallest->first += newSize;
	smallest->second -= newSize;
	if (smallest->second == 0)
	{
		this->free_place.erase(smallest);
	}
	this->memory[pointer.offset] = 1;//when create only one ref
	return pointer;
}

void memory_pool::free(ptr pointer)
{
	//go over until it find the place it supposed to be bofore it
	auto it = this->free_place.begin();
	auto before = this->free_place.end();
	for (it = this->free_place.begin(); it != this->free_place.end() && it->first < pointer.offset; ++it)
	{
		before = it;
	}
	//check if there isnt any memory between so it wont create unneccery place in vector
	if (it->first - pointer.size == pointer.offset)
	{
		it->first = pointer.offset;
		it->second += pointer.size;
	}
	//check if the last place dont have memory in between them
	else if (before!=this->free_place.end()&&before->first + before->second == pointer.offset)
	{
		before->second += pointer.size;
	}
	else
	{
		this->free_place.insert(it,std::pair<int,size_t>(pointer.offset,pointer.size));
	}
}

ptr& memory_pool::operator=(const ptr& rhs)
{
	ptr hi;
	return hi;
}
