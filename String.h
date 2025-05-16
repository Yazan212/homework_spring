#pragma once
#include <iostream>
#include <memory>
#include <cstring>

class String {
	static constexpr int THRESHOLD = 15;
	struct Heap {
		int capacity = 0;
		std::unique_ptr<char[]> heap;
		Heap() = default;
		Heap(const char* str, int size, int cap) : capacity(cap) {
			heap = std::make_unique<char[]>(cap + 1);
			std::memcpy(heap.get(), str, size);
			heap[size] = '\0';
		}
	};

	union Storage {
		Heap heap;
		char buffer[THRESHOLD + 1];
		Storage() { buffer[0] = '\0'; }
		~Storage() {}

	} storage;

	int size;
	bool sso;


public:
	//constructor
	String() : size(0), sso(true), storage() {}
	
	//constructor
	String(const char* str) : size(std::strlen(str))
	{
		if (size <= THRESHOLD) {
			sso = true;
			std::memcpy(storage.buffer, str, size + 1);
		}
		else {
			sso = false;
			new (&storage.heap) Heap(str, size, size );
		}
	}

	//destructor
	~String() {
		if (!sso)
		{
			storage.heap.~Heap();
		}
	}

	//copy constructor
	String(const String& str) : size(str.size), sso(str.sso) {
		if (sso) {
			std::memcpy(storage.buffer, str.storage.buffer, size + 1);
		}
		else {
			new (&storage.heap) Heap(str.storage.heap.heap.get(), size, size);
		}
	}


	//move constructor
	String(String&& str) : size(str.size), sso(str.sso) {
		if (sso) {
			std::memcpy(str.storage.buffer, str.storage.buffer, size + 1);
		}
		else {
			new (&storage.heap) Heap();
			storage.heap.heap = std::move(str.storage.heap.heap);
		}
		str.sso = false;
		str.size = 0;
		str.storage.buffer[0] = '\0';
	}
	

	//copy assignment 
	String& operator=(String& str) {
		this -> ~String();
		new (this) String(str);
		return *this;
	}

	//move assignment
	String& operator=(String&& str) {
		this->~String();
		new (this) String(str);
		return *this;
	}

	void SetSize(int sz) {
		size = sz;
	}

	int GetSize() const {
		return size;

	}

	void ProcessCapacity(int new_cap) {
		if (sso) {
			if (new_cap <= THRESHOLD) return;
			//move from buffer to heap
			Heap newHeap(storage.buffer, size, new_cap);
			new (&storage.heap) Heap(std::move(newHeap));
			sso = false;
		}
		else {
			if (new_cap <= storage.heap.capacity) return;

			//delete old heap and update it
			Heap newHeap(storage.heap.heap.get(), size, new_cap);
			storage.heap.~Heap();
			new (&storage.heap) Heap(std::move(newHeap));
		}
	}

	char operator[](int i) const {
		if (sso) {
			return storage.buffer[i];
		}
		else
		{
			return storage.heap.heap[i];
		}
	}


	void Reserve(int new_cap) {
		ProcessCapacity(new_cap);
	}


	//common c_str functionality to get the raw string
	const char* c_str() const {
		return sso ? storage.buffer : storage.heap.heap.get();
	}


	//Append one char
	void Append(char ch) {
		Reserve(size + 1);
		if (sso) {
			storage.buffer[size] = ch;
			size++;
			storage.buffer[size] = '\0';

		}
		else {
			storage.heap.heap[size] = ch;
			size++;
			storage.heap.heap[size] = '\0';
		}
	}


	//Append string of chars
	void Append(const char* str) {
		int extra_size = std::strlen(str);
		int new_size = size + extra_size;
		Reserve(new_size);

		if (sso) {
			std::memcpy(storage.buffer + size, str, extra_size + 1);
			size = new_size;
		}
		else {
			std::memcpy(storage.heap.heap.get() + size, str, extra_size + 1);
			size = new_size;
		}
	}

	int GetCapacity() const {
		return sso ? THRESHOLD : storage.heap.capacity;
	}


	String operator+(const String& rhs) {
		const char* ch = rhs.c_str();
		String answer(*this);
		answer.Append(ch);
		return answer;
	}
};