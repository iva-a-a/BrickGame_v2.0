#ifndef CONTROLLER_TETRIS_H
#define CONTROLLER_TETRIS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "back_tetris.h"

/**
 * @brief получение данных для отрисовки в интерфейсе
 *
 * @return возвращает структуру, содержащую информацию о текущем состоянии игры
 */
GameInfo_t updateCurrentState();

/**
 * @brief обработка нажатия кнопки
 *
 * @param action пользовательское действие
 * @param hold зажатие клавиши
 */
void userInput(UserAction_t action, bool hold);

#ifdef __cplusplus
}
#endif

#endif