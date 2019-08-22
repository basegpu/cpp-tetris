#ifndef TETRIMINO_H
#define TETRIMINO_H

#include <algorithm>

#define WIDTH 4
#define NROTATIONS 4


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

	Tetrimino(const unsigned char (&shape)[WIDTH][WIDTH]);

	unsigned char GetShape(const int& rotation, const int& x, const int& y) const;

private:

	unsigned char shapes[NROTATIONS][WIDTH][WIDTH];

	template<int ROTATION>
	void RotateRecursion(const unsigned char (&shape)[WIDTH][WIDTH])
	{
		this->DoRotation<ROTATION>(shape);
		this->RotateRecursion<ROTATION-1>(shape);
	}

	template<int ROTATION>
	void DoRotation(const unsigned char (&shape)[WIDTH][WIDTH])
	{
		this->AssetInitializationRecursion<WIDTH*WIDTH-1>(shape, ROTATION);
	}

	template<int INDEX>
	void AssetInitializationRecursion(const unsigned char (&shape)[WIDTH][WIDTH], const int& rotation)
	{
		this->DoAssetInitialization<INDEX>(shape, rotation);
		this->AssetInitializationRecursion<INDEX-1>(shape, rotation);
	}

	template<int INDEX>
	void DoAssetInitialization(const unsigned char (&shape)[WIDTH][WIDTH], const int& rotation)
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

#endif // TETRIMINO_H
