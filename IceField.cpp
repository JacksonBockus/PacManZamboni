#include "IceField.hpp"
#include <iostream>

const int IceField::rowChange[] = {-1, 0, 1, 0};
const int IceField::colChange[] = {0, 1, 0, -1};
const int IceField::turn[] = {EAST, SOUTH, WEST, NORTH};

IceField::IceField(int rows, int cols, int startRow, int startCol, long long int numMoves)
    : rows(rows)
    , cols(cols)
    , zamboniRow(startRow)
    , zamboniCol(startCol)
    , numMoves(numMoves)
{
    // The zamboni starts facing North.
    currentDirection = NORTH;
    
    // Give the zamboni its starting step size.
    stepSize = FIRST_STEP_SIZE;
    
    // Starts at the zero color
    currentColor = 0;
    
    // Allocates the array with enough items to represent a grid of
    // rows x cols squares.
    grid = new char[rows * cols];
    
    // Populates the grid with white ice squares.
    for (int i = 0; i < rows * cols; ++i)
    {
        grid[i] = WHITE_ICE;
    }
    
}

IceField::~IceField()
{
    // Since the grid was dynamically allocated, it needs to be
    // explicitly deallocated. 
    delete[] grid;
}

void IceField::clean()
{
    for (long long int i = 0; i < numMoves; ++i)
    {
        // Moves the zamboni in the current direction
        // and with the correct step size.
        moveZamboni();
        
        // Changes the color. If it gets to the point where
        // there have been more colors than the stated max,
        // wraps around back to the zero color.
        ++currentColor;
        currentColor %= NUMBER_OF_COLORS;
        
        // Turns the zamboni to face its new direction
        turnZamboni();
        
        // The zamboni will move one step farther next time
        ++stepSize;
    }
}

std::ostream& operator<<(std::ostream& o, const IceField &ice)
{
    for (int i = 0; i < ice.rows; ++i)
    {
        for (int j = 0; j < ice.cols; ++j)
        {
            o << ice.grid[i * ice.cols + j];
        }
        o << std::endl;
    }
    return o;
}

void IceField::moveZamboni()
{
    for (int i = 0; i < stepSize; ++i)
    {
        // Paints the current location of the zamboni.
        // Note that the location of this statement means that
        // the final location of the zamboni is not painted.
        // This is intended behavior, since the final location
        // of the zamboni gets a special character.
        grid[zamboniRow * cols + zamboniCol] = ZERO_COLOR + currentColor;
        
        // Moves the zamboni one square in its current direction.
        // Takes advantage of the arrays of row and column changes
        // defined in the class header.
        zamboniRow += rowChange[currentDirection];
        zamboniCol += colChange[currentDirection];
        
        // Causes the zamboni to wrap around if it has reached
        // an edge. Adding rows and cols respectively in the
        // parenthetical expressions makes sure that negative
        // values will wrap around correctly because % is not
        // a modulo operator but a division remainder operator. 
        zamboniRow = (zamboniRow + rows) % rows;
        zamboniCol = (zamboniCol + cols) % cols;
    }
    
    // Mark the resting location of the zamboni.
    grid[zamboniRow * cols + zamboniCol] = ZAMBONI;
}

void IceField::turnZamboni()
{
    // Uses the turn array from the class header to determine the
    // new direction for the zamboni.
    currentDirection = turn[currentDirection];
}