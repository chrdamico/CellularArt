#include <draw.h>

// ------------------- Position
Position::Position()
{
    x = 0;
    y = 0;
}

Position::Position(int i, int j)
{
    x = i;
    y = j;
}

// ------------------- Color
Color::Color()
{
    R = 50;
    G = 50;
    B = 50;
}

Color::Color(int red, int green, int blue)
{
    R = red;
    G = green;
    B = blue;
}

void Color::changeColorTo(Color newColor)
{
    R = newColor.R;
    G = newColor.G;
    B = newColor.B;
}

bool Color::operator==(Color otherColor)
{
    if (R == otherColor.R && G == otherColor.G && B == otherColor.B)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// ------------------- ColorPalette
ColorPalette::ColorPalette() :
    white(251, 251, 251), blue(1, 1, 251), green(1, 251, 1), red(251, 1, 1), black(1, 1, 1),
    brown(210, 105,  30), yellow(100, 100, 1), purple(139, 0, 139), lightblue(1, 251, 251),
    darkbrown(165,42,42), darkred(102, 0, 0), darkgreen(24, 176, 0), darkblue(1, 1, 102),
    darkpurple(75, 0,130)
{ }

// ------------------- Tile
Tile::Tile() : position(), color()
{
}

Tile::Tile(Position inPosition, Color inColor)
{
    position = inPosition;
    color = inColor;
}

Tile::Tile(int i, int j, Color inColor)
{
    position = Position(i,j);
    color = inColor;
}

void Tile::changeColorTo(Color newColor)
{
    color.R = newColor.R;
    color.G = newColor.G;
    color.B = newColor.B;
}

// ------------------- Board
Board::Board(int ROWS, int COLUMNS): data(std::vector<Tile>(ROWS*COLUMNS)), colorPalette()
{
    rows = ROWS;
    columns = COLUMNS;

    for (int i = 0; i<columns; i++)
    {
        for (int j = 0; j<rows; j++)
        {
            data[i+columns*j].color = colorPalette.black;
            data[i+columns*j].position.x = i;
            data[i+columns*j].position.y = j;
        }
    }
}

Tile Board::operator()(int i, int j)
{
    return data[i+columns*j];
}

Color Board::getTileColor(int i, int j)
{
    return data[i+columns*j].color;
}

void Board::changeTileColor(int i, int j, Color newColor)
{
    data[i+columns*j].color = newColor;
}

void Board::updateTile(Tile tile)
{
    int i = tile.position.x;
    int j = tile.position.y;
    Color color = tile.color;

    this->changeTileColor(i, j, color);
}

bool Board::isColorAdjacent(int i, int j, Color color)
{
    for (int count_i = i - 1; count_i < i+2; count_i++)
    {
        for (int count_j = j - 1; count_j < j+2; count_j++)
        {
            if (this->getTileColor(count_i, count_j) == color)
            {
                return true;
            }
        }
    }
    return false;
}

bool Board::isColorBelow(int i, int j, Color color)
{
    for (int count_i = i-1; count_i <= i+1; count_i++)
    {
        if (this->getTileColor(count_i, j+1) == color)
        {
            return true;
        }
    }
    return false;
}


bool Board::isColorAbove(int i, int j, Color color)
{
    for (int count_i = i-1; count_i <= i+1; count_i++)
    {
        if (this->getTileColor(count_i, j-1) == color)
        {
            return true;
        }
    }
    return false;
}

bool Board::isColorLeft(int i, int j, Color color)
{
    for (int count_j = j-1; count_j <= j+1; count_j++)
    {
        if (this->getTileColor(i-1, count_j) == color)
        {
            return true;
        }
    }
    return false;
}

bool Board::isColorRight(int i, int j, Color color)
{
    for (int count_j = j-1; count_j <= j+1; count_j++)
    {
        if (this->getTileColor(i+1, count_j) == color)
        {
            return true;
        }
    }
    return false;
}

int Board::countColorNearby(int i, int j, int radius, Color color)
{
    int counter = 0;
    for (int count_i = i - radius; count_i < i + radius; count_i++)
    {
        for (int count_j = j - radius; count_j < j + radius; count_j++)
        {
            if (this->getTileColor(count_i, count_j) == color)
            {
                counter ++;
            }
        }
    }
    return counter;
}

bool Board::isColorToHorSide(int i, int j, int sideLength, int ignoreDist, Color color)
{
    for (int count_i = i-sideLength; count_i <= i + sideLength; count_i++)
    {
        if (this->getTileColor(count_i, j) == color && abs(i-count_i)>ignoreDist)
        {
            return true;
        }
    }
    return false;
}

bool Board::isColorToVerSide(int i, int j, int sideLength, int ignoreDist, Color color)
{
    for (int count_j = j-sideLength; count_j <= j + sideLength; count_j++)
    {
        if (this->getTileColor(i, count_j) == color && abs(j-count_j)>ignoreDist)
        {
            return true;
        }
    }
    return false;
}

void Board::drawRectangle(int upperLefti, int upperLeftj, int lowerRighti, int lowerRightj, Color color)
{
    for (int count_i = upperLefti; count_i < lowerRighti ; count_i++)
    {
        for (int count_j = upperLeftj; count_j < lowerRightj; count_j++)
        {
            this->changeTileColor(count_i, count_j, color);
        }
    }
}

void Board::drawRectangle(Position upperLeft, Position lowerRight, Color color)
{
    for (int count_i = upperLeft.x; count_i < lowerRight.x ; count_i++)
    {
        for (int count_j = upperLeft.y; count_j < lowerRight.y; count_j++)
        {
            this->changeTileColor(count_i, count_j, color);
        }
    }
}

void Board::drawSquare( int i, int j, int edge, Color color)
{

    for (int count_i = i; count_i < i + edge ; count_i++)
    {
        for (int count_j = j-edge; count_j < j; count_j++)
        {
            this->changeTileColor(count_i, count_j, color);
        }
    }
}

void Board::drawSquare(Position position, int edge, Color color)
{

    for (int count_i = position.x; count_i < position.x + edge ; count_i++)
    {
        for (int count_j = position.y-edge; count_j < position.y; count_j++)
        {
            this->changeTileColor(count_i, count_j, color);
        }
    }
}

void Board::drawTriangle(int i, int j, int baseLength, Color color)
{
    int currentBase = baseLength;
    int currentIgnore = 0;
    for (int count_j = j; count_j >= j - baseLength/2; count_j --)
    {
        for (int count_i = i + currentIgnore; count_i < i + baseLength - currentIgnore; count_i++)
        {
            this->changeTileColor(count_i, count_j, color);
        }
        currentIgnore ++;
    }
}

void Board::draw(SDL_Surface* screenSurface)
{
    SDL_Rect rect;

    int screenWidth = screenSurface->w;
    int screenHeight = screenSurface->h;

    int hSizeOfPixel = screenWidth/columns;
    int vSizeOfPixel = screenHeight/rows;

    Board board = *this;

    for (int i = 0; i<columns; i++ )
    {
        for (int j = 0; j<rows; j++)
        {
            rect.x = hSizeOfPixel*board(i,j).position.x;
            rect.y = vSizeOfPixel*board(i,j).position.y;
            rect.w = hSizeOfPixel-1;
            rect.h = vSizeOfPixel-1;

            SDL_FillRect( screenSurface, &rect, SDL_MapRGB( screenSurface->format, board(i,j).color.R, board(i,j).color.G, board(i,j).color.B));
        }
    }
}

// ------------------- ChangesVector
void Board::addTileToBuffer(int i, int j, Color color)
{

    changesBuffer.push_back(Tile(i, j, color));

}

void Board::addTileToBuffer(Tile tile)
{
    changesBuffer.push_back(tile);
}

void Board::updateBoard()
{
    for (const auto &i : this->changesBuffer) {
        this->updateTile(i);
    }
    this->cleanUpBuffer();
}

void Board::cleanUpBuffer()
{
    changesBuffer.clear();
}
