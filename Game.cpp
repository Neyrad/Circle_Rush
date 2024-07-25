#include "Engine.h"
#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <windows.h>
#include <cmath>
#include <assert.h>

const int CHAR_WIDTH = 5;
const int CHAR_HEIGHT = 7;
const bool digits[10][CHAR_HEIGHT][CHAR_WIDTH] = {
	{
		{0, 1, 1, 1, 0},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{0, 1, 1, 1, 0},
	},
	{
		{0, 0, 1, 0, 0},
		{0, 1, 1, 0, 0},
		{1, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 1, 0, 0},
		{1, 1, 1, 1, 1},
	},
	{
		{1, 1, 1, 1, 0},
		{0, 0, 0, 0, 1},
		{0, 0, 0, 0, 1},
		{0, 1, 1, 1, 0},
		{1, 0, 0, 0, 0},
		{1, 0, 0, 0, 0},
		{1, 1, 1, 1, 1},
	},
	{
		{1, 1, 1, 1, 0},
		{0, 0, 0, 0, 1},
		{0, 0, 0, 0, 1},
		{0, 1, 1, 1, 0},
		{0, 0, 0, 0, 1},
		{0, 0, 0, 0, 1},
		{1, 1, 1, 1, 0},
	},
	{
		{0, 0, 0, 1, 0},
		{0, 0, 1, 1, 0},
		{0, 1, 0, 1, 0},
		{1, 0, 0, 1, 0},
		{1, 1, 1, 1, 1},
		{0, 0, 0, 1, 0},
		{0, 0, 0, 1, 0},
	},
	{
		{1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0},
		{1, 0, 0, 0, 0},
		{1, 1, 1, 1, 0},
		{0, 0, 0, 0, 1},
		{0, 0, 0, 0, 1},
		{1, 1, 1, 1, 0},
	},
	{
		{0, 1, 1, 1, 0},
		{1, 0, 0, 0, 0},
		{1, 0, 0, 0, 0},
		{1, 1, 1, 1, 0},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{0, 1, 1, 1, 0},
	},
	{
		{1, 1, 1, 1, 1},
		{0, 0, 0, 0, 1},
		{0, 0, 0, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 1, 0, 0, 0},
		{1, 0, 0, 0, 0},
		{1, 0, 0, 0, 0},
	},
	{
		{0, 1, 1, 1, 0},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{0, 1, 1, 1, 0},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{0, 1, 1, 1, 0},
	},
	{
		{0, 1, 1, 1, 0},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{0, 1, 1, 1, 1},
		{0, 0, 0, 0, 1},
		{0, 0, 0, 0, 1},
		{0, 1, 1, 1, 0},
	}
};


const int PLAY_WIDTH = 15;
const int PLAY_HEIGHT = 15;

const bool play[PLAY_HEIGHT][PLAY_WIDTH] = {
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
};

//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()

const float M_PI = 3.1415926535;

const int CENTER_X = SCREEN_WIDTH / 2;
const int CENTER_Y = SCREEN_HEIGHT / 2;

const int digitX = CENTER_X - 45;
const int digitY = CENTER_Y - 70;

const int RADIUS_BIG = 180;
const int RADIUS_SMALL = 30;

const uint32_t blue = 0x0000FF;
const uint32_t dark_blue = 0x000099;
const uint32_t yellow = 0xFFFF00;
const uint32_t red = 0xFF0000;
const uint32_t white = 0xFFFFFF;
const uint32_t almost_white = 0xFFFFFE;
const uint32_t green = 0x00FF00;
const uint32_t black = 0x000000;

bool startScreen = true;

int score = 0;

float angle = 0.0f;
bool clockwise = true;


const float KEY_DELAY = 0.2;

// Time

float lastKeyPressTime = 0;
float currentTime = 0;
float digitTime = 0;
float playTime = 0;

const int VERTICAL_SHIFT_CHANCE = 3;

// Box

int posX = 20;
int posY = 0;
int colorSquare = (rand() % 2) ? black : almost_white;
bool verticalDirectionUp = rand() % 2;
bool clockwiseBox = rand() % 2;
float angleBox = 0.0f;

bool show0 = false;
bool show1 = false;
bool show2 = false;
bool show3 = false;

bool squareDestroyed = false;

void DrawFilledSquare(int centerX, int centerY, double angle, int size, int color)
{
	int half_size = size / 2;

	for (int y = -half_size; y <= half_size; ++y)
		for (int x = -half_size; x <= half_size; ++x)
		{
			int rotated_x = x * cos(angle) - y * sin(angle);
			int rotated_y = x * sin(angle) + y * cos(angle);

			if (buffer[centerY + rotated_y][centerX + rotated_x] == white) // collision
			{
				if (color == black)
				{
					startScreen = true;
					playTime = currentTime;
				}
				if (color == almost_white)
				{
					score++;
					if (score > 999) score = 999;
					squareDestroyed = true;
					return;
				}
			}
			buffer[centerY + rotated_y][centerX + rotated_x] = color;
		}
}

void DrawDigit(int x, int y, int digit, int color, int SCALE)
{
	if (digit < 0 || digit > 9) return;

	for (int row = 0; row < CHAR_HEIGHT; row++)
	{
		for (int col = 0; col < CHAR_WIDTH; col++)
		{
			if (digits[digit][row][col])
			{
				for (int j = 0; j < SCALE; ++j)
				{
					for (int i = 0; i < SCALE; ++i)
					{
						buffer[y + SCALE * row + j][x + SCALE * col + i] = color;
					}
				}
			}
		}
	}
}

void DrawPlay(int x, int y, int color, int SCALE)
{
	for (int row = 0; row < PLAY_HEIGHT; row++)
	{
		for (int col = 0; col < PLAY_WIDTH; col++)
		{
			if (play[row][col])
			{
				for (int j = 0; j < SCALE; ++j)
				{
					for (int i = 0; i < SCALE; ++i)
					{
						buffer[y + SCALE * row + j][x + SCALE * col + i] = color;
					}
				}
			}
		}
	}
}

void DrawFilledCircle(int centerX, int centerY, int radius, int color)
{
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w;
			int dy = radius - h;
			if ((dx * dx + dy * dy) <= (radius * radius))
			{
				buffer[centerY + dy][centerX + dx] = color;
			}
		}
	}
}

// initialize game data in this function
void initialize()
{
	memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
	for (int y = 0; y < SCREEN_HEIGHT; ++y)
		for (int x = 0; x < SCREEN_WIDTH; ++x)
			buffer[y][x] = blue;

	DrawFilledCircle(CENTER_X, CENTER_Y, RADIUS_BIG, dark_blue);

	if (score >= 100)
	{
		DrawDigit(SCREEN_WIDTH - 82, 10, score / 100, white, 4);
	}

	if (score >= 10)
	{
		DrawDigit(SCREEN_WIDTH - 56, 10, (score % 100) / 10, white, 4);
	}

	DrawDigit(SCREEN_WIDTH - 30, 10, score % 10, white, 4);
}

void CirclesMovement()
{
	if (is_key_pressed(VK_SPACE))
	{
		if (currentTime - lastKeyPressTime > KEY_DELAY)
		{
			lastKeyPressTime = currentTime;
			clockwise = !clockwise;
		}
	}

	int smallCircleX = CENTER_X + RADIUS_BIG * cos(angle);
	int smallCircleY = CENTER_Y + RADIUS_BIG * sin(angle);

	DrawFilledCircle(smallCircleX, smallCircleY, RADIUS_SMALL, white);

	smallCircleX = CENTER_X - RADIUS_BIG * cos(angle);
	smallCircleY = CENTER_Y - RADIUS_BIG * sin(angle);

	DrawFilledCircle(smallCircleX, smallCircleY, RADIUS_SMALL, white);

	if (clockwise)
	{
		angle += 0.042f;
		if (angle > 2 * M_PI)
		{
			angle -= 2 * M_PI;
		}
	}

	if (!clockwise)
	{
		angle -= 0.042f;
		if (angle < -2 * M_PI)
		{
			angle += 2 * M_PI;
		}
	}
}

void BoxMovement()
{
	DrawFilledSquare(posX, posY, angleBox, 40, colorSquare);
	posX += 5;

	if (clockwiseBox)
	{
		angleBox += 0.006f;
		if (angleBox > 2 * M_PI)
		{
			angleBox -= 2 * M_PI;
		}
	}

	if (!clockwiseBox)
	{
		angleBox -= 0.006f;
		if (angleBox < -2 * M_PI)
		{
			angleBox += 2 * M_PI;
		}
	}

	if (!(rand() % VERTICAL_SHIFT_CHANCE))
	{
		posY += verticalDirectionUp ? -2 : 2;
	}
	if (posX >= SCREEN_WIDTH - 20 || squareDestroyed)
	{
		squareDestroyed = false;
		posX = 20;
		posY = CENTER_Y;
		colorSquare = (rand() % 3) ? black : almost_white;
		verticalDirectionUp = rand() % 2;
		clockwiseBox = rand() % 2;
		angleBox = 0;
	}
}

bool CountDown()
{
	if (show3)
	{
		digitTime = currentTime;
		show3 = false;
		show2 = true;
		initialize();
		DrawDigit(digitX, digitY, 3, white, 20);
		return true;
	}

	if (show2)
	{
		if (currentTime - digitTime < 1)
			return true;
		digitTime = currentTime;
		show2 = false;
		show1 = true;
		initialize();
		DrawDigit(digitX, digitY, 2, white, 20);
		return true;
	}

	if (show1)
	{
		if (currentTime - digitTime < 1)
			return true;
		digitTime = currentTime;
		show1 = false;
		show0 = true;
		initialize();
		DrawDigit(digitX, digitY, 1, white, 20);
		return true;
	}

	if (show0)
	{
		if (currentTime - digitTime < 1)
			return true;
		digitTime = currentTime;
		show0 = false;
		return true;
	}

	return false;
}

bool StartScreen()
{
	if (is_key_pressed(VK_SPACE) && startScreen)
	{
		if (currentTime - playTime < 0.5)
			return true;
		startScreen = false;
		score = 0;
		angle = 0;
		posX = 0;
		posY = CENTER_Y;
		colorSquare = (rand() % 3) ? black : almost_white;
		verticalDirectionUp = rand() % 2;
		clockwiseBox = rand() % 2;
		angleBox = 0;
		show3 = true;  
		return true;
	}

	if (startScreen)
	{
		initialize();
		DrawPlay(digitX - 26, digitY - 18, white, 12);
		return true;
	}

	return false;
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)

void act(float dt)
{
	if (is_key_pressed(VK_ESCAPE))
		schedule_quit_game();

	currentTime += dt;

	if (CountDown()) return;
	if (StartScreen()) return;
	initialize();
	CirclesMovement();
	BoxMovement();
	Sleep(1);
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
	// clear backbuffer



}

// free game data in this function
void finalize()
{
}

