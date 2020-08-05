#include "../includes/game.h"
#include "../includes/pong.h"
#include "../includes/misc.h"

#include <stdlib.h>
#include <string.h>

const double move_speed = 6.0;

GAME* create_game(int x, int y, int width, int height)
{
    GAME* game = (GAME*)malloc(sizeof(GAME));
    
    game->x = x;
    game->y = y;
    game->width = width;
    game->height = height;
    game->window = newwin(height, width, y, x);
    
    game->data = (GAME_DATA*)malloc(sizeof(GAME_DATA));
    init_game(game->data, (2.0 / (height - 2)));

    return game;
}

void refresh_game(GAME* game)
{
    werase(game->window);
    box(game->window, 0, 0);
}

void render_ball(GAME* game)
{
    int ballx, bally;
    ballx = (game->width - 2) * (0.5 * (game->data->m_ball.posx + 1.0)) + 1;
    bally = (game->height - 2) * (0.5 * (1.0 - game->data->m_ball.posy)) + 1;
    mvwaddch(game->window, bally, ballx, game->data->m_ball.sprite);
}

void render_paddles(GAME* game)
{
    GAME_DATA* data = game->data;

    // Render Left paddle
    int start = (game->height - 2) * ((1.0 - (game->data->p1_pos + 0.5 * data->m_paddle.size)) * 0.5) + 1;
    int end = (game->height - 2) * ((1.0 - (game->data->p1_pos - 0.5 * data->m_paddle.size)) * 0.5) + 1;
    for (int i = start; i < end; i++)
        mvwaddch(game->window, i, 0, game->data->m_paddle.sprite);

    // Render Right paddle
    start = (game->height - 2) * ((1.0 - (game->data->p2_pos + 0.5 * data->m_paddle.size)) * 0.5) + 1;
    end = (game->height - 2) * ((1.0 - (game->data->p2_pos - 0.5 * data->m_paddle.size)) * 0.5) + 1;
    for (int i = start; i < end; i++)
        mvwaddch(game->window, i, game->width - 1, game->data->m_paddle.sprite);
}

void render_score(GAME* game)
{
    int lscore_length = digits(game->data->p1_score);
    int x = 0.5 * game->width - lscore_length - 2;

    mvwprintw(game->window, 1, x, "%d | %d", game->data->p1_score, game->data->p2_score);
}

void render_game(GAME* game)
{
    refresh_game(game);

    render_score(game);
    render_ball(game);
    render_paddles(game);

    wrefresh(game->window);
}

void delete_game(GAME* game)
{
    free(game->data);
    delwin(game->window);
}

void game_test()
{
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    nodelay(stdscr, TRUE);      // Don't wait for user input

    // Make cursor invisible
    curs_set(0);

    int width = 70, height = 20;
    int x = 0.5 * (COLS - width);
    int y = 0.5 * (LINES - height);
    GAME* game = create_game(x, y, width, height);

    double prev = time_ms();
    double current;

    int ch;

    // Print name of game
    const char* name = "TONG!";
    mvprintw(y - 1, 0.5 * (COLS - strlen(name)), name);

    bool run = true;

    // Game Loop
    while (run)
    {
        current = time_ms();
        run = update_game(game->data, current - prev);
        prev = current;

        render_game(game);
    }

    delete_game(game);
    endwin();
}