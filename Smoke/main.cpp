#include <main.h>

int main ()
{
    // Initialize available color palette
    ColorPalette availableColors;
    // Initialize SDL and get a surface
    SDL_Window *window = initializeSDL();
    SDL_Surface *screenSurface = SDL_GetWindowSurface( window );
    std::mutex myMutex;

    // Create board
    int BOARD_ROWS = 64;
    int BOARD_COLUMNS = 48;
    Board board(BOARD_COLUMNS, BOARD_ROWS);
    modifyStartingBoard(&board);

    // Timing information to cap FPS
    int start_time = 0;
    int delta = 0;
    int current_time = SDL_GetTicks();

    // Loop until window is closed
    bool keep_window_open = true;
    while(keep_window_open)
    {
        // Handle events
        SDL_Event e;
        while(SDL_PollEvent(&e) > 0)
        {
            // Exit on the press of the close button
            switch(e.type)
            {
                case SDL_QUIT:
                keep_window_open = false;
                break;
            }

        }

        // Cap FPS
        current_time = SDL_GetTicks();
        delta = current_time - start_time;
        if (60-delta>0)
        {
            SDL_Delay(60-delta);
            start_time = current_time;
        }
        else
        {
            SDL_Delay(0);
            start_time = current_time;
        }

        // Update and draw the board
        updateBoard(&board);
        board.draw(screenSurface);

        //Update the surface
        SDL_UpdateWindowSurface( window );
    }


    //Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();

    return 0;
}
