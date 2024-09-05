#ifndef TYPES_H
#define TYPES_H

#include <vector>

struct Rectangle {
  int l, r, b, t;

  int area() const;
  bool operator==(const Rectangle &other) const;
  bool operator<(const Rectangle &other) const;
};

// Specialize std::hash for Rectangle
template <> struct std::hash<Rectangle> {
  size_t operator()(const Rectangle &rect) const {
    size_t h1 = hash<int>()(rect.l);
    size_t h2 = hash<int>()(rect.r);
    size_t h3 = hash<int>()(rect.b);
    size_t h4 = hash<int>()(rect.t);

    // Combine the individual hashes into a single hash value
    return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
  }
};

using Row = std::vector<int>;
using Matrix = std::vector<Row>;

std::pair<int, int> shape(const Matrix &matrix);

class HananGrid {
  int _width, _height;
  int _original_width, _original_height;
  int _grid_area, _grid_selected;
  Row _x_coordinates, _y_coordinates;
  Matrix _mat_accumulation, _mat_areas;

public:
  HananGrid(const Matrix &matrix);

  Matrix get_accumulation() const;

  Matrix get_areas() const;

  int get_area() const;

  int get_selected_area() const;

  /**
   * Pre: Rectangle coordinates are inside the hanan grid.
   * Post: Returns a rectangle with the coordinates in the original grid
   **/
  Rectangle from_hanan(const Rectangle &r) const;
};

#endif
