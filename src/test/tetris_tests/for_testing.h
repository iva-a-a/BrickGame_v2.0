#include "tetrisTests_suite.h"

/*сравнение матриц фигур/полей тетриса*/
bool eq_mat(int **mat_1, int **mat_2, int row, int col);

/*выделение памяти матрицу фигуры/поля тетриса*/
int **memory_alloc(int row, int col);

/*очистка памяти под фигуру/поле*/
void free_memory(int **mat, int row);
