#include "../includes/pong.h"

#define BALL_SPRITE 'O'
#define PADDLE_SPRITE (char)219

const double BALL_SPEED = 2.0;

const int PADDLE_SIZE = 5;
const int PADDLE_SPEED = 2;

void reset_ball(BALL_DATA* ball)
{
    ball->posx = ball->posy = 0.0;
    ball->velx = BALL_SPEED;
    ball->vely = BALL_SPEED * 0.75;
}

void init_paddle(PADDLE_DATA* paddle, double unit_size)
{
    paddle->sprite = PADDLE_SPRITE;
    paddle->size = PADDLE_SIZE;
    paddle->speed = PADDLE_SPEED;
    paddle->range = 1.0 - (paddle->size * unit_size);
}

void clamp(double* val, double min, double max)
{
    *val = (*val > min) ? ((*val < max) ? *val : max) : min;
}

double min(double a, double b)
{
    return (a < b) ? a : b;
}

double max(double a, double b)
{
    return (a > b) ? a : b;
}

void init_game(GAME_DATA* data, double u_size)
{
    data->m_ball.sprite = BALL_SPRITE;
    reset_ball(&data->m_ball);

    init_paddle(&data->m_paddle, u_size);

    data->unit_size = u_size;

    data->p1_pos = data->p2_pos = 0.5 * data->m_paddle.size * data->unit_size;
    data->p1_score = data->p2_score = 0;
}

void reset_game(GAME_DATA* data)
{
    reset_ball(&(data->m_ball));
    data->p1_pos = data->p2_pos = 0.5 * data->m_paddle.size * data->unit_size;
}

void update_ball(GAME_DATA* data, double ts)
{
    // Bounce ball at walls
    if (data->m_ball.posx >= 1.0 || data->m_ball.posx <= -1.0)
        data->m_ball.velx *= -1.0;

    if (data->m_ball.posy >= 1.0 || data->m_ball.posy <= -1.0)
        data->m_ball.vely *= -1.0;

    // Update position of ball
    data->m_ball.posx += data->m_ball.velx * ts * 1e-3;
    data->m_ball.posy += data->m_ball.vely * ts * 1e-3;

    clamp(&data->m_ball.posx, -1.0, 1.0);
    clamp(&data->m_ball.posy, -1.0, 1.0);
}

void update_paddles(GAME_DATA* data, int ch)
{
    switch(ch)
    {
        // Right Controls
        case KEY_UP:
            data->p2_pos += data->m_paddle.speed * data->unit_size;
            data->p2_pos = min(data->p2_pos, 1.0);
            break;
        case KEY_DOWN:
            data->p2_pos -= data->m_paddle.speed * data->unit_size;
            data->p2_pos = max(data->p2_pos, -data->m_paddle.range);
            break;

        // Left Controls
        case 'w':
            data->p1_pos += data->m_paddle.speed * data->unit_size;
            data->p1_pos = min(data->p1_pos, 1.0);
            break;
        case 's':
            data->p1_pos -= data->m_paddle.speed * data->unit_size;
            data->p1_pos = max(data->p1_pos, -data->m_paddle.range);
            break;
    }
}

void update_game(GAME_DATA* data, double ts)
{
    int ch = getch();

    update_paddles(data, ch);
    update_ball(data, ts);
}