#ifndef PONG_H
#define PONG_H

#include <ncurses.h>
#include <sys/time.h>

typedef struct
{
    char sprite;
    double posx, posy;
    double velx, vely;
} BALL;

typedef struct
{
    BALL m_ball;

    // Paddle
    chtype paddle;
    int half_paddle_size;

    // Players
    int p1_score, p2_score;
    double p1_pos, p2_pos;

} GAME_DATA;

void init_game(GAME_DATA* data);
void reset_game(GAME_DATA* data);

// Called in a loop
void update_game(GAME_DATA* data, double ts);

#endif // PONG_H