#include "../includes/pong.h"
#include "../includes/misc.h"

#define __USE_MISC 1 // Defined to access M_PI
#include <math.h>

#define BALL_SPRITE 'O'
#define PADDLE_SPRITE (char)219

const double BALL_SPEED = 1.5;
const double BALL_SPREAD = 0.2;

const int PADDLE_SIZE = 5;
const int PADDLE_SPEED = 2;

const double GAME_SPEED_INCREASE = 0.05;

/*
*   Functions for Resetting
*/

void reset_ball(BALL_DATA* ball)
{
    ball->posx = ball->posy = 0.0;
    ball->speed = BALL_SPEED;
    // Give the ball a random direction between -1 and 1 radians
    ball->direction = i_random() * 2.0 - 1.0;
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

void init_game(GAME_DATA* data, double u_size, bool is_vs)
{
    init_random();

    data->m_ball.sprite = BALL_SPRITE;
    reset_ball(&data->m_ball);

    init_paddle(&data->m_paddle, u_size);

    data->p1_pos = data->p2_pos = 0.0;
    data->p1_score = data->p2_score = 0;

    data->vs_mode = is_vs;
}

/*
*   Functions for Updating
*/

// TODO: Try and make a time independent version of this
bool collision_with_paddle(GAME_DATA* data, double ts)
{
    double ballY = data->m_ball.posy;
    double ballX = data->m_ball.posx + data->m_ball.speed * cos(data->m_ball.direction) * ts * 1e-3;
    
    return (
        // Check collision with right paddle
        ballX >= 1.0
        && ballY < data->p2_pos + (0.51 * data->m_paddle.size)
        && ballY > data->p2_pos - (0.51 * data->m_paddle.size)
    ) || (
        // Check collision with left paddle
        ballX <= -1.0
        && ballY < data->p1_pos + (0.51 * data->m_paddle.size)
        && ballY > data->p1_pos - (0.51 * data->m_paddle.size)
    );
}

// Alter direction of the ball based on how close it hits to the centre of the paddle
void alter_ball_direction(GAME_DATA* data)
{
    if (data->m_ball.posx > 0)
        data->m_ball.direction +=
            BALL_SPREAD * cos(M_PI * (data->m_ball.posy - data->p2_pos) / data->m_paddle.size);
    else
        data->m_ball.direction +=
            BALL_SPREAD * cos(M_PI * (data->m_ball.posy - data->p1_pos) / data->m_paddle.size);
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
        alter_ball_direction(data);
        data->m_ball.speed += GAME_SPEED_INCREASE;
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

// Paddle update function for playing against computer
void update_paddles_ai(GAME_DATA* data, int ch)
{
    switch(ch)
    {
        // Left Controls
        case KEY_UP:
            data->p1_pos += data->m_paddle.speed;
            data->p1_pos = min(data->p1_pos, data->m_paddle.range);
            break;
        case KEY_DOWN:
            data->p1_pos -= data->m_paddle.speed;
            data->p1_pos = max(data->p1_pos, -data->m_paddle.range);
            break;
    }

    // Super OP AI player
    data->p2_pos = data->m_ball.posy;
    clamp(&data->p2_pos, -data->m_paddle.range, data->m_paddle.range);
}

void update_paddles_vs(GAME_DATA* data, int ch)
{
    switch(ch)
    {
        // Left Controls
        case 'w':
            data->p1_pos += data->m_paddle.speed;
            data->p1_pos = min(data->p1_pos, data->m_paddle.range);
            break;
        case 's':
            data->p1_pos -= data->m_paddle.speed;
            data->p1_pos = max(data->p1_pos, -data->m_paddle.range);
            break;
        // Right Controls
        case KEY_UP:
            data->p2_pos += data->m_paddle.speed;
            data->p2_pos = min(data->p2_pos, data->m_paddle.range);
            break;
        case KEY_DOWN:
            data->p2_pos -= data->m_paddle.speed;
            data->p2_pos = max(data->p2_pos, -data->m_paddle.range);
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

// TODO: Add an exit condition
bool update_game(GAME_DATA* data, double ts)
{
    int ch = getch();

    // Use correct paddle update function according to game mode
    if (data->vs_mode) update_paddles_vs(data, ch);
    else update_paddles_ai(data, ch);

    update_ball(data, ts);
    update_score(data, ts);

    return ch != KEY_F(1);
}