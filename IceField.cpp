#include "IceField.hpp"
#include <iostream>

IceField::IceField(int rows, int cols, int startRow, int startCol, int numMoves)
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
    
    // Creates an array of rows for each row of ice squares
    grid = new int*[rows];
    
    // Makes each pointer in the grid array point to a row with
    // the correct number of columns. Then fills each row
    // with the character that represents uncolored ice,
    for (int i = 0; i < rows; ++i)
    {
        grid[i] = new int[cols];
        for (int j = 0; j < cols; ++j)
        {
            grid[i][j] = WHITE_ICE;
        }
    }
}

IceField::~IceField()
{
    // Since the grid was dynamically allocated, it needs to be
    // explicitly deallocated. First delete each row, then the
    // array of pointers to those rows.
    for (int i = 0; i < rows; ++i)
    {
        delete[] grid[i];
    }
    delete[] grid;
}

void IceField::clean()
{
    for (int i = 0; i < numMoves; ++i)
    {
        // Moves the zamboni in the current direction
        // and with the correct step size.
        moveZamboni();
        
        // Turns the zamboni to face its new direction
        turnZamboni();
        
        // The zamboni will move one step farther next time
        ++stepSize;
    }
}

std::ostream& operator<<(std::ostream& o, const IceField &ice)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            o << ice.grid[i][j];
        }
        o << std::endl;
    }
}

