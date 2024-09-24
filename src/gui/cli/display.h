#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>

#include "../../brick_game/tetris/back_tetris.h"

/**
 * @brief иницилизация графического интерфейса программы
 */
void setup_gui();

/**
 * @brief удаление графического интерфейса
 */
void delete_gui();

/**
 * @brief ввод с клавиатуры
 *
 * @return возвращает пользовательское действие
 */
UserAction_t input_key();

/**
 * @brief отрисовка заставки для выбора игры
 */
void print_game_setection();

/**
 * @brief очистка заставки для выбора игры
 */
void clear_screen();

/**
 * @brief отрисовка игрового поля
 */
void print_game_board();

/**
 * @brief вывод информациии об игре
 */
void print_stats_ban();

/**
 * @brief вывод заставки начала игры
 */
void print_start();

/**
 * @brief вывод сообщения об паузе
 */
void print_pause();

/**
 * @brief вывод сообщения об окончании игры
 */
void print_game_over();

/**
 * @brief отрисовка массива
 * @param arr указатель на массив
 */
void print_arr(int **arr);

/**
 * @brief вывод статистики игры
 * @param level номер уровня
 * @param speed скорость игры
 * @param score количество очков
 * @param high_score количество рекордных очков
 */
void print_stats(int level, int speed, int score, int high_score);

#endif