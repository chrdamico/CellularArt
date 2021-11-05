#include <rules.h>

void modifyStartingBoard(Board* boardPtr)
{
    ColorPalette& colors = boardPtr->colorPalette;

    int flower_size = 16;
    int flower_half_size = flower_size/2;

    // central bit
    Position flower(boardPtr->columns/2-flower_half_size,
                    boardPtr->rows/2+flower_half_size);

    boardPtr->drawSquare(flower, flower_size, colors.black);

    // Smoke generators
    Position left_top(boardPtr->columns/2-flower_half_size - 1,
                      boardPtr->rows/2-flower_half_size + 1);
    Position left_bottom(boardPtr->columns/2-flower_half_size,
                         boardPtr->rows/2+flower_half_size);
    boardPtr->drawRectangle(left_top, left_bottom, colors.darkblue);

    Position top_left(boardPtr->columns/2-flower_half_size,
                      boardPtr->rows/2-flower_half_size);
    Position top_right(boardPtr->columns/2+flower_half_size,
                       boardPtr->rows/2-flower_half_size + 1);
    boardPtr->drawRectangle(top_left, top_right, colors.darkred);

    Position right_top(boardPtr->columns/2+flower_half_size,
                       boardPtr->rows/2-flower_half_size + 1);
    Position right_bottom(boardPtr->columns/2+flower_half_size+1,
                          boardPtr->rows/2+flower_half_size);
    boardPtr->drawRectangle(right_top, right_bottom, colors.darkgreen);

    Position bottom_left(boardPtr->columns/2-flower_half_size,
                       boardPtr->rows/2+flower_half_size);
    Position bottom_right(boardPtr->columns/2+flower_half_size,
                          boardPtr->rows/2+flower_half_size+1);
    boardPtr->drawRectangle(bottom_left, bottom_right, colors.darkpurple);
}



void applyRule(Board* boardPtr, int i, int j)
{
    ColorPalette& colors = boardPtr->colorPalette;

    checkRedRule(boardPtr, i, j);
    checkBlueRule(boardPtr, i, j);
    checkGreenRule(boardPtr, i, j);
    checkPurpleRule(boardPtr, i, j);
}


void checkRedRule(Board* boardPtr, int i, int j)
{
    ColorPalette& colors = boardPtr->colorPalette;

    if (boardPtr->getTileColor(i, j) == colors.red)
    {
        int random = rand() % 100;
        if (random>88)
        {
            boardPtr->addTileToBuffer(i, j, colors.black);
        }
    }

    if (boardPtr->isColorBelow(i, j, colors.darkred))
    {
        boardPtr->addTileToBuffer(i, j, colors.red);
        return;
    }


    // generate elevating smoke
    if (boardPtr->isColorBelow(i, j, colors.red))
    {
        if (!boardPtr->isColorToHorSide(i, j, 6, 5, colors.red))
        {
            int random_num_1 = rand() % 10000;
            if (random_num_1 > 9500)
            {
                boardPtr->addTileToBuffer(i, j, colors.red);
                return;
            }
        }
        else if (!boardPtr->isColorToHorSide(i, j, 4, 3, colors.red))
        {
            int random_num_2 = rand() % 100000;
            if (random_num_2 > 99500)
            {
                boardPtr->addTileToBuffer(i, j, colors.red);
                return;
            }
        }

        else if (!boardPtr->isColorToHorSide(i, j, 3, 2, colors.red))
        {
            int random_num_3 = rand() % 100000;
            if (random_num_3 > 99900)
            {
                boardPtr->addTileToBuffer(i, j, colors.red);
                return;
            }
        }
    }

}

void checkBlueRule(Board* boardPtr, int i, int j)
{
  ColorPalette& colors = boardPtr->colorPalette;

  if (boardPtr->getTileColor(i, j) == colors.blue)
  {
      int random = rand() % 100;
      if (random>88)
      {
          boardPtr->addTileToBuffer(i, j, colors.black);
      }
  }

  if (boardPtr->isColorRight(i, j, colors.darkblue))
  {
      boardPtr->addTileToBuffer(i, j, colors.blue);
      return;
  }


  // generate elevating smoke
  if (boardPtr->isColorRight(i, j, colors.blue))
  {
      if (!boardPtr->isColorToVerSide(i, j, 6, 5, colors.blue))
      {
          int random_num_1 = rand() % 10000;
          if (random_num_1 > 9500)
          {
              boardPtr->addTileToBuffer(i, j, colors.blue);
              return;
          }
      }
      else if (!boardPtr->isColorToVerSide(i, j, 4, 3, colors.blue))
      {
          int random_num_2 = rand() % 100000;
          if (random_num_2 > 99500)
          {
              boardPtr->addTileToBuffer(i, j, colors.blue);
              return;
          }
      }

      else if (!boardPtr->isColorToVerSide(i, j, 3, 2, colors.blue))
      {
          int random_num_3 = rand() % 100000;
          if (random_num_3 > 99900)
          {
              boardPtr->addTileToBuffer(i, j, colors.blue);
              return;
          }
      }
  }

}

void checkGreenRule(Board* boardPtr, int i, int j)
{
  ColorPalette& colors = boardPtr->colorPalette;

  if (boardPtr->getTileColor(i, j) == colors.green)
  {
      int random = rand() % 100;
      if (random>88)
      {
          boardPtr->addTileToBuffer(i, j, colors.black);
      }
  }

  if (boardPtr->isColorLeft(i, j, colors.darkgreen))
  {
      boardPtr->addTileToBuffer(i, j, colors.green);
      return;
  }


  // generate elevating smoke
  if (boardPtr->isColorLeft(i, j, colors.green))
  {
      if (!boardPtr->isColorToVerSide(i, j, 6, 5, colors.green))
      {
          int random_num_1 = rand() % 10000;
          if (random_num_1 > 9500)
          {
              boardPtr->addTileToBuffer(i, j, colors.green);
              return;
          }
      }
      else if (!boardPtr->isColorToVerSide(i, j, 4, 3, colors.green))
      {
          int random_num_2 = rand() % 100000;
          if (random_num_2 > 99500)
          {
              boardPtr->addTileToBuffer(i, j, colors.green);
              return;
          }
      }

      else if (!boardPtr->isColorToVerSide(i, j, 3, 2, colors.green))
      {
          int random_num_3 = rand() % 100000;
          if (random_num_3 > 99900)
          {
              boardPtr->addTileToBuffer(i, j, colors.green);
              return;
          }
      }
  }

}

void checkPurpleRule(Board* boardPtr, int i, int j)
{
  ColorPalette& colors = boardPtr->colorPalette;

  if (boardPtr->getTileColor(i, j) == colors.purple)
  {
      int random = rand() % 100;
      if (random>88)
      {
          boardPtr->addTileToBuffer(i, j, colors.black);
      }
  }

  if (boardPtr->isColorAbove(i, j, colors.darkpurple))
  {
      boardPtr->addTileToBuffer(i, j, colors.purple);
      return;
  }


  // generate elevating smoke
  if (boardPtr->isColorAbove(i, j, colors.purple))
  {
      if (!boardPtr->isColorToHorSide(i, j, 6, 5, colors.purple))
      {
          int random_num_1 = rand() % 10000;
          if (random_num_1 > 9500)
          {
              boardPtr->addTileToBuffer(i, j, colors.purple);
              return;
          }
      }
      else if (!boardPtr->isColorToHorSide(i, j, 4, 3, colors.purple))
      {
          int random_num_2 = rand() % 100000;
          if (random_num_2 > 99500)
          {
              boardPtr->addTileToBuffer(i, j, colors.purple);
              return;
          }
      }

      else if (!boardPtr->isColorToHorSide(i, j, 3, 2, colors.purple))
      {
          int random_num_3 = rand() % 100000;
          if (random_num_3 > 99900)
          {
              boardPtr->addTileToBuffer(i, j, colors.purple);
              return;
          }
      }
  }


}
