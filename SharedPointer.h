#pragma once

#include <functional>
template <typename T>
struct DefaultDeleter {
	void operator()(T* ptr) {
		std::cout << "Called Default deleter! \n";
		delete ptr;
	}
};


template<typename T, typename Deleter = DefaultDeleter<T> >
class SharedPointer {
private:
	T* ptr;
	int* ref_count;
	
public:
	SharedPointer(T* pt = nullptr) :
		ptr(pt)
	{
		if (pt) {
			ref_count = new int(1);
		}
		else {
			ref_count = nullptr;
		}
	}


	//copy constructor
	SharedPointer(const SharedPointer& sh_ptr) :
		ptr(sh_ptr.ptr), ref_count(sh_ptr.ref_count) {
		std::cout << "Called Copy constructor\n";
		if (ref_count) {
			(*ref_count)++;
		}
	}

	//move constructor
	SharedPointer(SharedPointer&& sh_ptr)  :
	ptr(sh_ptr.ptr), ref_count(sh_ptr.ref_count){
		std::cout << "Called copy constructor\n";
		sh_ptr.ptr = nullptr;
		sh_ptr.ref_count = nullptr;
	}

	//copy assignment 
	SharedPointer& operator=(const SharedPointer& sh_ptr)
	{
		if (this != &sh_ptr) {
			reset();
			ptr = sh_ptr.ptr;
			ref_count = sh_ptr.ref_count;
			if (ref_count) {
				(*ref_count)++;
			}
		}
		return *this;
	}

	//move assignment 
	SharedPointer& operator=(SharedPointer&& sh_ptr) {
		if (this != &sh_ptr) {
			ptr = sh_ptr.ptr;
			ref_count = sh_ptr.ref_count;
			if (ref_count) {
				(*ref_count)++;
			}
			sh_ptr.ptr = nullptr;
			sh_ptr.ref_count = nullptr;
		}
		return *this;
	}
		

	//destructor
	~SharedPointer() {
		std::cout << "Called Desctructor\n";
		reset();

	}


	T& operator[](int i) {
		return ptr[i];
	}



	T* get() const {
		return ptr;
	}


	int use_count() const {
		return ref_count ? (*ref_count) : 0;
	}



private:
	void reset() {
		if (ref_count && --(*ref_count) == 0) {
			Deleter{}(ptr);
			delete ref_count;
		}
		ref_count = nullptr;
		ptr = nullptr;
	}
};