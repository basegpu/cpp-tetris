#pragma once

#include <stdexcept>

#define WIDTH 5
#define NROTATIONS 4

typedef struct
{
	int x;
	int y;
} Index;


class Piece
{
public:
	Piece(const char (&asset)[WIDTH][WIDTH])
	{
		this->rotate<NROTATIONS-1>(asset);
	}

	char getShape(const int& rotation, const int& x, const int& y) const
	{
		if (rotation < NROTATIONS)
		{
			return this->assets[rotation][x][y];
		}
		else
		{
			throw std::runtime_error("bad rotation");
		}
	}

private:

	char assets[NROTATIONS][WIDTH][WIDTH];

	template<int ROTATION>
	void rotate(const char (&asset)[WIDTH][WIDTH])
	{
		this->doRotation<ROTATION>(asset);
		this->rotate<ROTATION-1>(asset);
	}

	template<int ROTATE>
	void doRotation(const char (&asset)[WIDTH][WIDTH])
	{
		this->initAsset<WIDTH*WIDTH-1>(asset, ROTATE);
	}

	template<int ISHAPE>
	void initAsset(const char (&asset)[WIDTH][WIDTH], const int& rotation)
	{
		int ii = ISHAPE / WIDTH;
		int jj = ISHAPE % WIDTH;
		Index index = this->getRotatedIndices(ii, jj, rotation);
		this->assets[rotation][index.x][index.y] = asset[ii][jj];
		this->initAsset<ISHAPE-1>(asset, rotation);
	}

	Index getRotatedIndices(const int& x, const int& y, const int& rotation)
	{
		switch (rotation)
		{
			case 0: return {x, y};
			case 1: return {y, WIDTH-1-x};
			case 2: return {WIDTH-1-x, WIDTH-1-y};
			case 3: return {WIDTH-1-y, x};
			default: throw std::runtime_error("bad rotation");
		}
	}	
};

template<>
void Piece::rotate<0>(const char (&asset)[WIDTH][WIDTH])
{
	this->doRotation<0>(asset);
}

template<>
void Piece::initAsset<0>(const char (&asset)[WIDTH][WIDTH], const int& rotation)
{
	Index index = this->getRotatedIndices(0, 0, rotation);
	this->assets[rotation][index.x][index.y] = asset[0][0];
}