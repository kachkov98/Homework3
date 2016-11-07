#pragma once
#include <initializer_list>
#include <iostream>
#include <cstddef>

namespace LinearAlgebra
{
class Vector
{
public:
	explicit Vector (std::size_t size = 0) ;
	Vector (const std::initializer_list<double>& vector);
	Vector (const Vector& rhs);
	Vector& operator= (const Vector& rhs);
	std::size_t GetSize () const;
	void SetSize (std::size_t size);
	void Print (std::ostream& ostream) const;
	const double& operator[] (std::size_t position) const;
	double& operator[] (std::size_t position);
	Vector& operator+= (const Vector& rhs);
	Vector& operator*= (double rhs);
	void Insert (std::size_t position, const Vector& vector);
	~Vector ();
private:
	std::size_t size_;
	double *vector_;
};

std::ostream& operator<< (std::ostream& ostream, const Vector& vector);
Vector operator+ (const Vector& lhs, const Vector& rhs);
Vector operator* (const Vector& lhs, double rhs);
Vector operator* (double lhs, const Vector& rhs);
}
