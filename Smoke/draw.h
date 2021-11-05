#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <thread>

class Position
{
    public:
    int x, y;
    Position();
    Position(int i, int j);
};

class Color
{
    public:
    int R;
    int G;
    int B;

    Color();
    Color(int red, int green, int blue);
    void changeColorTo(Color newColor);
    bool operator==(Color otherColor);
};

class ColorPalette
{
    public:
    Color white, blue, green, red, black, brown, yellow, purple, lightblue, darkbrown;
    Color darkred, darkgreen, darkblue, darkpurple;
    ColorPalette();
};

class Tile
{
    public:
    Color color;
    Position position;

    Tile();
    Tile(Position position, Color color);
    Tile(int i, int j, Color color);
    void changeColorTo(Color newColor);
};

class Board {

    public:
    ColorPalette colorPalette; // available colors
    int columns, rows;
    std::vector<Tile> data;

    Board(int ROWS, int COLUMNS);
    // constructor that initializes all tiles to white

    Tile operator()(int i, int j);
    // returns tile at coordinate (i, j)

    Color getTileColor(int i, int j);

    void changeTileColor(int i, int j, Color newColor);

    void updateTile(Tile tile);

    bool isColorAdjacent(int i, int j, Color color);
    // checks nearby tiles and returns true if at least one is of color color

    bool isColorBelow(int i, int j, Color color);
    // checks if color color is in any of the tiles directly below

    bool isColorAbove(int i, int j, Color color);
    // checks if color color is in any of the tiles directly above
    bool isColorLeft(int i, int j, Color color);
    // checks if color color is in any of the tiles directly left
    bool isColorRight(int i, int j, Color color);
    // checks if color color is in any of the tiles directly rigth


    int countColorNearby(int i, int j, int radius, Color color);
    // counts instances of tiles that have color color in a neighborhood of size radius

    bool isColorToHorSide(int i, int j, int sideLength, int ignoreDist, Color color);
    // SideLength is the left-right distance that is looked
    // e.g. 1 looks at only adjacent tiles
    // IgnoreDist is the left-right distance of tiles that is ignored
    // e.g. 1 ignores the adjacent tiles

    bool isColorToVerSide(int i, int j, int sideLenght, int ignoreDist, Color color);
    // Same as "isColortoHorSide" but considering vertical adjacent tiles for
    // sideLenght and ignoreDist

    void drawRectangle(int upperLefti, int upperLeftj, int lowerRighti, int lowerRightj, Color color);
    void drawRectangle(Position upperLeft, Position lowerRight, Color color);
    // draws a rectangle given position of two points

    void drawSquare(int i, int j, int edge, Color color);
    void drawSquare(Position, int edge, Color color);
    // draws a square given its bottom left vertex

    void drawTriangle(int i, int j, int baseLength, Color color);
    // draws an isosceles triangle of given baseLength from its bottom left vertex

    void draw(SDL_Surface* screenSurface);
    // draws the whole board onto screen

    // -------- Buffer for changes to the board
    std::vector<Tile> changesBuffer;

    void addTileToBuffer(int i, int j, Color color);
    void addTileToBuffer(Tile tile);

    void cleanUpBuffer();
    // destroys the buffer vector

    void updateBoard();
    // updates the board with all changes in the buffer and cleans the buffer
};
