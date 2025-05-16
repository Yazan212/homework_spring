
#include "Deque.h"
#include "Stack.h"
#include "Matrix.h"
#include <iostream>
#include "GenericPrint.h"
#include "String.h"
#include "SharedPointer.h"
#include <memory>

int main() {


	std::cout << "Deque Testing\n";
	{
		//Deque testing:
		Deque<int> deque(8);
		deque.PushForward(1);
		deque.PushForward(2);
		deque.PushForward(3);
		deque.PushForward(4);
		deque.PushForward(5);
		deque.PushForward(6);
		deque.PushBack(10);
		deque.PushBack(9);
		Deque<int> deque2(deque);
		deque.PushBack(8);
		deque.PushBack(7);
		while (!deque.IsEmpty()) {
			std::cout << deque.GetFront() << "\n";
			std::cout << deque.GetBack() << "\n";
			deque.PopForward();
			deque.PopBack();
		}
		std::cout << "---------------------\n";
		while (!deque2.IsEmpty()) {
			std::cout << deque2.GetFront() << "\n";
			std::cout << deque2.GetBack() << "\n";
			deque2.PopForward();
			deque2.PopBack();
		}
	}
	

	
	std::cout << "******************************\nStack testing\n";
	//Stack testing
	{
		Stack<int> st;
		st.Push(1);
		st.Push(2);
		st.Push(3);
		auto st2 = st;
		st.Push(4);
		while (!st.IsEmpty()) {
			std::cout << st.Top() << "\n";
			st.Pop();
		}
		std::cout << "-------------\n";
		while (!st2.IsEmpty()) {
			std::cout << st2.Top() << "\n";
			st2.Pop();
		}
	}

	std::cout << "***********************\nMatrix testing\n";
	{
		Matrix<int, 2, 3> mt1 = { 1,2,3,
								  4,5,6 };

		Matrix<int, 3, 3> mt2 = { 1,2,3,
								  4,5,6,
								  7,8,9 };
		auto sum = mt1 + mt1 * 2;
		auto mul = mt1 * mt2;
		sum.print();
		mul.print();
		auto tr = Trace(mt2);
		std::cout << "trace of mt1 is : " << tr << '\n';
		std::cout << "Transpose of mt1 is : \n";
		auto T = Transpose<int,2,3>(mt1);
		T.print();
	}


	std::cout << "***********************\nGeneric Print Testing\n";
	{
		int x = 1;
		double y = 2.24;
		print(5, "hello", x, y, 'c');
	}
	
	std::cout << "***********************\nSmall String Testing\n";
	{
		const char* str = "hello";
		String st(str);
		std::cout << st[0];
		std::cout << st.c_str();
		String st2("helloThereIamALongString");
		String st3 = st2 + st;
		std::cout << st3.c_str();
	}
	


	

	return 0;
}