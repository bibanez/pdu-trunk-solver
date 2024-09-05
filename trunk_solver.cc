#include "trunk_solver.h"
#include "types.h"
#include <queue>
#include <unordered_set>
using namespace std;

struct QueueElem {
  int selected_inside;
  int selected_corners;
  int rect_area;
  Rectangle rect;

  bool operator<(const QueueElem &other) const {
    if (selected_corners == other.selected_corners) {
      if (selected_inside == other.selected_inside)
        return rect_area > other.rect_area;
      else
        return selected_inside > other.selected_inside;
    } else
      return selected_corners < other.selected_corners;
  }

  bool operator==(const QueueElem &other) const {
    return selected_corners == other.selected_corners and
           selected_inside == other.selected_inside and
           rect_area == other.rect_area;
  }

  bool operator<=(const QueueElem &other) const {
    return *this < other or *this == other;
  }
};

Matrix horizontal_sum(const Matrix &matrix) {
  auto [n, m] = shape(matrix);
  Matrix res(matrix);
  for (int i = 1; i < n; ++i)
    for (int j = 0; j < m; ++j)
      res[i][j] += res[i - 1][j];
  return res;
}

Matrix vertical_sum(const Matrix &matrix) {
  auto [n, m] = shape(matrix);
  Matrix res(matrix);
  for (int i = 0; i < n; ++i)
    for (int j = 1; j < m; ++j)
      res[i][j] += res[i][j - 1];
  return res;
}

vector<QueueElem> generate_queue_elements(const QueueElem &e,
                                          const Matrix &hsum,
                                          const Matrix &vsum,
                                          const Matrix &hareasum,
                                          const Matrix &vareasum) {
  auto [n, m] = shape(hsum);
  vector<QueueElem> res;

  // Left edge
  {
    Rectangle r = {e.rect.l + 1, e.rect.r, e.rect.b, e.rect.t};
    if (r.l < r.r) {
      int selected_inside = e.selected_inside;
      int selected_corners = e.selected_corners;
      int rect_area = e.rect_area;
      if (e.rect.b == 0) {
        selected_corners +=
            vsum[e.rect.l][m - 1] - vsum[e.rect.l][e.rect.t - 1];
        selected_inside -= vsum[e.rect.l][e.rect.t - 1];
        rect_area -= vareasum[e.rect.l][e.rect.t - 1];
      } else {
        selected_corners +=
            (vsum[e.rect.l][m - 1] - vsum[e.rect.l][e.rect.t - 1]) +
            vsum[e.rect.l][e.rect.b - 1];
        selected_inside -=
            vsum[e.rect.l][e.rect.t - 1] - vsum[e.rect.l][e.rect.b - 1];
        rect_area -=
            vareasum[e.rect.l][e.rect.t - 1] - vareasum[e.rect.l][e.rect.b - 1];
      }
      res.push_back({selected_inside, selected_corners, rect_area, r});
    }
  }

  // Right edge
  {
    Rectangle r = {e.rect.l, e.rect.r - 1, e.rect.b, e.rect.t};
    if (r.l < r.r) {
      int selected_inside = e.selected_inside;
      int selected_corners = e.selected_corners;
      int rect_area = e.rect_area;
      if (e.rect.b == 0) {
        selected_corners +=
            vsum[e.rect.r - 1][m - 1] - vsum[e.rect.r - 1][e.rect.t - 1];
        selected_inside -= vsum[e.rect.r - 1][e.rect.t - 1];
        rect_area -= vareasum[e.rect.r - 1][e.rect.t - 1];
      } else {
        selected_corners +=
            (vsum[e.rect.r - 1][m - 1] - vsum[e.rect.r - 1][e.rect.t - 1]) +
            vsum[e.rect.r - 1][e.rect.b - 1];
        selected_inside -=
            vsum[e.rect.r - 1][e.rect.t - 1] - vsum[e.rect.r - 1][e.rect.b - 1];
        rect_area -= vareasum[e.rect.r - 1][e.rect.t - 1] -
                     vareasum[e.rect.r - 1][e.rect.b - 1];
      }
      res.push_back({selected_inside, selected_corners, rect_area, r});
    }
  }

  // Bottom edge
  {
    Rectangle r = {e.rect.l, e.rect.r, e.rect.b + 1, e.rect.t};
    if (r.b < r.t) {
      int selected_inside = e.selected_inside;
      int selected_corners = e.selected_corners;
      int rect_area = e.rect_area;
      if (e.rect.l == 0) {
        selected_corners +=
            hsum[n - 1][e.rect.b] - hsum[e.rect.r - 1][e.rect.b];
        selected_inside -= hsum[e.rect.r - 1][e.rect.b];
        rect_area -= hareasum[e.rect.r - 1][e.rect.b];
      } else {
        selected_corners +=
            (hsum[n - 1][e.rect.b] - hsum[e.rect.r - 1][e.rect.b]) +
            hsum[e.rect.l - 1][e.rect.b];
        selected_inside -=
            hsum[e.rect.r - 1][e.rect.b] - hsum[e.rect.l - 1][e.rect.b];
        rect_area -=
            hareasum[e.rect.r - 1][e.rect.b] - hareasum[e.rect.l - 1][e.rect.b];
      }
      res.push_back({selected_inside, selected_corners, rect_area, r});
    }
  }

  // Top edge
  {
    Rectangle r = {e.rect.l, e.rect.r, e.rect.b, e.rect.t - 1};
    if (r.b < r.t) {
      int selected_inside = e.selected_inside;
      int selected_corners = e.selected_corners;
      int rect_area = e.rect_area;
      if (e.rect.l == 0) {
        selected_corners +=
            hsum[n - 1][e.rect.t - 1] - hsum[e.rect.r - 1][e.rect.t - 1];
        selected_inside -= hsum[e.rect.r - 1][e.rect.t - 1];
        rect_area -= hareasum[e.rect.r - 1][e.rect.t - 1];
      } else {
        selected_corners +=
            (hsum[n - 1][e.rect.t - 1] - hsum[e.rect.r - 1][e.rect.t - 1]) +
            hsum[e.rect.l - 1][e.rect.t - 1];
        selected_inside -=
            hsum[e.rect.r - 1][e.rect.t - 1] - hsum[e.rect.l - 1][e.rect.t - 1];
        rect_area -= hareasum[e.rect.r - 1][e.rect.t - 1] -
                     hareasum[e.rect.l - 1][e.rect.t - 1];
      }
      res.push_back({selected_inside, selected_corners, rect_area, r});
    }
  }

  return res;
}

pair<bool, Rectangle> calculate_trunk(const HananGrid &grid, double epsilon) {
  Matrix matrix = grid.get_accumulation(), areas = grid.get_areas();

  auto [n, m] = shape(matrix);
  Matrix hsum = horizontal_sum(matrix), vsum = vertical_sum(matrix);
  Matrix hareasum = horizontal_sum(areas), vareasum = vertical_sum(areas);

  unordered_set<Rectangle> visited;
  queue<QueueElem> q;

  // {selected_inside, selected_corners, rect_area, rect}
  q.push({grid.get_selected_area(), 0, grid.get_area(), {0, n, 0, m}});

  QueueElem trunk;
  bool found_suitable = false;
  // Main loop
  while (not q.empty()) {
    QueueElem e = q.front();
    q.pop();

    // Prevent this rectangle from being visited again
    visited.insert(e.rect);

    if (found_suitable and e.selected_corners > trunk.selected_corners)
      continue;

    if ((not found_suitable or e < trunk) and
        (double)(e.rect_area - e.selected_inside) / e.rect_area <= epsilon) {
      trunk = e;
      if (not found_suitable) found_suitable = true;
    }

    vector<QueueElem> v =
        generate_queue_elements(e, hsum, vsum, hareasum, vareasum);
    for (const QueueElem &elem : v) {
      if (visited.find(elem.rect) == visited.end() and
          (not found_suitable or elem <= trunk)) {
        q.push(elem);
      }
    }
  }

  if (found_suitable)
    return {true, grid.from_hanan(trunk.rect)};
  else
    return {false, Rectangle()};
}
