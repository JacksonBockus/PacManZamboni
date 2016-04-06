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
    
    // Starts at the zero color
    currentColor = 0;
    
    // Creates an array of rows for each row of ice squares
    grid = new char*[rows];
    
    // Makes each pointer in the grid array point to a row with
    // the correct number of columns. Then fills each row
    // with the character that represents uncolored ice,
    for (int i = 0; i < rows; ++i)
    {
        grid[i] = new char[cols];
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
    for (int i = 0; i < ice.rows; ++i)
    {
        for (int j = 0; j < ice.cols; ++j)
        {
            o << ice.grid[i][j];
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
        
        // Causes the zamboni to wrap around if it has reached
        // an edge. Adding rows and cols respectively in the
        // parenthetical expressions makes sure that negative
        // values will wrap around correctly because % is not
        // a modulo operator but a division remainder operator. 
        zamboniRow = (zamboniRow + rows) % rows;
        zamboniCol = (zamboniCol + cols) % cols;
    }
    
    // Mark the resting location of the zamboni.
    grid[zamboniRow][zamboniCol] = ZAMBONI;
}

void IceField::turnZamboni()
{
    // This implementation turns the zamboni 90 degrees clockwise
    // as defined in the specification. 
    switch(currentDirection)
    {
        case NORTH : currentDirection = EAST; break;
        case EAST  : currentDirection = SOUTH; break;
        case SOUTH : currentDirection = WEST; break;
        case WEST  : currentDirection = NORTH; break;
        // if something's gone horribly wrong and the currentDirection
        // isn't North, South, East, or West, this will set it
        // to move North. May replace with some exception handling
        // at a later time.
        default: currentDirection = NORTH; break;
    }
}