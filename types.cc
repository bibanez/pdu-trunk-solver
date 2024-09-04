#include "types.h"
using namespace std;

std::pair<int, int> shape(const Matrix &matrix) {
  return {matrix.size(), matrix[0].size()};
}

vector<int> horizontal_edges(const Matrix &matrix) {
  auto [n, m] = shape(matrix);
  vector<int> edges;

  for (int j = 0; j < m; ++j) {
    int i = 0;
    bool found = false;
    while (i < n and not found) {
      if (j == 0)
        found = (matrix[i][j] != 0);
      else
        found = (matrix[i][j] != 0 and matrix[i][j - 1] == 0) or
                (matrix[i][j] == 0 and matrix[i][j - 1] != 0);
      ++i;
    }
    if (found)
      edges.push_back(j);
  }

  int i = 0;
  while (i < n and matrix[i][m - 1] == 0)
    ++i;
  if (i < n)
    edges.push_back(m);

  return edges;
}

vector<int> vertical_edges(const Matrix &matrix) {
  auto [n, m] = shape(matrix);
  vector<int> edges;

  for (int i = 0; i < n; ++i) {
    int j = 0;
    bool found = false;
    while (j < m and not found) {
      if (i == 0)
        found = (matrix[i][j] != 0);
      else
        found = (matrix[i][j] != 0 and matrix[i - 1][j] == 0) or
                (matrix[i][j] == 0 and matrix[i - 1][j] != 0);
      ++j;
    }
    if (found)
      edges.push_back(i);
  }

  int j = 0;
  while (j < m and matrix[n - 1][j] == 0)
    ++j;
  if (j < m)
    edges.push_back(n);

  return edges;
}

int rectangle_sum(const Matrix &matrix, const Rectangle &r) {
  int sum = 0;
  for (int i = r.l; i < r.r; ++i)
    for (int j = r.b; j < r.t; ++j)
      sum += matrix[i][j];
  return sum;
}

HananGrid::HananGrid(const Matrix &matrix) {
  _original_width = matrix.size();
  _original_height = matrix[0].size();
  _x_coordinates = vertical_edges(matrix);
  _y_coordinates = horizontal_edges(matrix);
  _width = _x_coordinates.size() - 1;
  _height = _y_coordinates.size() - 1;

  _mat_accumulation = Matrix(_width, Row(_height));
  for (int i = 0; i < _width; ++i)
    for (int j = 0; j < _height; ++j)
      _mat_accumulation[i][j] =
          rectangle_sum(matrix, from_hanan({i, i + 1, j, j + 1}));
}

Matrix HananGrid::get_accumulation() { return _mat_accumulation; }

Rectangle HananGrid::from_hanan(const Rectangle &r) {
  return {_x_coordinates[r.l], _x_coordinates[r.r], _y_coordinates[r.b],
          _y_coordinates[r.t]};
}