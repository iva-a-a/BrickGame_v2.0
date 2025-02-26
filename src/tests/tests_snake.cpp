#include "s21_tests.h"

class TestSnake : public s21::SnakeGame {
 public:
  TestSnake() = default;
  ~TestSnake() = default;
  void set_score(int score) { s_score = score; }
  void set_apple(s21::Coordinate a) { apple = a; }
  void set_snake(const std::list<s21::Coordinate> &s) { snake = s; }
};

TEST(ModelSnakeGameTest, StateActionSetGet) {
  s21::SnakeGame snake;
  EXPECT_EQ(snake.get_state(), Begin);
  snake.set_state(Exit);
  EXPECT_EQ(snake.get_state(), Exit);

  EXPECT_EQ(snake.get_currAction(), None);
  snake.set_currAction(Right);
  EXPECT_EQ(snake.get_currAction(), Right);
}

TEST(ModelSnakeGameTest, ConstClearSnake) {
  s21::SnakeGame snake;
  EXPECT_EQ(snake.get_score(), 0);
  EXPECT_EQ(snake.get_high_score(), 0);
  EXPECT_EQ(snake.get_level(), 1);
  EXPECT_EQ(snake.get_speed(), 500);
  EXPECT_EQ(snake.get_currAction(), None);
  EXPECT_EQ(snake.get_state(), Begin);
}

TEST(ModelSnakeGameTest, GetSnake) {
  s21::SnakeGame snake;
  snake.create_snake();
  auto &coord = snake.get_snake();
  EXPECT_EQ(coord.size(), 4);
  EXPECT_EQ(coord.front().x, 18);
  EXPECT_EQ(coord.front().y, 5);
}

TEST(ModelSnakeGameTest, GetApple) {
  s21::SnakeGame snake;
  snake.put_apple();
  s21::Coordinate apple = snake.get_apple();
  EXPECT_GE(apple.x, 0);
  EXPECT_LT(apple.x, ROWS_BOARD);
  EXPECT_GE(apple.y, 0);
  EXPECT_LT(apple.y, COL_BOARD);
}

TEST(ModelSnakeGameTest, PutAppleCreateSn) {
  s21::SnakeGame snake;
  snake.create_snake();
  snake.put_apple();
  s21::Coordinate apple = snake.get_apple();
  for (const auto &i : snake.get_snake()) {
    EXPECT_FALSE(apple.eq_coordinate(i));
  }
  std::list<s21::Coordinate> check_snake = {{18, 5}, {17, 5}, {16, 5}, {15, 5}};

  ASSERT_EQ(snake.get_snake().size(), check_snake.size());

  auto i1 = snake.get_snake().begin();
  auto i2 = check_snake.begin();
  for (; i1 != snake.get_snake().end() && i2 != check_snake.end(); ++i1, ++i2) {
    EXPECT_EQ(*i1, *i2);
  }
}

TEST(ModelSnakeGameTest, ChangeDirection) {
  s21::SnakeGame snake;

  snake.create_snake();
  snake.change_direction(Down);

  std::list<s21::Coordinate> check_snake = snake.get_snake();
  s21::Coordinate head_before = check_snake.back();
  sleep(1);
  snake.check_move_snake();
  check_snake = snake.get_snake();
  s21::Coordinate head_after = check_snake.back();
  EXPECT_EQ(head_after.y, head_before.y);
  EXPECT_EQ(head_after.x + 1, head_before.x);

  snake.change_direction(Right);
  check_snake = snake.get_snake();
  head_before = check_snake.back();
  sleep(1);
  snake.check_move_snake();
  check_snake = snake.get_snake();
  head_after = check_snake.back();
  EXPECT_EQ(head_after.y, head_before.y + 1);
  EXPECT_EQ(head_after.x, head_before.x);

  snake.change_direction(Up);
  check_snake = snake.get_snake();
  head_before = check_snake.back();
  sleep(1);
  snake.check_move_snake();
  check_snake = snake.get_snake();
  head_after = check_snake.back();
  EXPECT_EQ(head_after.y, head_before.y);
  EXPECT_EQ(head_after.x + 1, head_before.x);

  snake.change_direction(Left);
  check_snake = snake.get_snake();
  head_before = check_snake.back();
  sleep(1);
  snake.check_move_snake();
  check_snake = snake.get_snake();
  head_after = check_snake.back();
  EXPECT_EQ(head_after.y + 1, head_before.y);
  EXPECT_EQ(head_after.x, head_before.x);
}

TEST(ModelSnakeGameTest, SnakeHeadNewPos) {
  s21::SnakeGame snake;
  snake.create_snake();
  snake.change_direction(Up);
  s21::Coordinate newPos = snake.snake_head_new_pos();
  EXPECT_EQ(newPos.x, snake.get_snake().back().x - 1);
  EXPECT_EQ(newPos.y, snake.get_snake().back().y);

  snake.change_direction(Down);
  newPos = snake.snake_head_new_pos();
  EXPECT_EQ(newPos.x, snake.get_snake().back().x - 1);
  EXPECT_EQ(newPos.y, snake.get_snake().back().y);

  snake.change_direction(Left);
  newPos = snake.snake_head_new_pos();
  EXPECT_EQ(newPos.x, snake.get_snake().back().x);
  EXPECT_EQ(newPos.y, snake.get_snake().back().y - 1);

  snake.change_direction(Right);
  newPos = snake.snake_head_new_pos();
  EXPECT_EQ(newPos.x, snake.get_snake().back().x);
  EXPECT_EQ(newPos.y, snake.get_snake().back().y + 1);
}

TEST(ModelSnakeGameTest, Collision) {
  s21::SnakeGame snake;
  snake.create_snake();
  s21::Coordinate testCoor = {17, 5};
  EXPECT_TRUE(snake.collision(testCoor));

  testCoor = {19, 5};
  EXPECT_FALSE(snake.collision(testCoor));

  testCoor = {0, 21};
  EXPECT_TRUE(snake.collision(testCoor));
}

TEST(ModelSnakeGameTest, MoveSnake) {
  TestSnake snake;
  snake.create_snake();
  snake.change_direction(Right);
  snake.move_snake();

  auto headPos = snake.snake_head_new_pos();
  EXPECT_EQ(snake.get_snake().back().x, headPos.x);
  EXPECT_EQ(snake.get_snake().back().y + 1, headPos.y);

  snake.set_snake({{0, 0}, {0, 1}});
  snake.change_direction(Up);
  snake.change_direction(Left);
  sleep(1);
  snake.move_snake();
  EXPECT_EQ(snake.get_state(), End);

  snake.create_snake();
  snake.change_direction(Up);
  snake.set_apple({14, 5});
  sleep(1);
  snake.move_snake();
  EXPECT_EQ(snake.get_score(), 1);
  EXPECT_EQ(snake.get_state(), Attaching);

  snake.create_snake();
  snake.change_direction(Up);
  snake.set_apple({14, 5});
  snake.set_score(199);
  sleep(1);
  snake.move_snake();
  EXPECT_EQ(snake.get_score(), 200);
  EXPECT_EQ(snake.get_state(), End);
}

TEST(ModelSnakeGameTest, Update) {
  s21::SnakeGame snake;
  snake.set_state(Begin);

  snake.update();
  EXPECT_EQ(snake.get_score(), 0);
  EXPECT_EQ(snake.get_high_score(), 0);
  EXPECT_EQ(snake.get_level(), 1);
  EXPECT_EQ(snake.get_speed(), 500);
  EXPECT_EQ(snake.get_currAction(), None);
  EXPECT_EQ(snake.get_state(), Begin);
  s21::Coordinate apple = snake.get_apple();
  for (const auto &i : snake.get_snake()) {
    EXPECT_FALSE(apple.eq_coordinate(i));
  }
  auto &coord = snake.get_snake();
  EXPECT_EQ(coord.size(), 4);
  EXPECT_EQ(coord.front().x, 18);
  EXPECT_EQ(coord.front().y, 5);

  snake.set_state(Generation);
  snake.update();
  apple = snake.get_apple();
  for (const auto &i : snake.get_snake()) {
    EXPECT_FALSE(apple.eq_coordinate(i));
  }
  EXPECT_GE(apple.x, 0);
  EXPECT_LT(apple.x, ROWS_BOARD);
  EXPECT_GE(apple.y, 0);
  EXPECT_LT(apple.y, COL_BOARD);
  EXPECT_EQ(snake.get_state(), Falling);

  snake.set_state(Falling);
  snake.change_direction(Right);
  sleep(1);
  std::list<s21::Coordinate> check_snake = snake.get_snake();
  s21::Coordinate head_before = check_snake.back();
  snake.update();
  check_snake = snake.get_snake();
  s21::Coordinate head_after = check_snake.back();
  EXPECT_EQ(head_after.y, head_before.y + 1);
  EXPECT_EQ(head_after.x, head_before.x);

  snake.change_direction(Right);
  check_snake = snake.get_snake();
  head_before = check_snake.back();
  sleep(1);
  snake.check_move_snake();
  check_snake = snake.get_snake();
  head_after = check_snake.back();
  EXPECT_EQ(head_after.y, head_before.y + 1);
  EXPECT_EQ(head_after.x, head_before.x);

  snake.set_state(Moving_rotate);
  snake.change_direction(Right);
  snake.update();
  EXPECT_EQ(snake.get_state(), Falling);

  snake.set_state(Attaching);
  snake.update();
  EXPECT_EQ(snake.get_level(), 1);
  EXPECT_EQ(snake.get_state(), Generation);
}

TEST(ModelSnakeGameTest, SaveHighScore) {
  s21::SnakeGame snake;
  snake.save_high_score();
  std::ifstream inputFile("highscore_snake.txt");
  int check_h_score;
  if (inputFile.is_open()) {
    inputFile >> check_h_score;
    inputFile.close();
  }
  EXPECT_EQ(check_h_score, 0);
}

TEST(ModelSnakeGameTest, IncreaseLevel) {
  TestSnake snake;
  snake.set_currAction(None);
  for (int score = 0; score < LEVEL_NEXT_SNAKE; score += 1) {
    snake.set_score(score);
    snake.increase_level();
    EXPECT_EQ(snake.get_level(), 1);
    EXPECT_EQ(snake.get_speed(), 500);
  }

  snake.set_score(LEVEL_NEXT_SNAKE);
  snake.increase_level();
  EXPECT_EQ(snake.get_level(), 2);
  EXPECT_EQ(snake.get_speed(), 450);

  snake.set_score(LEVEL_NEXT_SNAKE * 2);
  snake.increase_level();
  EXPECT_EQ(snake.get_level(), 3);
  EXPECT_EQ(snake.get_speed(), 400);

  snake.set_score(LEVEL_NEXT_SNAKE * (MAX_LEVEL - 1));
  snake.increase_level();
  EXPECT_EQ(snake.get_level(), MAX_LEVEL);
  EXPECT_EQ(snake.get_speed(), 50);

  snake.set_score(LEVEL_NEXT_SNAKE * MAX_LEVEL);
  snake.increase_level();
  EXPECT_EQ(snake.get_level(), MAX_LEVEL);
  EXPECT_EQ(snake.get_speed(), 50);
}

TEST(ControllSnakeGameTest, ConvertSnake) {
  s21::Controller controller;
  std::list<s21::Coordinate> snake = {{0, 0}, {1, 0}, {1, 0}};
  int **arr = controller.convert_snake_to_array(snake);

  ASSERT_EQ(arr[0][0], 0);
  ASSERT_EQ(arr[0][1], 0);
  ASSERT_EQ(arr[0][2], 0);
  ASSERT_EQ(arr[1][0], 1);
  ASSERT_EQ(arr[1][1], 0);
  ASSERT_EQ(arr[1][2], 0);
  ASSERT_EQ(arr[2][0], 1);
  ASSERT_EQ(arr[2][1], 0);
  ASSERT_EQ(arr[2][2], 0);
  ASSERT_EQ(arr[3][0], -1);
  ASSERT_EQ(arr[3][1], -1);
  ASSERT_EQ(arr[3][2], -1);

  controller.free_array(arr);
}

TEST(ControllSnakeGameTest, ConvertAppleToArray) {
  s21::Controller controller;
  s21::Coordinate apple = {1, 1};
  int **arr = controller.convert_apple_to_array(apple);

  ASSERT_EQ(arr[0][0], 1);
  ASSERT_EQ(arr[0][1], 1);
  ASSERT_EQ(arr[0][2], 7);
  ASSERT_EQ(arr[1][0], -1);
  ASSERT_EQ(arr[1][1], -1);
  ASSERT_EQ(arr[1][2], -1);

  controller.free_array(arr);
}

TEST(ControllSnakeGameTest, UpdateCurrentState) {
  s21::Controller controller;
  GameInfo_t info = controller.updateCurrentState();

  ASSERT_EQ(info.score, 0);
  ASSERT_EQ(info.high_score, 0);
  ASSERT_EQ(info.speed, 500);
  ASSERT_EQ(info.level, 1);

  int **snakeArray = info.next;
  int **appleArray = info.field;
  ASSERT_EQ(snakeArray[0][0], 18);
  ASSERT_EQ(snakeArray[0][1], 5);
  ASSERT_EQ(snakeArray[0][2], 0);
  ASSERT_EQ(snakeArray[1][0], 17);
  ASSERT_EQ(snakeArray[1][1], 5);
  ASSERT_EQ(snakeArray[1][2], 0);
  ASSERT_EQ(snakeArray[2][0], 16);
  ASSERT_EQ(snakeArray[2][1], 5);
  ASSERT_EQ(snakeArray[2][2], 0);
  ASSERT_EQ(snakeArray[3][0], 15);
  ASSERT_EQ(snakeArray[3][1], 5);
  ASSERT_EQ(snakeArray[3][2], 0);
  ASSERT_EQ(snakeArray[4][0], -1);
  ASSERT_EQ(snakeArray[4][1], -1);
  ASSERT_EQ(snakeArray[4][2], -1);

  ASSERT_NE(appleArray, nullptr);

  controller.clearGameInfo(info);
}

TEST(ControllSnakeGameTest, UserInput) {
  s21::Controller controller;
  controller.userInput(Start, false);
  ASSERT_EQ(controller.get_model()->get_state(), Generation);

  controller.get_model()->set_state(Falling);
  controller.userInput(Pause, false);
  ASSERT_EQ(controller.get_model()->get_state(), Break);

  controller.get_model()->set_state(Falling);
  controller.userInput(Left, false);
  ASSERT_EQ(controller.get_model()->get_state(), Moving_rotate);
  ASSERT_EQ(controller.get_model()->get_currAction(), Left);

  controller.get_model()->set_state(Falling);
  controller.userInput(Terminate, false);
  ASSERT_EQ(controller.get_model()->get_state(), End);

  controller.get_model()->set_state(Break);
  controller.userInput(Pause, false);
  ASSERT_EQ(controller.get_model()->get_state(), Falling);

  controller.get_model()->set_state(Break);
  controller.userInput(Terminate, false);
  ASSERT_EQ(controller.get_model()->get_state(), End);

  controller.get_model()->set_state(End);
  controller.userInput(Start, false);
  ASSERT_EQ(controller.get_model()->get_state(), Begin);

  controller.get_model()->set_state(End);
  controller.userInput(Terminate, false);
  ASSERT_EQ(controller.get_model()->get_state(), Exit);

  controller.get_model()->set_state(Falling);
  s21::Coordinate headPos = controller.get_model()->snake_head_new_pos();
  controller.userInput(Left, true);
  s21::Coordinate newHeadPos = controller.get_model()->snake_head_new_pos();
  EXPECT_EQ(newHeadPos.x, headPos.x - 1);
  EXPECT_EQ(newHeadPos.y, headPos.y);
}

TEST(ControllSnakeGameTest, GetModel) {
  s21::Controller controller;
  s21::SnakeGame *model = controller.get_model();
  ASSERT_NE(model, nullptr);
}