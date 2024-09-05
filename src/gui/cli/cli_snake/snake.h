#pragma once

#include "../display.h"
#include "display_snake.h"

namespace s21 {

void game_snake();
void userInput(UserAction_t currentAction, bool hold);
GameInfo_t updateCurrentState();
void printCurrentState();

} // namespace s21