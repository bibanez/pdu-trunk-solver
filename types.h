#ifndef TYPES_H
#define TYPES_H

#include <vector>

struct Rectangle {
  int l, r, b, t;
};

using Row = std::vector<int>;
using Matrix = std::vector<Row>;

std::pair<int, int> shape(const Matrix &matrix);

class HananGrid {
  int _width, _height;
  int _original_width, _original_height;
  Row _x_coordinates, _y_coordinates;
  Matrix _mat_accumulation;

public:

  HananGrid(const Matrix &matrix);

  Matrix get_accumulation();

  /**
   * Pre: Rectangle coordinates are inside the hanan grid.
   * Post: Returns a rectangle with the coordinates in the original grid
   **/
  Rectangle from_hanan(const Rectangle &r);
};

#endif
