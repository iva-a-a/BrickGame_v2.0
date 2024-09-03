#include "display.h"

void setup_gui() {
  initscr();   /*инициализация ncurses*/
  curs_set(0); /*скрыть курсор*/
  noecho(); /*отключить вывод введенных символов на экран*/
  keypad(stdscr, TRUE); /*включить обработку функциональных клавиш*/
  nodelay(stdscr, TRUE); /*неблокирующее считывание клавиш*/
}

void delete_gui() { endwin(); /*завершение работы с ncurses*/ }

UserAction_t input_key() {
  UserAction_t return_key;
  int key = getch(); /*считываем клавишу с клавиатуры*/
  switch (key) {
    case KEY_DOWN:
      return_key = Down;
      break;
    case KEY_LEFT:
      return_key = Left;
      break;
    case KEY_RIGHT:
      return_key = Right;
      break;
    case 10: /*enter - начало игры*/
      return_key = Start;
      break;
    case 263: /*backspace - пауза*/
      return_key = Pause;
      break;
    case 27: /*esc - завершение игры*/
      return_key = Terminate;
      break;
    case 32: /*пробел - движение (поворот фигуры)*/
      return_key = Action;
      break;
    default:
      return_key = Up;
  }
  return return_key;
}

void print_game_board() {
  for (int i = 0; i < ROWS_BOARD + 2; i++) {
    for (int j = 0; j < (COL_BOARD + 2) * 2; j++) {
      if (i == 0 || i == ROWS_BOARD + 1) {
        if (j < (COL_BOARD + 2) * 2 - 2) {
          mvaddch(i, j, '.');
        } else {
          mvaddch(i, j, ' ');
        }
      } else if (j == 0 || j == (COL_BOARD + 1) * 2 - 1) {
        mvaddch(i, j, '.');
      } else if (j % 2 == 0) {
        mvaddch(i, j, ' ');
      } else {
        mvaddch(i, j, ' ');
      }
    }
  }
  mvprintw(10, 13, "%*c", 8, ' '); /*стираем стартовую заставку*/
}

void print_start() {
  for (int i = 0; i < 25; i++) {
    if (i != 10) {
      mvprintw(i, 0, "%*c", 80, ' ');
    }
  }
  mvprintw(10, 0, " Press ENTER to START%*c", 59, ' ');
}

void print_stats(Game_tetris *info) {
  mvprintw(0, 27, "NEXT");
  mvprintw(5, 27, "LEVEL");
  mvprintw(8, 27, "SPEED");
  mvprintw(11, 27, "SCORE");
  mvprintw(14, 27, "HIGH SCORE");
  mvprintw(17, 24, "ESC - exit");
  mvprintw(18, 24, "BACKSPACE - pause");
  mvprintw(19, 24, "SPACE - rotate");
  mvprintw(20, 24, "ARROWS - move");

  mvprintw(6, 29, "%d", info->game_info.level);
  mvprintw(9, 29, "%.2f", (float)1000 / info->game_info.speed);
  mvprintw(12, 29, "%d", info->game_info.score);
  mvprintw(15, 29, "%d", info->game_info.high_score);
}

void print_pause() {
  mvprintw(9, 0, "%*c", 22, ' ');
  mvprintw(10, 0, "        PAUSE         ");
  mvprintw(11, 0, "%*c", 22, ' ');
}

void print_game_over() {
  mvprintw(9, 0, "%*c", 22, ' ');
  mvprintw(10, 0, "      GAME OVER!      ");
  mvprintw(11, 0, "%*c", 22, ' ');
  mvprintw(21, 24, "ENTER - restart");
}

void print_fall_figure(Game_tetris *tetris) {
  for (int i = 0; i < ROWS_BOARD; i++) {
    for (int j = 0; j < COL_BOARD; j++) {
      if (tetris->game_info.field[i][j] == 1) {
        mvprintw(i + 1, j * 2 + 1, "[]");
      }
    }
  }
}

void print_now_figure(Game_tetris *tetris) {
  for (int i = 0; i < ROWS_FIGURE; i++) {
    for (int j = 0; j < COL_FIGURE; j++) {
      if (tetris->now[i][j] == 1) {
        mvprintw(tetris->y + i + 1, (tetris->x + j) * 2 + 1, "[]");
      }
    }
  }
}

void print_next_figure(Game_tetris *tetris) {
  for (int i = 0; i < ROWS_FIGURE - 1; i++) {
    for (int j = 0; j < COL_FIGURE; j++) {
      if (tetris->game_info.next[i][j] == 1) {
        mvprintw(2 + i, 28 + j * 2 + 1, "[]");
      } else {
        mvprintw(2 + i, 28 + j * 2 + 1, "  ");
      }
    }
  }
}
