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
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            o << ice.grid[i][j];
        }
        o << std::endl;
    }
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
        grid[zamboniRow][zamboniCol] = ZERO_COLOR + currentColor;
        
        // Moves the zamboni one square in its current direction.
        // It may be faster to put the condition here outside of 
        // the loop, since the value of currentDirection does not
        // change during the loop.
        switch (currentDirection)
        {
            case NORTH : --zamboniRow; break;
            case EAST  : ++zamboniCol; break;
            case SOUTH : ++zamboniRow; break;
            case WEST  : --zamboniCol; break;
            default : break;
        }
    }
    
    // Mark the resting location of the zamboni.
    grid[zamboniRow][zamboniCol] = ZAMBONI;
    
}

