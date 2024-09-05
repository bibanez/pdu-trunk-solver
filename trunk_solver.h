#ifndef TRUNK_SOLVER_H
#define TRUNK_SOLVER_H

#include "types.h"

std::pair<bool, Rectangle> calculate_trunk(const HananGrid &grid, double epsilon = 0.2);

#endif
