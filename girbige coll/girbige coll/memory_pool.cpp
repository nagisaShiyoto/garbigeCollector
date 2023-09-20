#include "memory_pool.h"
#include <windows.h>

memory_pool::memory_pool()
{
	this->collect = true;//activativate the cleaning
	this->memory = (unsigned char*) malloc(this->EMOUNT_OF_MEMORY);
	//the offset in the start is always 0
	this->free_place.push_back(std::pair<int, size_t>(0, this->EMOUNT_OF_MEMORY));
	std::thread asd (&memory_pool::clean, this);
	asd.detach();
	this->started = false;
	while (!this->started)
	{
		std::cout << "didn't start yet:("<<std::endl;

	}
}

memory_pool::~memory_pool()
{
	//deactivate the cleaning
	this->collect = false;
	//free the pool
	delete this->memory;
}

ptr* memory_pool::alloc(const size_t& size)
{
	ptr* pointer=new ptr;
	bool found = false;
	while(!this->lock.try_lock());
	auto smallest = this->free_place.begin();
	//find the smallest place he can fit in
	for (auto it = this->free_place.begin(); it != this->free_place.end(); it++)
	{
		if (smallest->second > it->second && it->second>size)
		{
			found = true;
			smallest = it;
		}
	}
	if (found)
	{
		throw std::out_of_range("not enough space");
	}
	pointer->offset = smallest->first;
	pointer->size = size;
	//put it in place
	smallest->first += size;
	smallest->second -= size;
	if (smallest->second == 0)
	{
		this->free_place.erase(smallest);
	}
	//put it in the vector and make the refCount 1
	pointer->refCount = 1;
	this->pointers.push_back(pointer);
	this->lock.unlock();
	Sleep(100);
	return pointer;
}

void memory_pool::free(ptr pointer)
{
	while(!this->lock.try_lock());
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
	for (auto it = this->pointers.begin(); it != this->pointers.end(); it++)
	{
		if ((**it) == pointer)
		{
			delete* it;
			this->pointers.erase(it);
			break;
		}
	}
	this->lock.unlock();
	Sleep(100);
}

void memory_pool::clean()
{
	this->started = true;
	while (this->collect)
	{
		while (this->lock.try_lock() == false)
		{
			std::cout << "okupaid";
		}
		for (int i = 0; i < this->pointers.size(); i++)
		{
			if (this->pointers[i]->refCount == 0)
			{
				this->lock.unlock();
				this->free(*this->pointers[i]);
				this->lock.lock();//so it could unlock
			}
			
		}
		this->lock.unlock();
	}
}

ptr* ptr::assigne(ptr* rhs)
{
	rhs->refCount++;
	this->refCount--;
	return rhs;
}
bool ptr::operator==(const ptr& rhs)
{
	if (this->offset == rhs.offset && this->size == rhs.size && this->refCount == rhs.refCount)
	{
		return true;
	}
	return false;
}