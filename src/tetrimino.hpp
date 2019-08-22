#pragma once

#include <stdexcept>
#include <algorithm>

#define WIDTH 4
#define NROTATIONS 4


class Tetrimino
{
public:

	enum class Type : unsigned char {
		None,
		Square,
		Line,

	};

	Tetrimino(const unsigned char (&shape)[WIDTH][WIDTH])
	{
		this->rotateRecursion<NROTATIONS-1>(shape);
	}

	unsigned char getShape(const int& rotation, const int& x, const int& y) const
	{
		return this->shapes[rotation % NROTATIONS][x][y];
	}

private:

	unsigned char shapes[NROTATIONS][WIDTH][WIDTH];

	template<int ROTATION>
	void rotateRecursion(const unsigned char (&shape)[WIDTH][WIDTH])
	{
		this->doRotation<ROTATION>(shape);
		this->rotateRecursion<ROTATION-1>(shape);
	}

	template<int ROTATION>
	void doRotation(const unsigned char (&shape)[WIDTH][WIDTH])
	{
		this->assetInitializationRecursion<WIDTH*WIDTH-1>(shape, ROTATION);
	}

	template<int INDEX>
	void assetInitializationRecursion(const unsigned char (&shape)[WIDTH][WIDTH], const int& rotation)
	{
		this->doAssetInitialization<INDEX>(shape, rotation);
		this->assetInitializationRecursion<INDEX-1>(shape, rotation);
	}

	template<int INDEX>
	void doAssetInitialization(const unsigned char (&shape)[WIDTH][WIDTH], const int& rotation)
	{
		// row and column indices
		int ii = INDEX / WIDTH;
		int jj = INDEX % WIDTH;
		// reference value
		unsigned char v = shape[ii][jj];
		// lambda function for inverse index
		auto invIndex = [](int& index) { index = WIDTH-1-index; };
		// do rotation
		switch (rotation % NROTATIONS)
		{
			case 0: break;
			case 1: std::swap(ii,jj); invIndex(jj); break;
			case 2: invIndex(ii); invIndex(jj); break;
			case 3: std::swap(ii,jj); invIndex(ii); break;
		}
		// assign rotated values
		this->shapes[rotation][ii][jj] = v;
	}
};

template<>
void Tetrimino::rotateRecursion<0>(const unsigned char (&shape)[WIDTH][WIDTH])
{
	this->doRotation<0>(shape);
}

template<>
void Tetrimino::assetInitializationRecursion<0>(const unsigned char (&shape)[WIDTH][WIDTH], const int& rotation)
{
	this->doAssetInitialization<0>(shape, rotation);
}


Tetrimino makePiece(const Tetrimino::Type& type)
{
	switch (type)
	{
		case Tetrimino::Type::Square: return Tetrimino({
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0},
		});
		case Tetrimino::Type::Line: return Tetrimino({
			{0,0,1,0},
			{0,0,1,0},
			{0,0,1,0},
			{0,0,1,0},
		});
		default: throw std::runtime_error("piece type not known");
	}
}