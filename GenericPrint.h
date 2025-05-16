#pragma once
#include <iostream>
#include <utility>



void print() {
	std::cout << "\n";
}

template<typename T, typename... Args>
void print(T&& first, Args&&... rest) {
	std::cout << std::forward<T>(first) << " ";
	print(std::forward<Args>(rest)...);
}