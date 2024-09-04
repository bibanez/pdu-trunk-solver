#include "types.h"
#include <iostream>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  Matrix matrix(n, Row(m));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> matrix[i][j];

  HananGrid grid(matrix);
  Matrix mat_acc = grid.get_accumulation();
  auto [width, height] = shape(mat_acc);
  for (int i = 0; i < width; ++i) {
    cout << mat_acc[i][0];
    for (int j = 1; j < height; ++j) {
      cout << ' ' << mat_acc[i][j];
    }
    cout << endl;
  }
}
