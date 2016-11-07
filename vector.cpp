#include <algorithm>
#include <iomanip>
#include <cassert>
#include "vector.h"

namespace LinearAlgebra
{
Vector::Vector (std::size_t size):
	size_(size),
	vector_(nullptr)
{
	if (size_)
		vector_ = new double[size_]();
}

Vector::Vector (const std::initializer_list<double>& vector):
	size_(vector.size()),
	vector_(nullptr)
{
	if (size_)
	{
		vector_ = new double[size_];
		std::copy (vector.begin(), vector.end(), vector_);
	}
}

Vector::Vector (const Vector& rhs):
	size_(rhs.size_),
	vector_(nullptr)
{
	if (size_)
	{
		vector_ = new double[size_];
		std::copy (rhs.vector_, rhs.vector_ + size_, vector_);
	}
}

Vector& Vector::operator= (const Vector& rhs)
{
	if (this == &rhs)
		return *this;
	double *vector = nullptr;
	if (rhs.vector_)
	{
		vector = new double[rhs.size_];
		std::copy (rhs.vector_, rhs.vector_ + rhs.size_, vector);
	}
	delete[] vector_;
	size_ = rhs.size_;
	vector_ = vector;
	return *this;
}

std::size_t Vector::GetSize() const
{
	return size_;
}

void Vector::SetSize (std::size_t size)
{
	if (size == size_)
		return;
	double *vector = new double[size]();
	std::copy (vector_, vector_ + std::min(size, size_), vector);
	delete[] vector_;
	size_ = size;
	vector_ = vector;
}

void Vector::Print (std::ostream& ostream) const
{
	for (std::size_t i = 0; i < size_; i++)
		ostream << std::setw (3) << vector_[i] << " ";
}

const double& Vector::operator[] (std::size_t position) const
{
	assert(position < size_);
	return vector_[position];
}

double& Vector::operator[] (std::size_t position)
{
	return const_cast<double&>(static_cast<const Vector&>(*this)[position]);
}

Vector& Vector::operator+= (const Vector& rhs)
{
	assert (size_ == rhs.size_);
	for (std::size_t i = 0; i < size_; i++)
		vector_[i] += rhs.vector_[i];
	return *this;
}

Vector& Vector::operator*= (double rhs)
{
	for (std::size_t i = 0; i < size_; i++)
		vector_[i] *= rhs;
	return *this;
}

void Vector::Insert (std::size_t position, const Vector& vector)
{
	assert (position + vector.size_ <= size_);
	for (std::size_t i = 0; i  < vector.size_; i++)
		vector_[position + i] = vector[i];
}

Vector::~Vector()
{
	delete[] vector_;
}

std::ostream& operator<< (std::ostream& ostream, const Vector& vector)
{
	vector.Print(ostream);
	return ostream;
}

Vector operator+ (const Vector& lhs, const Vector& rhs)
{
	Vector tmp = lhs;
	tmp += rhs;
	return tmp;
}

Vector operator* (const Vector& lhs, double rhs)
{
	Vector tmp = lhs;
	tmp *= rhs;
	return tmp;
}

Vector operator* (double lhs, const Vector& rhs)
{
	Vector tmp = rhs;
	tmp *= lhs;
	return tmp;
}
}
