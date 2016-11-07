#pragma once
#include "vector.h"

namespace LinearAlgebra
{
class Matrix
{
public:
	explicit Matrix (std::size_t width = 0, std::size_t height = 0);
	Matrix (const std::initializer_list<Vector> &matrix);
	Matrix (const Matrix& rhs);
	Matrix& operator= (const Matrix& rhs);
	std::size_t GetWidth () const;
	std::size_t GetHeight () const;
	void SetWidth (std::size_t width);
	void SetHeight (std::size_t height);
	void Print (std::ostream& ostream) const;
	const Vector& operator[] (std::size_t row) const;
	Vector& operator[] (std::size_t row);
	Matrix& operator*= (double rhs);
	void Insert (std::size_t row, std::size_t column, const Matrix& matrix);
	bool CheckSquareness () const;
	~Matrix ();
private:
	std::size_t width_, height_;
	Vector *rows_;
};

std::ostream& operator<< (std::ostream& ostream, const Matrix& matrix);
Matrix operator* (const Matrix& lhs, double rhs);
Matrix operator* (double lhs, const Matrix& rhs);
Matrix KroneckerProduct (const Matrix& lhs, const Matrix& rhs);
}
