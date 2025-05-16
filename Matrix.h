#pragma once
#include <memory>


template <typename T, int Rows, int Columns>
class Matrix {
private:
	std::unique_ptr<T[]> matrix;
	

public:

	static constexpr int ROWS = Rows;
	static constexpr int COLUMNS = Columns;


	//constructor
	Matrix():matrix(std::make_unique<T[]>(Rows * Columns)) {}

	//Constructor 
	Matrix(std::initializer_list<T> list) : Matrix() {
		//check dimesions 
		if (list.size() != Rows * Columns) {
			throw std::runtime_error("dimensions did not match the initializer list\n");
		}
		//static_assert(sz == Rows * Columns, "Initializer list dimensions doesn't match the dimension of the matrix!\n");
		std::copy(list.begin(), list.end(), matrix.get());
	}

	//copy constructor
	Matrix(const Matrix& other) :
	Matrix() {
		std::copy(other.matrix.get(), other.matrix.get() + (Rows * Columns), matrix.get());
	}


	
	//move constructor 
	Matrix(Matrix&& other) : matrix(std::move(other.matrix)) {}

	// Move Assignment 
	Matrix& operator=(Matrix&& other) {
		matrix = std::move(other.matrix);
		return *this;
	}

	//Copy assignment
	Matrix& operator=(const Matrix& other) {
		matrix = std::make_unique<T[]>(Rows * Columns);
		std::copy(other.matrix.get(), other.matrix.get() + (Rows * Columns), matrix.get());
		return *this;
	}

	//At operation
	T& operator()(int i, int j) {
		//assert boundaries
		if (i >= Rows || j >= Columns) {
			throw std::runtime_error("index out of bound!\n");
		}
		return matrix[i * Columns + j];
	}

	const T& operator()(int i, int j) const {
		//assert boundaries
		static_assert(i < Rows && j < Columns, "index out of bound!\n");
		return matrix[i * Columns + j];
	}

	//scalar multiplication
	template<int R = Rows, int C = Columns>
	Matrix<T,R,C> operator*(const T& value) {
		Matrix<T, R, C> answer;
		for (int i = 0; i < R * C; ++i) {
			answer.matrix[i] = value * matrix[i];
		}
		return answer;
	}


	//Addition
	template<int R = Rows, int C = Columns>
	Matrix<T,R,C> operator+(const Matrix<T,R,C>& rhs) {
		//check boundaries 
		static_assert(R == Rows && C == Columns, "Dimensions must match to perform addition!\n");
		
		Matrix<T, R, C> answer;
		for (int i = 0; i < R * C; ++i) {
			answer.matrix[i] = matrix[i] + rhs.matrix[i];
		}
		return answer;
	}

	//Subtraction
	template<int R = Rows, int C = Columns>
	Matrix<T, R, C> operator-(const Matrix<T, R, C>& rhs) {
		//check boundaries 
		static_assert(R == Rows && C == Columns, "Dimensions must match to perform addition!\n");
		
		Matrix<T, R, C> answer;
		for (int i = 0; i < R * C; ++i) {
			answer.matrix[i] = matrix[i] - rhs.matrix[i];
		}
		return answer;

	}

	//Multiplication
	template<int R = Rows, int C = Columns>
	Matrix<T, Rows, C> operator*( Matrix<T, R, C>& rhs)  {
		static_assert(Columns == R, "Matrices are not compatible for multiplcation!\n");
		Matrix<T, Rows, C> answer;
		for (int i = 0; i < Rows; ++i) {
			for (int j = 0; j < C; ++j) {
				answer(i, j) = T();
				for (int k = 0; k < Columns; ++k) {
					answer(i, j) += (*this)(i, k) * rhs(k, j);
				}
			}
		}
		return answer;
	}

	void print() const {
		for (int i = 0; i < Rows * Columns; ++i) {
			std::cout << matrix[i] << " ";
			if ((i + 1) % Columns == 0) {
				std::cout << "\n";
			}
		}
		std::cout << "\n";
	}
};




//universal transpose function 
template<typename T, int Rows, int Columns, typename Mat>
Matrix<T, Columns, Rows> Transpose(Mat&& matrix) {
	Matrix<T, Columns, Rows> answer;
	for (int i = 0; i < Rows; ++i) {
		for (int j = 0; j < Columns; ++j) {
			answer(j, i) = std::forward<Mat>(matrix)(i, j);
		}
	}
	return answer;
}



//lambda trace 
auto Trace = [](auto& matrix) {
	using matType = std::decay_t<decltype(matrix)>;

	static_assert(matType::ROWS == matType::COLUMNS, "trace only for square matrices!\n");
	using T = std::decay_t<decltype(matrix(0, 0))>;
	T sum{};
	for (int i = 0; i < matType::ROWS; ++i) {
		sum += matrix(i, i);
	}
	return sum;
};