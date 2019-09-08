#include "tetrimino.hpp"
#include <bitset>
#include <stdexcept>


const int Tetrimino::BlocksPerPiece = TETRIMINO_WIDTH;

const int Tetrimino::NumberOfRotations = TETRIMINO_NROTATIONS;

const int Tetrimino::NumberOfTypes = TETRIMINO_NTYPES;

Tetrimino::Tetrimino() :
Tetrimino({{},{},{},{}}, Symmetry::None, 0)
{
    ;
}

bool Tetrimino::operator==(const Tetrimino& other) const
{
    return this->EqualityRecursion<TETRIMINO_WIDTH*TETRIMINO_WIDTH-1>(other);
}

Tetrimino::Symmetry Tetrimino::GetSymmetry() const
{
    return this->symmetry;
}

size_t Tetrimino::GetHash() const
{
    Hash hash;
    this->HashRecursion<TETRIMINO_WIDTH*TETRIMINO_WIDTH-1>(hash);
    if (this->rotationState / 2) hash.set(TETRIMINO_HASHSIZE-2);
    if (this->rotationState % 2) hash.set(TETRIMINO_HASHSIZE-1);
    return hash.to_ullong();
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

template<>
void Tetrimino::HashRecursion<0>(Hash& hash) const
{
    this->AssignBit<0>(hash);
}

template<>
bool Tetrimino::EqualityRecursion<0>(const Tetrimino& other) const
{
    return this->CheckEquality<0>(other);
}

Tetrimino Tetrimino::Make(const Tetrimino::Type& type, const int& rotation)
{
    switch (type)
    {
        case Type::Square: return Tetrimino({
            {0,0,0,0},
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0},
        }, Symmetry::Point, rotation);
        case Type::Line: return Tetrimino({
            {0,0,1,0},
            {0,0,1,0},
            {0,0,1,0},
            {0,0,1,0},
        }, Symmetry::Line, rotation);
        case Type::RightHook: return Tetrimino({
            {0,1,0,0},
            {0,1,0,0},
            {0,1,1,0},
            {0,0,0,0},
        }, Symmetry::None, rotation);
        case Type::LeftHook: return Tetrimino({
            {0,0,1,0},
            {0,0,1,0},
            {0,1,1,0},
            {0,0,0,0},
        }, Symmetry::None, rotation);
        case Type::Tee: return Tetrimino({
            {0,0,0,0},
            {0,0,1,0},
            {0,1,1,1},
            {0,0,0,0},
        }, Symmetry::None, rotation);
        case Type::RightChair: return Tetrimino({
            {0,0,0,0},
            {0,1,1,0},
            {0,0,1,1},
            {0,0,0,0},
        }, Symmetry::Line, rotation);
        case Type::LeftChair: return Tetrimino({
            {0,0,0,0},
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0},
        }, Symmetry::Line, rotation);
        default: throw std::invalid_argument("unknown Tetrimino type.");
    }
}