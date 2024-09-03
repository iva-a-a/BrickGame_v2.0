#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdbool.h>

#include "defines.h"
#include "struct.h"

/**
 * @brief получение состояния игры
 *
 * @return возвращает структуру, содержащую информацию о текущем состоянии игры
 */
Game_tetris *get_GameInfo();

/**
 * @brief получение времени в миллисекундах
 *
 * @return возвращает время в миллисекундах
 */
long long int time_in_millisec();

/**
 * @brief иницилизация игры
 */
void setup_game();

/**
 * @brief начальное состояние игры
 */
void initial_info();

/**
 * @brief очистка состояние игры
 */
void free_info();

/**
 * @brief рандомноя фигура
 *
 * @param tetris состояние игры
 */

void gen_rand_figure(Game_tetris *tetris);

/**
 * @brief заполнение поля упавшими фигурами
 *
 * @param tetris состояние игры
 */

void filling_field(Game_tetris *tetris);

/**
 * @brief удаление заполненных строк
 *
 * @param tetris состояние игры
 *
 * @return количество убранных строк
 */

int remove_row(Game_tetris *tetris);

/**
 * @brief падение фигруры
 *
 * @param tetris состояние игры
 */

void fall_figure(Game_tetris *tetris);

/**
 * @brief вращение фигуры
 *
 * @param tetris состояние игры
 */

void rotate_figure(Game_tetris *tetris);

/**
 * @brief движение фигуры вправо, влево, вниз
 *
 * @param tetris состояние игры
 * @param key пользовательское действие
 */

void move_figure(Game_tetris *tetris, UserAction_t key);

/**
 * @brief касание фигуры поля или других фигур
 *
 * @param tetris состояние игры
 *
 * @return возращает состояние касания
 */

int collision(Game_tetris *tetris);

/**
 * @brief копирование фигуры
 *
 * @param tetris состояние игры
 */

void copy_figures(Game_tetris *tetris);

/**
 * @brief подсчет очков
 *
 * @param tetris состояние игры
 * @param count количество убранных линий
 *
 */

void scoring_points(Game_tetris *tetris, int count);

/**
 * @brief увеличение уровня
 *
 * @param tetris состояние игры
 */

void increase_level(Game_tetris *tetris);

/**
 * @brief сохранение рекордных очков
 *
 * @param tetris состояние игры
 */

void save_high_score(Game_tetris *tetris);

/**
 * @brief очистка матрицы (зануление элементов матрицы)
 *
 * @param matrix массив указателей матрицы
 * @param x количество строк матрицы
 * @param y количество столбцов матрицы
 */

void clear_mat(int **matrix, int x, int y);

/**
 * @brief очистка состояния игры
 */

void clearing_game();

#endif