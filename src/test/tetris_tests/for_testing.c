#include "for_testing.h"

bool eq_mat(int **mat_1, int **mat_2, int row, int col) {
  bool eq = true;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (mat_1[i][j] != mat_2[i][j]) {
        eq = false;
      }
    }
  }
  return eq;
}

int **memory_alloc(int row, int col) {
  int **mat = (int **)malloc(sizeof(int *) * row);
  for (int i = 0; i < row; i++) {
    mat[i] = (int *)calloc(sizeof(int), col);
  }
  return mat;
}

void free_memory(int **mat, int row) {
  for (int i = 0; i < row; i++) {
    free(mat[i]);
  }
  free(mat);
}