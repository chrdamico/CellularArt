#include <rules.h>

void modifyStartingBoard(Board* boardPtr)
{
    ColorPalette& colors = boardPtr->colorPalette;
    // sky and grass
    boardPtr->drawRectangle(0, 0, boardPtr->columns, boardPtr->rows, colors.lightblue);
    boardPtr->drawRectangle(0, 80, boardPtr->columns, boardPtr->rows, colors.green);

    // start of the tree
    boardPtr->drawSquare(boardPtr->columns/2 +10, boardPtr->rows, 5, colors.brown);

    // house
    boardPtr->drawSquare(20, 80, 15, colors.darkbrown);
    boardPtr->drawTriangle(20, 64, 15, colors.purple);
    // chimney
    boardPtr->drawSquare(22, 61, 2, colors.darkred);
    boardPtr->changeTileColor(22, 61, colors.darkred);
    boardPtr->changeTileColor(23, 61, colors.darkred);
    // door
    boardPtr->drawRectangle(30, 75, 33, 80, colors.white);

}

void applyRule(Board* boardPtr, int i, int j)
{

    // alias name to make code more readable
    ColorPalette& colors = boardPtr->colorPalette;

    // Ignore brown or dark green tiles
    if (boardPtr->getTileColor(i, j) == colors.darkgreen || boardPtr->getTileColor(i, j) == colors.red)
    {
        return;
    } 

    // Sometimes destroy smoke tiles
    if (boardPtr->getTileColor(i, j) == colors.black)
    {
        int random = rand() % 100;
        if (random>90)
        {
            boardPtr->addTileToBuffer(i, j, colors.lightblue);
            return;
        }
    
    }

    // ----------- Tree evolution
    // Apples
    if (boardPtr->getTileColor(i, j) == colors.brown || boardPtr->getTileColor(i, j) == colors.lightblue)
    {
        // Check to see if there is red nearby
        if (boardPtr->isColorAdjacent(i, j, colors.red))
        {

            // Do nothing if getting something bigger than a 4x4 apple
            if (boardPtr->getTileColor(i+4, j) == colors.red
             || boardPtr->getTileColor(i-4, j) == colors.red
             || boardPtr->getTileColor(i, j+4) == colors.red
             || boardPtr->getTileColor(i, j-4) == colors.red
             || boardPtr->getTileColor(i-4, j-4) == colors.red
             || boardPtr->getTileColor(i+4, j+4) == colors.red
             || boardPtr->getTileColor(i+4, j-4) == colors.red
             || boardPtr->getTileColor(i-4, j+4) == colors.red
             || boardPtr->countColorNearby(i, j, 3, colors.green))
            {}
            else // Increase apple size
            {
                boardPtr->addTileToBuffer(i, j, colors.red);
            }
        }

        // Spawn a new apple sparingly
        int random_num = rand() % 100000;
        if (random_num > 99998)
        {
            if (boardPtr->countColorNearby(i, j, 2, colors.red) < 1 && boardPtr->isColorAdjacent(i, j, colors.brown))
            {
                boardPtr->addTileToBuffer(i, j, colors.red);
                return;
            }
        }
    }

    // expand the tree
    // Check if brown is below tile
    if (boardPtr->isColorBelow(i, j, colors.brown))
    {
        // look at sides
        if (!boardPtr->isColorToHorSide(i, j, 6, 5, colors.brown))
        {
            // Add brown some of the time
            int random_num_1 = rand() % 10000;
            if (random_num_1 > 9500)
            {   
                boardPtr->addTileToBuffer(i, j, colors.brown);
                return;
            }
        }
        // repeat with different side lookups and probabilities
        else if (!boardPtr->isColorToHorSide(i, j, 5, 4, colors.brown))
        {
            int random_num_2 = rand() % 100000;
            if (random_num_2 > 99000)
            {   
                boardPtr->addTileToBuffer(i, j, colors.brown);
                return;
            }
        }
        
        else if (!boardPtr->isColorToHorSide(i, j, 4, 3, colors.brown))
        {
            int random_num_2 = rand() % 100000;
            if (random_num_2 > 99500)
            {   
                boardPtr->addTileToBuffer(i, j, colors.brown);
                return;
            }
        }

        else if (!boardPtr->isColorToHorSide(i, j, 3, 2, colors.brown))
        {
            int random_num_3 = rand() % 100000;
            if (random_num_3 > 99900)
            {   
                boardPtr->addTileToBuffer(i, j, colors.brown);
                return;
            }
        }
    }

    // --------- smoke
    // generate static smoke over the chimney
    if (boardPtr->isColorBelow(i, j, colors.darkred))
    {
        boardPtr->addTileToBuffer(i, j, colors.black);
        return;
    }

    // generate elevating smoke
    if (boardPtr->isColorBelow(i, j, colors.black))
    {
        if (!boardPtr->isColorToHorSide(i, j, 6, 5, colors.black))
        {
            int random_num_1 = rand() % 10000;
            if (random_num_1 > 9500)
            {   
                boardPtr->addTileToBuffer(i, j, colors.black);
                return;
            }
        }
        else if (!boardPtr->isColorToHorSide(i, j, 4, 3, colors.black))
        {
            int random_num_2 = rand() % 100000;
            if (random_num_2 > 99500)
            {   
                boardPtr->addTileToBuffer(i, j, colors.black);
                return;
            }
        }

        else if (!boardPtr->isColorToHorSide(i, j, 3, 2, colors.black))
        {
            int random_num_3 = rand() % 100000;
            if (random_num_3 > 99900)
            {   
                boardPtr->addTileToBuffer(i, j, colors.black);
                return;
            }
        }
    }
}
