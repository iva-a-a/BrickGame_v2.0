#ifndef BACK_TETRIS_H
#define BACK_TETRIS_H

#include <stdbool.h>

#include "../defines.h"
#include "../struct.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct Game_tetris
 * @brief полная информация о текущем состоянии игры
 */
typedef struct {
  /** игровое поле */
  int **field;
  /** превью фигура */
  int **next;
  /** текущая фигура на поле */
  int **now;
  /** координата фигуры по строке */
  int x;
  /** координата фигуры по столбцу */
  int y;
  /** номер текущей фигуры */
  int number_now_f;
  /** номер следующей генерируемой фигуры */
  int number_next_f;
  /** предыдущее время падения фигуры */
  long long int prev_time;
  /** количество очков */
  int score;
  /** количество рекордных очков */
  int high_score;
  /** номер уровня */
  int level;
  /** скорость */
  int speed;
  /** информация о состоянии конечного автомата */
  GameState_t state;
} Game_tetris;

/**
 * @brief получение состояния игры
 *
 * @return возвращает указатель на структуру, содержащую информацию о текущем
 * состоянии игры
 */

GameInfo_t *get_GameInfo();

/**
 * @brief иницилизация игры
 *
 * @param tetris состояние игры
 */
void setup_game(Game_tetris *tetris);

/**
 * @brief начальное состояние игры
 *
 * @param tetris состояние игры
 */
void initial_info(Game_tetris *tetris);

/**
 * @brief очистка состояние игры
 *
 * @param tetris состояние игры
 */
void free_info(Game_tetris *tetris);

/**
 * @brief генерация рандомной фигуры
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
 * @brief падение фигуры
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
 *
 * @param tetris состояние игры
 */

void clearing_game(Game_tetris *tetris);

/**
 * @brief обновление состояния игры
 *
 * @param tetris состояние игры
 */
void update_game(Game_tetris *tetris);

/**
 * @brief конвертирует матрицы, путем извлечения координат всех единиц из
 * входной матрицы и сдвиг их на заданные значения x и y
 *
 *@param arr1 указатель на входную матрицу
 * @param row количество строк в матрице
 * @param col количество столбцов в матрице
 * @param x значение, на которое будет сдвинута строка (горизонтально)
 * @param y Значение, на которое будет сдвинута колонка (вертикально)
 *
 * @return указатель на новую матрицу
 */
int **convert_matrix(int **arr1, int row, int col, int x, int y);

/**
 * @brief устанавливает код цвета для кажого элемента матрицы
 *
 * @param arr указатель на входную матрицу
 * @param color номер цвета
 */
void set_color_third_elem(int **arr, int color);
/**
 * @brief соединение двух матриц
 *
 * @param arr1 указатель на входную матрицу 1
 * @param arr2 указатель на входную матрицу 2
 */
int **join_matrix(int **arr1, int **arr2);

/**
 * @brief очистка памяти под матрицу
 *
 * @param arr указатель на входную матрицу
 */
void free_matrix(int **arr);

/**
 * @brief очистка памяти для информации о текущем состоянии игры
 *
 * @param info указатель на структуру, содержащую информацию о текущем
 */
void free_gameinfo(GameInfo_t *info);

#ifdef __cplusplus
}
#endif

#endif