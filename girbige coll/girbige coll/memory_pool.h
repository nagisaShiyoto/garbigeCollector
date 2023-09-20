#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <thread>
#include <mutex>
class ptr
{
public:
	int offset;
	size_t size;
	int refCount;
	ptr*  assigne(ptr* rhs);
	bool operator == (const ptr& rhs);
}; 
class memory_pool
{
public:
	memory_pool();
	~memory_pool();
	ptr* alloc(const size_t& size);
	void free(ptr pointer);
	void clean();
private:
	int const EMOUNT_OF_MEMORY= 4056;
	//first int for the place second size_t for the amount of place
	std::vector<std::pair<int, size_t>> free_place;
	std::vector<ptr*> pointers;
	bool started;
	std::mutex lock;
	unsigned char* memory;
	bool collect;
};

