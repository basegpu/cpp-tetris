#ifndef TETRIMINO_H
#define TETRIMINO_H

#include "globals.hpp"
#include <algorithm>
#include <bitset>


class Tetrimino
{
public:

    Tetrimino();
    virtual ~Tetrimino() {;}

    enum class Type : unsigned char {
        Square,
        Line,
        RightHook,
        LeftHook,
        Tee,
        RightChair,
        LeftChair
    };

    enum class Symmetry : unsigned char {
        None,
        Line,
        Point
    };

    static Tetrimino Make(const Type& type, const int& rotation);
    static const int BlocksPerPiece;
    static const int NumberOfRotations;
    static const int NumberOfTypes;

    bool operator==(const Tetrimino& other) const;
    Symmetry GetSymmetry() const;
    size_t GetHash() const;
    unsigned char GetShape(const int& x, const int& y) const;
    int GetTopBlock() const;
    int GetLeftBlock() const;
    int GetBottomBlock() const;
    int GetRightBlock() const;
    void Rotate();

protected:

    Tetrimino(
        const unsigned char (&shape)[TETRIMINO_WIDTH][TETRIMINO_WIDTH],
        const Symmetry& symmetry,
        const int& rotation);
    void SetRotation(const int& rotation);


private:
    
    typedef std::bitset<TETRIMINO_HASHSIZE> Hash;

    unsigned char shapes[TETRIMINO_NROTATIONS][TETRIMINO_WIDTH][TETRIMINO_WIDTH];
    int cornerBlocks[TETRIMINO_NROTATIONS][4];
    Symmetry symmetry;
    int rotationState;

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
        // init corner positions: top, left, bottom , right
        int corners[4] = {TETRIMINO_WIDTH, TETRIMINO_WIDTH, 0, 0};
        this->CornerPositionRecursion<TETRIMINO_WIDTH*TETRIMINO_WIDTH-1>(corners, ROTATION);
        for (int ii = 0; ii < 4; ii++)
        {
            this->cornerBlocks[ROTATION][ii] = corners[ii];
        }
    }

    template<int INDEX>
    void AssetInitializationRecursion(const unsigned char (&shape)[TETRIMINO_WIDTH][TETRIMINO_WIDTH], const int& rotation)
    {
        this->DoAssetInitialization<INDEX>(shape, rotation);
        this->AssetInitializationRecursion<INDEX-1>(shape, rotation);
    }

    template<int INDEX>
    void CornerPositionRecursion(int (&corners)[4], const int& rotation)
    {
        this->UpdateCorners<INDEX>(corners, rotation);
        this->CornerPositionRecursion<INDEX-1>(corners, rotation);
    }

    template<int INDEX>
    void HashRecursion(Hash& hash) const
    {
        this->AssignBit<INDEX>(hash);
        this->HashRecursion<INDEX-1>(hash);
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
    void UpdateCorners(int (&corners)[4], const int& rotation)
    {
        // row and column indices
        int row, col;
        this->Transform2RowCol<INDEX>(row, col);
        // only check if not empty
        if (this->shapes[rotation][row][col] != 0)
        {
            corners[0] = std::min(corners[0], row);
            corners[1] = std::min(corners[1], col);
            corners[2] = std::max(corners[2], row);
            corners[3] = std::max(corners[3], col);
        }
    }

    template<int INDEX>
    void AssignBit(Hash& hash) const
    {
        // row and column indices
        int row, col;
        this->Transform2RowCol<INDEX>(row, col);
        // eventually assign bit
        if (this->shapes[this->rotationState][row][col])
        {
            hash.set(INDEX);
        }
    }

    template<int INDEX>
    void Transform2RowCol(int& row, int& col) const
    {
        row = INDEX / TETRIMINO_WIDTH;
        col = INDEX % TETRIMINO_WIDTH;
    }
};

#endif // TETRIMINO_H
