#include "../includes/pong.h"

#define BALL_SPRITE 'O'
const double BALL_SPEED = 7.5;

void reset_ball(BALL* ball)
{
    ball->posx = 0.0;
    ball->posy = 0.0;
    ball->velx = BALL_SPEED;
    ball->vely = BALL_SPEED * 0.5;
}

void clamp(double* val, double min, double max)
{
    *val = (*val > min) ? ((*val < max) ? *val : max) : min;
}

void init_game(GAME_DATA* data)
{
    data->m_ball.sprite = BALL_SPRITE;
    reset_ball(&(data->m_ball));

    data->p1_pos = data->p2_pos = 0.0;
    data->p1_score = data->p2_score = 0;
}

void reset_game(GAME_DATA* data)
{
    reset_ball(&(data->m_ball));
    data->p1_pos = data->p2_pos = 0.0;
}

void update_game(GAME_DATA* data, double ts)
{
    // Bounce ball at walls
    if (data->m_ball.posx >= 1.0 || data->m_ball.posx <= -1.0)
        data->m_ball.velx *= -1.0;

    if (data->m_ball.posy >= 1.0 || data->m_ball.posy <= -1.0)
        data->m_ball.vely *= -1.0;

    // Update position of ball
    data->m_ball.posx += data->m_ball.velx * ts * 1e-3;
    data->m_ball.posy += data->m_ball.vely * ts * 1e-3;
}