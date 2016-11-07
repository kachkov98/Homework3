#include <cassert>
#include "matrix.h"

namespace LinearAlgebra
{
Matrix::Matrix (std::size_t width, std::size_t height):
	width_(width),
	height_(height),
	rows_(nullptr)
{
	if (height)
		rows_ = new Vector[height_];
	for (std::size_t i = 0; i < height_; i++)
		rows_[i].SetSize(width);
}

Matrix::Matrix (const std::initializer_list<Vector> &matrix):
	width_(0),
	height_(matrix.size()),
	rows_(nullptr)
{
	if (height_)
	{
		rows_ = new Vector[height_];
		std::copy (matrix.begin(), matrix.end(), rows_);
		width_ = rows_[0].GetSize();
	}
}

Matrix::Matrix (const Matrix& rhs):
	width_(rhs.width_),
	height_(rhs.height_),
	rows_(nullptr)
{
	if (height_)
	{
		rows_ = new Vector[height_];
		std::copy (rhs.rows_, rhs.rows_ + height_, rows_);
	}
}

Matrix& Matrix::operator= (const Matrix& rhs)
{
	if (this == &rhs)
		return *this;
	Vector *rows = nullptr;
	if (rhs.rows_)
	{
		rows = new Vector[rhs.height_];
		std::copy (rhs.rows_, rhs.rows_ + rhs.height_, rows);
	}
	delete[] rows_;
	width_ = rhs.width_;
	height_ = rhs.height_;
	rows_ = rows;
	return *this;
}

std::size_t Matrix::GetWidth () const
{
	assert (CheckSquareness());
	return width_;
}

std::size_t Matrix::GetHeight () const
{
	return height_;
}

void Matrix::SetWidth (std::size_t width)
{
	assert (CheckSquareness());
	if (width == width_)
		return;
	for (std::size_t i = 0; i < height_; i++)
		rows_[i].SetSize(width);
	width_ = width;
}

void Matrix::SetHeight (std::size_t height)
{
	if (height == height_)
		return;
	Vector *rows = new Vector[height];
	if (height < height_)
		std::copy (rows_, rows_ + height, rows);
	else
	{
		std::copy (rows_, rows_ + height_, rows);
		for (std::size_t i = height_; i < height; i++)
			rows[i].SetSize(width_);
	}
	delete [] rows_;
	height_ = height;
	rows_ = rows;
}

void Matrix::Print (std::ostream& ostream) const
{
	for (std::size_t i = 0; i < height_; i++)
		ostream << rows_[i] << std::endl;
}

const Vector& Matrix::operator[] (std::size_t row) const
{
	assert(row < height_);
	return rows_[row];
}

Vector& Matrix::operator[] (std::size_t row)
{
	return const_cast<Vector&>(static_cast<const Matrix&>(*this)[row]);
}

Matrix& Matrix::operator*= (double rhs)
{
	for (std::size_t i = 0; i < height_; i++)
		rows_[i] *= rhs;
	return *this;
}

void Matrix::Insert (std::size_t row, std::size_t column, const Matrix& matrix)
{
	assert (row + matrix.height_ <= height_);
	for (std::size_t i = 0; i < matrix.height_; i++)
		rows_[row + i].Insert (column, matrix[i]);
}

bool Matrix::CheckSquareness () const
{
	for (std::size_t i = 0; i < height_; i++)
		if (rows_[i].GetSize() != width_)
			return false;
	return true;
}

Matrix::~Matrix ()
{
	delete[] rows_;
}

std::ostream& operator<< (std::ostream& ostream, const Matrix& matrix)
{
	matrix.Print (ostream);
	return ostream;
}

Matrix operator* (const Matrix& lhs, double rhs)
{
	Matrix tmp = lhs;
	tmp *= rhs;
	return tmp;
}

Matrix operator* (double lhs, const Matrix& rhs)
{
	Matrix tmp = rhs;
	tmp *= lhs;
	return tmp;
}

Matrix KroneckerProduct (const Matrix& lhs, const Matrix& rhs)
{
	assert(lhs.CheckSquareness() && rhs.CheckSquareness());
	Matrix ans (lhs.GetWidth() * rhs.GetWidth(), lhs.GetHeight() * rhs.GetHeight());
	for (std::size_t i = 0; i < lhs.GetHeight(); i++)
		for (std::size_t j = 0; j < lhs.GetWidth(); j++)
			ans.Insert(i * rhs.GetHeight(), j * rhs.GetWidth(), lhs[i][j] * rhs);
	return ans;
}
}
