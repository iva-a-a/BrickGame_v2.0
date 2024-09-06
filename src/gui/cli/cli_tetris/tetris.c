#include "tetris.h"

void game_tetris() {
  Game_tetris *tetris = get_GameInfo();
  while (tetris->state != Exit) {
    userInput(input_key(), false);
    Game_tetris game_state = updateCurrentState();
    printCurrentState(&game_state);
  }
}

void userInput(UserAction_t action, bool hold) {
  Game_tetris *tetris = get_GameInfo();
  if (action == Start && tetris->state == Begin) {
    tetris->state = Generation;
  } else if (tetris->state == Falling) {
    if (action == Pause) {
      tetris->state = Break;
    } else if (action == Left && !hold) {
      tetris->state = Moving_left;
    } else if (action == Right && !hold) {
      tetris->state = Moving_right;
    } else if (action == Down) {
      tetris->state = Moving_down;
    } else if (action == Action) {
      tetris->state = Moving_rotate;
    } else if (action == Terminate) {
      tetris->state = End;
    }
  } else if (tetris->state == Break) {
    if (action == Pause) {
      tetris->state = Falling;
    } else if (action == Terminate) {
      tetris->state = End;
    }
  } else if (tetris->state == End) {
    if (action == Start) {
      tetris->state = Begin;
    } else if (action == Terminate) {
      tetris->state = Exit;
    }
  }
}

Game_tetris updateCurrentState() {
  Game_tetris *tetris = get_GameInfo();
  if (tetris->state == Begin) {
    clearing_game();
  } else if (tetris->state == Generation) {
    tetris->x = COL_BOARD / 2 - COL_FIGURE / 2;
    tetris->y = 0;
    tetris->prev_time = time_in_millisec();
    copy_figures(tetris);
    gen_rand_figure(tetris);
    if (collision(tetris) == 0) {
      tetris->state = Falling;
    } else {
      tetris->state = End;
    }
  } else if (tetris->state == Falling) {
    fall_figure(tetris);
  } else if (tetris->state == Moving_down) {
    move_figure(tetris, Down);
    tetris->state = Falling;
  } else if (tetris->state == Moving_left) {
    move_figure(tetris, Left);
    tetris->state = Falling;
  } else if (tetris->state == Moving_right) {
    move_figure(tetris, Right);
    tetris->state = Falling;
  } else if (tetris->state == Moving_rotate) {
    rotate_figure(tetris);
    tetris->state = Falling;
  } else if (tetris->state == Attaching) {
    filling_field(tetris);
    scoring_points(tetris, remove_row(tetris));
    increase_level(tetris);
    save_high_score(tetris);
    tetris->state = Generation;
  }
  return *tetris;
}

void printCurrentState(Game_tetris *tetris) {
  if (tetris->state == Begin) {
    print_start();
  } else if (tetris->state == End) {
    print_game_over();
  } else {
    print_game_board();
    print_stats();
    print_stats_tetris(tetris);
    print_now_figure(tetris);
    print_next_figure(tetris);
    print_fall_figure(tetris);
    if (tetris->state == Break) {
      print_pause();
    }
  }
  refresh();
}
