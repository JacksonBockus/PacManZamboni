// Used for getting parameters from the console
#include <iostream>
#include "IceField.hpp"

int main()
{
    // The input parameters, in the order in which they're expected.
    int rows;
    int columns;
    int startingRow;
    int startingColumn;
    long long int numSteps;
    
    // Gathers input in the specified order.
    std::cin >> rows;
    std::cin >> columns;
    std::cin >> startingRow;
    std::cin >> startingColumn;
    std::cin >> numSteps;
    
    // The starting row and column numbers are unit-indexed,
    // but zero-indexed numbers are easier to use, so
    --startingRow;
    --startingColumn;
    
    IceField rink(rows, columns, startingRow, startingColumn, numSteps);
    rink.clean();
    std::cout << rink << std::endl;
}