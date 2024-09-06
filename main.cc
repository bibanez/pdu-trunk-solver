#include "trunk_solver.h"
#include "types.h"
#include <iostream>
using namespace std;

void print_matrix(const Matrix &matrix) {
  auto [n, m] = shape(matrix);
  for (int i = 0; i < n; ++i) {
    cout << matrix[i][0];
    for (int j = 1; j < m; ++j)
      cout << ' ' << matrix[i][j];
    cout << endl;
  }
  cout << endl;
}

void print_rectangle(const Rectangle &r, int width, int height) {
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < height; ++j) {
      if (i >= r.l and i < r.r and j >= r.b and j < r.t)
        cout << "1 ";
      else
        cout << "0 ";
    }
    cout << endl;
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  Matrix matrix(n, Row(m));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> matrix[i][j];

  cout << "Original matrix:" << endl;
  print_matrix(matrix);

  HananGrid grid(matrix);
  cout << "Hanan grid accumulation:" << endl;
  print_matrix(grid.get_accumulation());
  cout << "Hanan grid areas:" << endl;
  print_matrix(grid.get_areas());

  auto [res, rect] = calculate_trunk(grid, 0.05);
  if (res) {
    cout << "Trunk:" << endl;
    print_rectangle(rect, n, m);
  } else {
    cout << "Could not solve" << endl;
  }
}
