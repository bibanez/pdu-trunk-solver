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

int main() {
  int n, m;
  cin >> n >> m;
  Matrix matrix(n, Row(m));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> matrix[i][j];

  HananGrid grid(matrix);
  print_matrix(grid.get_accumulation());
  print_matrix(grid.get_areas());

  auto [res, rect] = calculate_trunk(grid, 0.2);
  if (res) {
    cout << rect.l << ' ' << rect.r << ' ' << rect.b << ' ' << rect.t << endl;
  } else {
    cout << "Could not solve" << endl;
  }
}
