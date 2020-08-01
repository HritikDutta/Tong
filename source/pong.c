#include "../includes/pong.h"
#include "../includes/misc.h"

#define __USE_MISC 1 // Defined to access M_PI
#include <math.h>

#define BALL_SPRITE 'O'
#define PADDLE_SPRITE (char)219

const double BALL_SPEED = 1.5;

const int PADDLE_SIZE = 5;
const int PADDLE_SPEED = 2;

/*
*   Functions for Resetting
*/

void reset_ball(BALL_DATA* ball)
{
    ball->posx = ball->posy = 0.0;
    ball->speed = BALL_SPEED;
    ball->direction = 1.0;
}

void reset_game(GAME_DATA* data)
{
    reset_ball(&(data->m_ball));
    data->p1_pos = data->p2_pos = 0.5 * data->m_paddle.size;
}

/*
*   Functions for Initializing
*/

void init_paddle(PADDLE_DATA* paddle, double unit_size)
{
    paddle->sprite = PADDLE_SPRITE;
    paddle->size = PADDLE_SIZE * unit_size;
    paddle->speed = PADDLE_SPEED * unit_size;
    paddle->range = 1.0 - (0.5 * paddle->size);
}

void init_game(GAME_DATA* data, double u_size)
{
    data->m_ball.sprite = BALL_SPRITE;
    reset_ball(&data->m_ball);

    init_paddle(&data->m_paddle, u_size);

    data->p1_pos = data->p2_pos = 0.0;
    data->p1_score = data->p2_score = 0;
}

/*
*   Functions for Updating
*/

bool collision_with_paddle(GAME_DATA* data, double ts)
{
    double ballY = data->m_ball.posy;
    double ballX = data->m_ball.posx + data->m_ball.speed * cos(data->m_ball.direction) * ts * 1e-3;
    
    return (
        // Check collision with right paddle
        ballX >= 1.0
        && ballY <= data->p2_pos + (0.5 * data->m_paddle.size)
        && ballY >= data->p2_pos - (0.5 * data->m_paddle.size)
    ) || (
        // Check collision with left paddle
        ballX <= -1.0
        && ballY <= data->p1_pos + (0.5 * data->m_paddle.size)
        && ballY >= data->p1_pos - (0.5 * data->m_paddle.size)
    );
}

void update_ball(GAME_DATA* data, double ts)
{
    // Bounce ball at horizontal walls
    if (data->m_ball.posy >= 1.0 || data->m_ball.posy <= -1.0)
        data->m_ball.direction *= -1.0;
    // Bounce ball and increase speed if hit with paddle
    else if (collision_with_paddle(data, ts))
    {
        data->m_ball.direction = M_PI - data->m_ball.direction;
        data->m_ball.speed += 0.1;
    }
    // Reset ball when it hits a vertical wall
    else if (data->m_ball.posx >= 1.0 || data->m_ball.posx <= -1.0)
        reset_ball(&data->m_ball);
    
    // Update position of ball
    data->m_ball.posx += data->m_ball.speed * cos(data->m_ball.direction) * ts * 1e-3;
    data->m_ball.posy += data->m_ball.speed * sin(data->m_ball.direction) * ts * 1e-3;

    clamp(&data->m_ball.posx, -1.0, 1.0);
    clamp(&data->m_ball.posy, -1.0, 1.0);
}

void update_paddles(GAME_DATA* data, int ch)
{
    switch(ch)
    {
        // Right Controls
        case KEY_UP:
            data->p2_pos += data->m_paddle.speed;
            data->p2_pos = min(data->p2_pos, data->m_paddle.range);
            break;
        case KEY_DOWN:
            data->p2_pos -= data->m_paddle.speed;
            data->p2_pos = max(data->p2_pos, -data->m_paddle.range);
            break;

        // Left Controls
        case 'w':
            data->p1_pos += data->m_paddle.speed;
            data->p1_pos = min(data->p1_pos, data->m_paddle.range);
            break;
        case 's':
            data->p1_pos -= data->m_paddle.speed;
            data->p1_pos = max(data->p1_pos, -data->m_paddle.range);
            break;
    }
}

void update_score(GAME_DATA* data, double ts)
{
    if (collision_with_paddle(data, ts)) return;

    if (data->m_ball.posx >= 1.0)
        data->p1_score++;
    else if (data->m_ball.posx <= -1.0)
        data->p2_score++;
}

void update_game(GAME_DATA* data, double ts)
{
    int ch = getch();

    update_score(data, ts);
    update_paddles(data, ch);
    update_ball(data, ts);
}