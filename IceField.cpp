#include "IceField.hpp"
#include <iostream>

IceField::IceField(int rows, int cols, int startRow, int startCol, int numMoves)
    : rows(rows), cols(cols), startRow(startRow), numMoves(numMoves)
{
    // The zamboni starts facing North.
    currentDirection = NORTH;
    
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

