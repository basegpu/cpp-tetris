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

	static Tetrimino* Make(const Type& type);
	static const size_t BlocksPerPiece;
	static const size_t NumberOfRotations;
	static const size_t NumberOfTypes;

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
		int top = TETRIMINO_WIDTH;
		int left = TETRIMINO_WIDTH;
		this->TopLeftPositionRecursion<TETRIMINO_WIDTH*TETRIMINO_WIDTH-1>(top, left, ROTATION);
		this->topleftBlock[ROTATION][0] = top;
		this->topleftBlock[ROTATION][1] = left;
	}

	template<int INDEX>
	void AssetInitializationRecursion(const unsigned char (&shape)[TETRIMINO_WIDTH][TETRIMINO_WIDTH], const int& rotation)
	{
		this->DoAssetInitialization<INDEX>(shape, rotation);
		this->AssetInitializationRecursion<INDEX-1>(shape, rotation);
	}

	template<int INDEX>
	void TopLeftPositionRecursion(int& top, int& left, const int& rotation)
	{
		this->CheckIfTopLeft<INDEX>(top, left, rotation);
		this->TopLeftPositionRecursion<INDEX-1>(top, left, rotation);
	}

	template<int INDEX>
	void DoAssetInitialization(const unsigned char (&shape)[TETRIMINO_WIDTH][TETRIMINO_WIDTH], const int& rotation)
	{
		// row and column indices
		int row, col;
		this->Transform2RowCol<INDEX>(row, col);
		// reference value
		unsigned char v = shape[row][col];
		// lambda function for inverse index
		auto invIndex = [](int& index) { index = TETRIMINO_WIDTH-1-index; };
		// do rotation
		switch (rotation % TETRIMINO_NROTATIONS)
		{
			case 0: break;
			case 1: std::swap(row,col); invIndex(col); break;
			case 2: invIndex(row); invIndex(col); break;
			case 3: std::swap(row,col); invIndex(row); break;
		}
		// assign rotated values
		this->shapes[rotation][row][col] = v;
	}

	template<int INDEX>
	void CheckIfTopLeft(int& top, int& left, const int& rotation)
	{
		// row and column indices
		int row, col;
		this->Transform2RowCol<INDEX>(row, col);
		// only check if not empty
		if (this->shapes[rotation][row][col] != 0)
		{
			top = std::min(top, row);
			left = std::min(left, col);
		}
	}

	template<int INDEX>
	void Transform2RowCol(int& row, int& col)
	{
		row = INDEX / TETRIMINO_WIDTH;
		col = INDEX % TETRIMINO_WIDTH;
	}
};

#endif // TETRIMINO_H
