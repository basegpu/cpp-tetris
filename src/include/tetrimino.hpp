#ifndef TETRIMINO_H
#define TETRIMINO_H

#include <algorithm>

#define TETRIMINO_WIDTH 4
#define TETRIMINO_NROTATIONS 4


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

protected:

	Tetrimino(const unsigned char (&shape)[TETRIMINO_WIDTH][TETRIMINO_WIDTH]);


private:

	unsigned char shapes[TETRIMINO_NROTATIONS][TETRIMINO_WIDTH][TETRIMINO_WIDTH];

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
	}

	template<int INDEX>
	void AssetInitializationRecursion(const unsigned char (&shape)[TETRIMINO_WIDTH][TETRIMINO_WIDTH], const int& rotation)
	{
		this->DoAssetInitialization<INDEX>(shape, rotation);
		this->AssetInitializationRecursion<INDEX-1>(shape, rotation);
	}

	template<int INDEX>
	void DoAssetInitialization(const unsigned char (&shape)[TETRIMINO_WIDTH][TETRIMINO_WIDTH], const int& rotation)
	{
		// row and column indices
		int ii = INDEX / TETRIMINO_WIDTH;
		int jj = INDEX % TETRIMINO_WIDTH;
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
};

#endif // TETRIMINO_H
