#include "tetrimino.hpp"


const int Tetrimino::BlocksPerPiece = TETRIMINO_WIDTH;

const int Tetrimino::NumberOfRotations = TETRIMINO_NROTATIONS;

const int Tetrimino::NumberOfTypes = TETRIMINO_NTYPES;

Tetrimino::Symmetry Tetrimino::GetSymmetry() const
{
    return this->symmetry;
}

unsigned char Tetrimino::GetShape(const int& row, const int& col) const
{
    return this->shapes[this->rotationState][row][col];
}

int Tetrimino::GetTopBlock() const
{
    return this->cornerBlocks[this->rotationState][0];
}

int Tetrimino::GetLeftBlock() const
{
    return this->cornerBlocks[this->rotationState][1];
}

int Tetrimino::GetBottomBlock() const
{
    return this->cornerBlocks[this->rotationState][2];
}

int Tetrimino::GetRightBlock() const
{
    return this->cornerBlocks[this->rotationState][3];
}

void Tetrimino::Rotate()
{
    this->SetRotation(this->rotationState + 1);
}

Tetrimino::Tetrimino(
    const unsigned char (&shape)[TETRIMINO_WIDTH][TETRIMINO_WIDTH],
    const Symmetry& sym,
    const int& rotation) :
    symmetry(sym),
    rotationState(rotation)
{
    this->RotateRecursion<TETRIMINO_NROTATIONS-1>(shape);
}

void Tetrimino::SetRotation(const int& rotation)
{
    this->rotationState = rotation % TETRIMINO_NROTATIONS;
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
void Tetrimino::CornerPositionRecursion<0>(int (&corners)[4], const int& rotation)
{
    this->UpdateCorners<0>(corners, rotation);
}

Tetrimino* Tetrimino::Make(const Tetrimino::Type& type, const int& rotation)
{
    switch (type)
    {
        case Type::Square: return new Tetrimino({
            {0,0,0,0},
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0},
        }, Symmetry::Point, rotation);
        case Type::Line: return new Tetrimino({
            {0,0,1,0},
            {0,0,1,0},
            {0,0,1,0},
            {0,0,1,0},
        }, Symmetry::Line, rotation);
        case Type::RightHook: return new Tetrimino({
            {0,1,0,0},
            {0,1,0,0},
            {0,1,1,0},
            {0,0,0,0},
        }, Symmetry::None, rotation);
        case Type::LeftHook: return new Tetrimino({
            {0,0,1,0},
            {0,0,1,0},
            {0,1,1,0},
            {0,0,0,0},
        }, Symmetry::None, rotation);
        case Type::Tee: return new Tetrimino({
            {0,0,0,0},
            {0,0,1,0},
            {0,1,1,1},
            {0,0,0,0},
        }, Symmetry::None, rotation);
        case Type::RightChair: return new Tetrimino({
            {0,0,0,0},
            {0,1,1,0},
            {0,0,1,1},
            {0,0,0,0},
        }, Symmetry::Line, rotation);
        case Type::LeftChair: return new Tetrimino({
            {0,0,0,0},
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0},
        }, Symmetry::Line, rotation);
        default: return nullptr;
    }
}