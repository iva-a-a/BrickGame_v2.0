#pragma once

#include "../../../brick_game/snake/back_snake.h"
#include "../display.h"

namespace s21 {

void print_win();
void print_snake(std::list<Coordinate> snake);
void print_apple(Coordinate apple);
void print_stats_snake(GameInfo_t gameInfo);

} // namespace s21