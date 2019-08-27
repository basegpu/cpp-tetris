#include "tetrimino.hpp"


const size_t Tetrimino::BlocksPerPiece = TETRIMINO_WIDTH;

Tetrimino::Tetrimino(const unsigned char (&shape)[TETRIMINO_WIDTH][TETRIMINO_WIDTH])
{
	this->RotateRecursion<TETRIMINO_NROTATIONS-1>(shape);
}

unsigned char Tetrimino::GetShape(const int& rotation, const int& x, const int& y) const
{
	return this->shapes[rotation % TETRIMINO_NROTATIONS][x][y];
}

int Tetrimino::GetTopBlock(const int& rotation) const
{
	return this->topleftBlock[rotation][0];
}

int Tetrimino::GetLeftBlock(const int& rotation) const
{
	return this->topleftBlock[rotation][1];
}

template<>
void Tetrimino::RotateRecursion<0>(const unsigned char (&shape)[TETRIMINO_WIDTH][TETRIMINO_WIDTH])
{
	this->DoRotation<0>(shape);
}

template<>
void Tetrimino::AssetInitializationRecursion<0>(const unsigned char (&shape)[TETRIMINO_WIDTH][TETRIMINO_WIDTH], const int& rotation)
{
	this->DoAssetInitialization<0>(shape, rotation);
}

template<>
void Tetrimino::TopLeftPositionRecursion<0>(int& x, int& y, const int& rotation)
{
	this->CheckIfTopLeft<0>(x, y, rotation);
}

Tetrimino Tetrimino::Make(const Tetrimino::Type& type)
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