#pragma once

#include <QMainWindow>
#include <QPainter>
#include <QWidget>

/**
 * @def SIZE_RECT
 * @brief размер одного пикселя
 */
#define SIZE_RECT 30
namespace s21 {
/**
 * @class CommonDraw
 * @brief класс для работы с рисованием в приложении на основе Qt (общая
 * отрисовка для змейки и тетриса)
 */
class CommonDraw : public QWidget {
 public:
  /**
   * @brief конструктор класса CommonDraw
   * @param w указатель на родительское окно QMainWindow
   */
  explicit CommonDraw(QMainWindow *w) : parent{w} {};
  /**
   * @brief деструктор класса CommonDraw по умолчаниюф
   */
  ~CommonDraw() = default;

  /**
   * @brief настройка окна для рисования
   */
  void setup_window();
  /**
   * @brief настройка объекта QPainter для рисования
   * @param p ссылка на объект QPainter
   */
  void setup_painter(QPainter &p);

  /**
   * @brief отрисовка двумерного массива
   * @param arr указатель на массив
   * @param p ссылка на объект QPainter для рисования
   * @param color цвет, которым будет рисоваться массив
   */
  void draw_arr(int **arr, QPainter &p, const QColor &color);

  /**
   * @brief отрисовка игрового поля
   * @param p ссылка на объект QPainter для рисования
   */
  void draw_board(QPainter &p);
  /**
   * @brief отрисовка состояния "Начало игры"
   * @param p ссылка на объект QPainter для рисования
   */
  void draw_start(QPainter &p);
  /**
   * @brief отрисовка состояния "Пауза"
   * @param p ссылка на объект QPainter для рисования
   */
  void draw_pause(QPainter &p);
  /**
   * @brief отрисовка состояния "Игра окончена"
   * @param p ссылка на объект QPainter для рисования
   */
  void draw_gameover(QPainter &p);

  /**
   * @brief отрисовка баннера со статистикой игры
   * @param p ссылка на объект QPainter для рисования
   * @param level уровень игры
   * @param speed скорость игры
   * @param score количество очков
   * @param h_score количество рекордных очков
   */
  void draw_banner_stat(QPainter &p, int level, int speed, int score,
                        int h_score);

 protected:
  QMainWindow *parent; /**< указатель на родительское окно */
};
}  // namespace s21
