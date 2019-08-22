#pragma once

#include <stdexcept>
#include <algorithm>

#define WIDTH 4
#define NROTATIONS 4


class Piece
{
public:

	enum class Type : unsigned char {
		None,
		Square,
		Line
	};

	Piece(const unsigned char (&asset)[WIDTH][WIDTH])
	{
		this->rotateRecursion<NROTATIONS-1>(asset);
	}

	unsigned char getShape(const int& rotation, const int& x, const int& y) const
	{
		return this->assets[rotation % NROTATIONS][x][y];
	}

private:

	unsigned char assets[NROTATIONS][WIDTH][WIDTH];

	template<int ROTATION>
	void rotateRecursion(const unsigned char (&asset)[WIDTH][WIDTH])
	{
		this->doRotation<ROTATION>(asset);
		this->rotateRecursion<ROTATION-1>(asset);
	}

	template<int ROTATION>
	void doRotation(const unsigned char (&asset)[WIDTH][WIDTH])
	{
		this->assetInitializationRecursion<WIDTH*WIDTH-1>(asset, ROTATION);
	}

	template<int INDEX>
	void assetInitializationRecursion(const unsigned char (&asset)[WIDTH][WIDTH], const int& rotation)
	{
		this->doAssetInitialization<INDEX>(asset, rotation);
		this->assetInitializationRecursion<INDEX-1>(asset, rotation);
	}

	template<int INDEX>
	void doAssetInitialization(const unsigned char (&asset)[WIDTH][WIDTH], const int& rotation)
	{
		// row and column indices
		int ii = INDEX / WIDTH;
		int jj = INDEX % WIDTH;
		// reference value
		unsigned char v = asset[ii][jj];
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
		this->assets[rotation][ii][jj] = v;
	}
};

template<>
void Piece::rotateRecursion<0>(const unsigned char (&asset)[WIDTH][WIDTH])
{
	this->doRotation<0>(asset);
}

template<>
void Piece::assetInitializationRecursion<0>(const unsigned char (&asset)[WIDTH][WIDTH], const int& rotation)
{
	this->doAssetInitialization<0>(asset, rotation);
}


Piece makePiece(const Piece::Type& type)
{
	switch (type)
	{
		case Piece::Type::Square: return Piece({
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0},
		});
		case Piece::Type::Line: return Piece({
			{0,0,1,0},
			{0,0,1,0},
			{0,0,1,0},
			{0,0,1,0},
		});
		default: throw std::runtime_error("piece type not known");
	}
}