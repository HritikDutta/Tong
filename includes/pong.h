#ifndef PONG_H
#define PONG_H

#include <ncurses.h>
#include <sys/time.h>

typedef struct
{
    char sprite;
    double posx, posy;
    double velx, vely;
} BALL_DATA;

typedef struct
{
    char sprite;
    int size;
    int speed;
    double range;
} PADDLE_DATA;

typedef struct
{
    // Ball
    BALL_DATA m_ball;

    // Paddle
    PADDLE_DATA m_paddle;

    // Rendering Data
    double unit_size;

    // Players
    int p1_score, p2_score;
    double p1_pos, p2_pos;      // Positions of top ends of both paddles

} GAME_DATA;

void init_game(GAME_DATA* data, double u_size);
void reset_game(GAME_DATA* data);

// Called in a loop
void update_game(GAME_DATA* data, double ts);

#endif // PONG_H