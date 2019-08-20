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
		this->doRotation<NROTATIONS-1>(asset);
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
	void doRotation(const char (&asset)[WIDTH][WIDTH])
	{
		this->rotate<ROTATION>(asset);
		this->doRotation<ROTATION-1>(asset);
	}

	template<int ROTATE>
	void rotate(const char (&asset)[WIDTH][WIDTH])
	{
		for (int ii=0; ii<WIDTH; ii++)
		{
			for (int jj=0; jj<WIDTH; jj++)
			{
				Index index = this->getRotatedIndices(ii, jj, ROTATE);
				this->assets[ROTATE][index.x][index.y] = asset[ii][jj];
			}
		}
	}

	Index getRotatedIndices(const int& x, const int& y, const int& rotate)
	{
		switch (rotate)
		{
			case 0: return {x, y};
			case 1: return {x, y};
			case 2: return {x, y};
			case 3: return {x, y};
			default: throw std::runtime_error("bad rotation");
		}
	}	
};

template<>
void Piece::doRotation<0>(const char (&asset)[WIDTH][WIDTH])
{
	this->rotate<0>(asset);
}