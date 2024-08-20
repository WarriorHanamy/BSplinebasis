/*
 * ########################################################################
 * The contents of this file is free and unencumbered software released into the
 * public domain. For more information, please refer to <http://unlicense.org/>
 * ########################################################################
 */

#include <bspline/Core.h>

#include <fstream>
#include <iostream>
#include <limits>
#include <rclcpp/rclcpp.hpp>
#include <vector>

int main(int argc, char **argv) {
  static constexpr size_t SPLINE_DEGREE = 1;
  using Spline = bspline::Spline<double, SPLINE_DEGREE>;

  // Define knots vector.
  const std::vector<double> knots{0.0, 0.0, 1.0, 2.0, 3.0, 4.0, 5.0};

  // Generate Splines.
  const std::vector<Spline> spl =
      bspline::generateBSplines<SPLINE_DEGREE>(knots);
  std::ofstream out("diffusion.csv");
  out.precision(std::numeric_limits<double>::max_digits10);

  for (double x = -1.0; x <= 6.0; x += 0.01) {
    out << x << ",";
    for (auto &s : spl) {
      if (s == spl.back()) {
        out << s(x) << "\n";
      } else {
        out << s(x) << ",";
      }
    }
    // for (data_t x = static_cast<data_t>(-10); x <= static_cast<data_t>(10);
    //      x += static_cast<data_t>(1) / 100) {
    //   out << x << "\t" << diffCoeff(x) << "\t" << solution(x) << "\n";
    // }
  }
}