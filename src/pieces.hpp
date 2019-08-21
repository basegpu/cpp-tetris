#pragma once

#include <stdexcept>

#define WIDTH 5
#define NROTATIONS 4


class Piece
{
public:
	Piece(const char (&asset)[WIDTH][WIDTH])
	{
		this->rotateRecursion<NROTATIONS-1>(asset);
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
	void rotateRecursion(const char (&asset)[WIDTH][WIDTH])
	{
		this->doRotation<ROTATION>(asset);
		this->rotateRecursion<ROTATION-1>(asset);
	}

	template<int ROTATION>
	void doRotation(const char (&asset)[WIDTH][WIDTH])
	{
		this->assetInitializationRecursion<WIDTH*WIDTH-1>(asset, ROTATION);
	}

	template<int INDEX>
	void assetInitializationRecursion(const char (&asset)[WIDTH][WIDTH], const int& rotation)
	{
		this->doAssetInitialization<INDEX>(asset, rotation);
		this->assetInitializationRecursion<INDEX-1>(asset, rotation);
	}

	template<int INDEX>
	void doAssetInitialization(const char (&asset)[WIDTH][WIDTH], const int& rotation)
	{
		int ii = INDEX / WIDTH;
		int jj = INDEX % WIDTH;
		char v = asset[ii][jj];
		this->rotateIndices(ii, jj, rotation);
		this->assets[rotation][ii][jj] = v;
	}

	void rotateIndices(int& x, int& y, const int& rotation)
	{
		int ii = x;
		int jj = y;
		switch (rotation)
		{
			case 0: break;
			case 1: x = jj; y = WIDTH-1-ii; break;
			case 2: x = WIDTH-1-ii; y = WIDTH-1-jj; break;
			case 3: x = WIDTH-1-jj, y = ii; break;
			default: throw std::runtime_error("bad rotation");
		}
	}	
};

template<>
void Piece::rotateRecursion<0>(const char (&asset)[WIDTH][WIDTH])
{
	this->doRotation<0>(asset);
}

template<>
void Piece::assetInitializationRecursion<0>(const char (&asset)[WIDTH][WIDTH], const int& rotation)
{
	this->doAssetInitialization<0>(asset, rotation);
}