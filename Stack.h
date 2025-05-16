#pragma once

#include "Deque.h"

template<typename T>
class Stack {
private:
	Deque<T> deque;


public:
	Stack() = default;

	//copy constructor
	Stack(const Stack& other) : deque(other.deque){}

	//copy assignment
	Stack& operator=(const Stack& other) {
		deque = other.deque;
	}

	void Push(T value) {
		deque.PushBack(value);
	}

	void Pop() {
		deque.PopBack();
	}

	T Top() {
		return deque.GetBack();
	}

	int GetSize() {
		return deque.GetSize();
	}

	bool IsEmpty() {
		return deque.IsEmpty();
	}

};
