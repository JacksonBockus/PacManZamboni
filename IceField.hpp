// #include guards
#ifndef ICEFIELD_HPP
#define ICEFIELD_HPP

// Used for overloading << operator with an ostream
#include <iostream>

/* A class representing an ice rink that, like in Pac-Man and
 * Final Fantasy, has wraparound geography and finite dimensions.
 */
class IceField {
public:
    
    /* Creates a new IceField object
     * PARAMS
     **** rows: number of rows on the IceField
     **** cols: number of columns on the IceField
     **** startRow: initial row number of the zamboni, zero-indexed
     **** startCol: initial column number of the zamboni, zero-indexed
     **** numMoves: number of time the zamboni moves and changes color
     * RETURN
     **** IceField object created with the given parameters
     */
    IceField(int rows, int cols, int startRow, int startCol, long long int numMoves);
    
    /* Safely destroys the IceField object.
     */
    ~IceField();
    
    /* Cleans the ice according to the Pac-Man algorithm:
     * stepSize := 1
     * loop numMoves times
     *     Move stepSize steps in the current direction
     *     Rotate the direction of the zamboni 90 degrees clockwise
     *     Switch to the next color
     *     stepSize := stepSize + 1
     * end loop
     * The zamboni starts by facing up.
     */
    void clean();
    
    /* Outputs a visual representation of the ice field, with
     * the letters A-Z representing the different colors, the
     * character '.' representing white ice, and the character
     * '@' representing the current location of the Zamboni. 
     */
    friend std::ostream& operator<<(std::ostream& o, const IceField &ice);
    
private:
    
    /* The number of steps the zamboni should take the first time
     * it moves
     */
    static const int FIRST_STEP_SIZE = 1;
    
    /* The number of colors the zamboni can paint. Since each
     * letter of the alphabet represents a different color,
     * there are 26 possible colors.
     */
    static const int NUMBER_OF_COLORS = 26;
    
    /* The character that represents the first color the zamboni
     * will paint. This is used to the field currentColor into
     * a character, since the expressions ZERO_COLOR + 0,
     * ZERO_COLOR + 1, and ZERO_COLOR + 2 will have the values
     * 'A', 'B', and 'C', respectively, and so on.
     */
    static const char ZERO_COLOR = 'A';
    
    /* The character that represents uncolored white ice.
     */
    static const char WHITE_ICE = '.';
    
    /* The character that represents the current location of the
     * zamboni on the ice.
     */
    static const char ZAMBONI = '@';
    
    /* Constants that represent the four directions in which the
     * zamboni can move.
     */
    static const int NORTH = 0;
    static const int EAST = 1;
    static const int SOUTH = 2;
    static const int WEST = 3;
    
    /* Arrays to look up the change in row and column for any given direction.
     * It's important to note that the indices of these arrays are the 
     * int values of the directions listed above, so if you change the values
     * for the directions, also change the arrays below.
     */
    
    // The change in row when moving north, east, south, and west.
    static const int rowChange[];
    
    // the change in col when moving north, east, south, and west.
    static const int colChange[];
    
    //the direction in which the zamboni will point after turning 90 deg clockwise
    static const int turn[];
    
    /* Number of rows in the ice field.
     */
    const int rows;
    
    /* Number of columns in the ice field
     */
    const int cols;
    
    /* Current row number of the zamboni, zero-indexed
     */
    int zamboniRow;
    
    /* Current column number of the zamboni, zero-indexed
     */
    int zamboniCol;
    
    /* Number of times the zamboni moves and changes color.
     */
    const long long int numMoves;
    
    /* Distance the zamboni should move in the next direction.
     */
    int stepSize;
    
    /* An array that contains the colors of every square on the
     * ice field, with '.' representing white, A-Z representing colors,
     * and '@' representing the current location of the zamboni.
     * Uses a 1-dimensional array to improve cache locality. In order 
     * to access the value at row r, column c, use grid[r * cols + c].
     */
    char* grid;
    
    /* An integer representing the color the zamboni is painting.
     * Always meets the condition 0 <= currentColor < NUMBER_OF_COLORS.
     * To guarantee this, it should always be modded by NUMBER_OF_COLORS
     * after incrementing.
     */
    int currentColor;
    
    /* An integer representing the direction in which the zamboni is
     * moving. It should always have the value NORTH, EAST, SOUTH, or
     * WEST.
     */
    int currentDirection;
    
    /* Moves the zamboni in its current direction, coloring every square
     * it passes over, including the square it starts from, and not
     * including the square it finishes on. If it moves across one edge,
     * it wraps around to the opposite edge.
     */
    void moveZamboni();
    
    /* Turns the zamboni clockwise.
     */
    void turnZamboni();
};

// Closes #include guard.
#endif