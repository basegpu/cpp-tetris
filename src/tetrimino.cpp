#include "tetrimino.hpp"


Tetrimino::Tetrimino(const unsigned char (&shape)[WIDTH][WIDTH])
{
	this->rotateRecursion<NROTATIONS-1>(shape);
}

unsigned char Tetrimino::getShape(const int& rotation, const int& x, const int& y) const
{
	return this->shapes[rotation % NROTATIONS][x][y];
}

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

Tetrimino Tetrimino::make(const Tetrimino::Type& type)
{
	switch (type)
	{
		case Type::Square: return Tetrimino({
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0},
		});
		case Type::Line: return Tetrimino({
			{0,0,1,0},
			{0,0,1,0},
			{0,0,1,0},
			{0,0,1,0},
		});
		case Type::RightHook: return Tetrimino({
			{0,1,0,0},
			{0,1,0,0},
			{0,1,1,0},
			{0,0,0,0},
		});
		case Type::LeftHook: return Tetrimino({
			{0,0,1,0},
			{0,0,1,0},
			{0,1,1,0},
			{0,0,0,0},
		});
		case Type::Tee: return Tetrimino({
			{0,0,0,0},
			{0,0,1,0},
			{0,1,1,1},
			{0,0,0,0},
		});
		case Type::RightChair: return Tetrimino({
			{0,0,0,0},
			{0,1,1,0},
			{0,0,1,1},
			{0,0,0,0},
		});

		case Type::LeftChair: return Tetrimino({
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0},
		});
	}
}