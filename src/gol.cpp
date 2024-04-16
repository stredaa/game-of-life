#include "gol.hpp"
#include "Arduino.h"

bool current_state = false;
bool internal_state[2][GOL_HEIGHT * GOL_WIDTH];

GameOfLife::GameOfLife()
{
    for (size_t i = 0; i < GOL_HEIGHT; i++)
    {
        for (size_t j = 0; j < GOL_WIDTH; j++)
        {
            internal_state[0][i * GOL_WIDTH + j] = random(2);
            internal_state[1][i * GOL_WIDTH + j] = random(2);
        }
    }
}

bool *GameOfLife::getState()
{
    return internal_state[current_state];
}

void GameOfLife::step()
{
    for (size_t i = 0; i < GOL_HEIGHT; i++)
    {
        for (size_t j = 0; j < GOL_WIDTH; j++)
        {
            char neighbours = 0;
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    if (x == 0 && y == 0)
                        continue;

                    neighbours += internal_state[current_state][((i + x) % GOL_HEIGHT) * GOL_WIDTH + ((j + y) % GOL_WIDTH)];
                }

            }
            switch (neighbours) {
                case 0:  // underpopulation
                case 1:
                    internal_state[current_state ^ 1][i * GOL_WIDTH + j] = 0;
                    break;
                case 2: // survive
                    internal_state[current_state ^ 1][i * GOL_WIDTH + j] = internal_state[current_state][i * GOL_WIDTH + j];
                    break;
                case 3: // survive or reproduce
                    internal_state[current_state ^ 1][i * GOL_WIDTH + j] = 1;
                    break;
                default: // overpopulation
                    internal_state[current_state ^ 1][i * GOL_WIDTH + j] = 0;
            }
        }
    }
    current_state ^= 1;
}