#ifndef TETRIMINO_H
#define TETRIMINO_H

#include "globals.hpp"
#include <algorithm>


class Tetrimino
{
public:

	enum class Type : unsigned char {
		Square,
		Line,
		RightHook,
		LeftHook,
		Tee,
		RightChair,
		LeftChair
	};

	static Tetrimino Make(const Type& type);
	static const size_t BlocksPerPiece;

	unsigned char GetShape(const int& rotation, const int& x, const int& y) const;
	int GetTopBlock(const int& rotation) const;
	int GetLeftBlock(const int& rotation) const;

protected:

	Tetrimino(const unsigned char (&shape)[TETRIMINO_WIDTH][TETRIMINO_WIDTH]);


private:

	unsigned char shapes[TETRIMINO_NROTATIONS][TETRIMINO_WIDTH][TETRIMINO_WIDTH];
	int topleftBlock[TETRIMINO_NROTATIONS][2];

	template<int ROTATION>
	void RotateRecursion(const unsigned char (&shape)[TETRIMINO_WIDTH][TETRIMINO_WIDTH])
	{
		this->DoRotation<ROTATION>(shape);
		this->RotateRecursion<ROTATION-1>(shape);
	}

	template<int ROTATION>
	void DoRotation(const unsigned char (&shape)[TETRIMINO_WIDTH][TETRIMINO_WIDTH])
	{
		this->AssetInitializationRecursion<TETRIMINO_WIDTH*TETRIMINO_WIDTH-1>(shape, ROTATION);
		int x = TETRIMINO_WIDTH;
		int y = TETRIMINO_WIDTH;
		this->TopLeftPositionRecursion<TETRIMINO_WIDTH*TETRIMINO_WIDTH-1>(x, y, ROTATION);
		this->topleftBlock[ROTATION][0] = x;
		this->topleftBlock[ROTATION][1] = y;
	}

	template<int INDEX>
	void AssetInitializationRecursion(const unsigned char (&shape)[TETRIMINO_WIDTH][TETRIMINO_WIDTH], const int& rotation)
	{
		this->DoAssetInitialization<INDEX>(shape, rotation);
		this->AssetInitializationRecursion<INDEX-1>(shape, rotation);
	}

	template<int INDEX>
	void TopLeftPositionRecursion(int& x, int& y, const int& rotation)
	{
		this->CheckIfTopLeft<INDEX>(x, y, rotation);
		this->TopLeftPositionRecursion<INDEX-1>(x, y, rotation);
	}

	template<int INDEX>
	void DoAssetInitialization(const unsigned char (&shape)[TETRIMINO_WIDTH][TETRIMINO_WIDTH], const int& rotation)
	{
		// row and column indices
		int ii, jj;
		this->Transform2XY<INDEX>(ii, jj);
		// reference value
		unsigned char v = shape[ii][jj];
		// lambda function for inverse index
		auto invIndex = [](int& index) { index = TETRIMINO_WIDTH-1-index; };
		// do rotation
		switch (rotation % TETRIMINO_NROTATIONS)
		{
			case 0: break;
			case 1: std::swap(ii,jj); invIndex(jj); break;
			case 2: invIndex(ii); invIndex(jj); break;
			case 3: std::swap(ii,jj); invIndex(ii); break;
		}
		// assign rotated values
		this->shapes[rotation][ii][jj] = v;
	}

	template<int INDEX>
	void CheckIfTopLeft(int& x, int& y, const int& rotation)
	{
		// row and column indices
		int ii, jj;
		this->Transform2XY<INDEX>(ii, jj);
		// only check if not empty
		if (this->shapes[rotation][ii][jj] != 0)
		{
			x = std::min(x, ii);
			y = std::min(y, jj);
		}
	}

	template<int INDEX>
	void Transform2XY(int& x, int& y)
	{
		x = INDEX / TETRIMINO_WIDTH;
		y = INDEX % TETRIMINO_WIDTH;
	}
};

#endif // TETRIMINO_H
