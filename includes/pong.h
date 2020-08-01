#ifndef PONG_H
#define PONG_H

#include <ncurses.h>
#include <sys/time.h>

typedef struct
{
    char sprite;
    double posx, posy;
    double speed, direction; // direction in radians
} BALL_DATA;

typedef struct
{
    char sprite;
    double size;
    double speed;
    double range;
} PADDLE_DATA;

typedef struct
{
    // Ball
    BALL_DATA m_ball;

    // Paddle
    PADDLE_DATA m_paddle;

    // Players
    int p1_score, p2_score;
    double p1_pos, p2_pos;
} GAME_DATA;

void init_game(GAME_DATA* data, double u_size);
void reset_game(GAME_DATA* data);

// Called in a loop
void update_game(GAME_DATA* data, double ts);

#endif // PONG_H