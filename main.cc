#include <iostream>
#include <vector>
using namespace std;

template <typename T> using Row = vector<T>;
template <typename T> using Matrix = Row<Row<T>>;

template <typename T> pair<int, int> shape(const Matrix<T> &matrix) {
  return {matrix.size(), matrix[0].size()};
}

vector<int> horizontal_edges(const Matrix<int> &matrix) {
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

vector<int> vertical_edges(const Matrix<int> &matrix) {
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

int main() {
  int n, m;
  cin >> n >> m;
  Matrix<int> matrix(n, Row<int>(m));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      cin >> matrix[i][j];
  vector<int> h_edges = horizontal_edges(matrix);
  cout << h_edges.size() << endl;
  for (int x : h_edges)
    cout << x << ' ';
  cout << endl;
  vector<int> v_edges = vertical_edges(matrix);
  cout << v_edges.size() << endl;
  for (int y : v_edges)
    cout << y << ' ';
  cout << endl;
}
