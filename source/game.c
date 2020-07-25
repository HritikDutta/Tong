#include "../includes/game.h"
#include "../includes/pong.h"

#include <sys/time.h>
#include <stdlib.h>

GAME* create_game(int x, int y, int width, int height)
{
    GAME* game = (GAME*)malloc(sizeof(GAME));
    
    game->x = x;
    game->y = y;
    game->width = width;
    game->height = height;
    game->window = newwin(height, width, y, x);
    
    game->data = (GAME_DATA*)malloc(sizeof(GAME_DATA));
    init_game(game->data);

    return game;
}

void refresh_game(GAME* game)
{
    werase(game->window);
    wborder(game->window, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219, (char)219);
}

void render_game(GAME* game)
{
    refresh_game(game);

    // Render ball
    int ballx, bally;
    ballx = (game->width - 2) * (0.5 * (game->data->m_ball.posx + 1.0)) + 1;
    bally = (game->height - 2) * (0.5 * (1.0 - game->data->m_ball.posy)) + 1;
    mvwaddch(game->window, bally, ballx, game->data->m_ball.sprite);

    wrefresh(game->window);
}

void delete_game(GAME* game)
{
    free(game->data);
    delwin(game->window);
}

double time_ms()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000.0 + tv.tv_usec * 0.001;
}

void game_test()
{
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    
    // Make cursor invisible
    curs_set(0);

    int width = 40, height = 15;
    int x = 0.5 * (COLS - width);
    int y = 0.5 * (LINES - height);
    GAME* game = create_game(x, y, width, height);

    double prev = time_ms();
    double current;

    // Game Loop
    while (true)
    {
        current = time_ms();
        update_game(game->data, current - prev);
        prev = current;

        render_game(game);
    }

    delete_game(game);
    endwin();
}