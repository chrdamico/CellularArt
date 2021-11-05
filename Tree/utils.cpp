#include <utils.h>

void updateBoard(Board* boardPtr)
{
    // Iterate over all tiles and queue update rules to the buffer
    for (int i=1; i<boardPtr->columns-1; i++)
    {

        for (int j = 1; j<boardPtr->rows; j++)
        {
            applyRule(boardPtr, i, j);

        }
    }
    boardPtr->updateBoard();
}
