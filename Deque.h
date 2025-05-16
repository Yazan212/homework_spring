#pragma once
#include <iostream>

template <typename T>
class Deque {
private:
	T* data = nullptr;
	int front, back, capacity, size;


private:
	//step in circular array forward 
	int CirciularForward(int i, int cap) {
		return (i + 1) % cap;
	}

	//step in cicrular array backwards
	int CircularBackward(int i, int cap) {
		return (i - 1 + cap) % cap;
	}

	//Reset function 
	void Reset() {
		delete[] data;
		data = nullptr;
	}

	void Resize() {
		int new_capacity = capacity * 2;
		T* new_data = new T[new_capacity];
		for (int i = 0; i < size; ++i) {
			new_data[i] = data[(front + i) % capacity];
		}
		delete[] data;
		data = new_data;
		front = 0;
		back = size;
		capacity = new_capacity;
	}

public:
	//constructor
	Deque() :
		front(0),
		back(0),
		capacity(8),
		size(0)
	{
		data = new T[capacity];
	}

	//overloaded constructor
	Deque(int cap) :
		front(0),
		back(0),
		capacity(cap),
		size(0)
	{
		data = new T[capacity];
	}

	//copy constructor
	Deque(const Deque<T>& other) :
		size(other.size),
		capacity(other.capacity)
	{
		if (this != &other) {
			Reset();
			data = new T[capacity];
			//deep copy elements from front to end
			for (int i = 0; i < size; ++i) {
				data[i] = other.data[(other.front + i) % other.capacity];
			}
			front = 0;
			back = size;
		}
		
	}


	//copy assignment
	Deque& operator=(const Deque<T>& other) {
		if (this != &other) {
			Reset();
			size = other.size;
			capacity = other.capacity;
			data = new T[capacity];
			//deep copy elements from front to end
			for (int i = 0; i < size; ++i) {
				data[i] = other.data[(other.front + i) % other.capacity];
			}
			front = 0;
			back = size - 1;
		}
		return *this;
	}

	//destructor
	~Deque() {
		Reset();
	}


	bool IsEmpty() const {
		return (size == 0);
	}


	bool IsFull() const {
		return (size == capacity);
	}


	


	void PushForward(T value) {
		if (IsFull()) {
			Resize();
		}
		front = (CircularBackward(front, capacity));
		data[front] = value;
		size++;
	}

	void PushBack(T value) {
		if (IsFull()) {
			Resize();
		}
		data[back] = value;
		back = CirciularForward(back, capacity);
		size++;
	}


	void PopForward() {
		if (IsEmpty()) {
			std::cout << "Container is empty, nothing to pop!\n";
			return;
		}	
		front = CirciularForward(front, capacity);
		size--;
	}

	void PopBack() {
		if (IsEmpty()) {
			std::cout << "Container is empty, nothing to pop!\n";
			return;
		}
		back = CircularBackward(back, capacity);
		size--;
	}

	T GetFront() {
		if (IsEmpty()) {
			std::cout << "Container is empty!\n";
			return -1;
		}
		return data[front];
	}

	T GetBack() {
		if (IsEmpty()) {
			std::cout << "Container is empty!\n";
			return -1;
		}
		return data[CircularBackward(back, capacity)];
	}

	int GetSize() {
		return size;
	}

	int GetCapacity() {
		return capacity;
	}

};

