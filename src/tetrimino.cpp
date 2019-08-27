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

void Tetrimino::RotateIndices(int& ii, int& jj, const int& rotation)
{
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