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

	static Tetrimino make(const Type& type);

	Tetrimino(const unsigned char (&shape)[WIDTH][WIDTH]);

	unsigned char getShape(const int& rotation, const int& x, const int& y) const;

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

#endif // TETRIMINO_H
