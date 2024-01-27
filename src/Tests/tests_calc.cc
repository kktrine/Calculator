#include <gtest/gtest.h>

#include "../Model/model_calculator.h"
#define EPS 1e-7
using namespace s21;

TEST(EXCEPTIONS, without_parameters) {
  ModelCalculator test("", "");
  ASSERT_THROW(test.Process(), std::invalid_argument);
}

TEST(EXCEPTIONS, too_long_string) {
  std::string expr;
  for (int i = 0; i < 258; i += 2) {
    expr.append("2+");
  }
  ModelCalculator test(expr, "");
  ASSERT_THROW(test.Process(), std::out_of_range);
}

TEST(EXCEPTIONS, wrong_input) {
  std::string expr = "1++2";
  ModelCalculator test(expr, "");
  ASSERT_THROW(test.Process(), std::logic_error);
}

TEST(EXCEPTIONS, wrong_input_2) {
  std::string expr = "sin(+-+)";
  ModelCalculator test(expr, "");
  ASSERT_THROW(test.Process(), std::logic_error);
}

TEST(EXCEPTIONS, wrong_input_3) {
  std::string expr = "sin(cos())";
  ModelCalculator test(expr, "");
  ASSERT_THROW(test.Process(), std::logic_error);
}

TEST(COMMON_TEST, trigonometric) {
  std::string expr = "sin(cos(tan(2+3^6)))";
  double answer = sin(cos(tan(2 + pow(3, 6))));
  ModelCalculator test(expr, "");
  ASSERT_NEAR(test.Process(), answer, EPS);
}

TEST(COMMON_TEST, inf) {
  std::string expr = "1/0";
  // double answer = sin(cos(tan(2 + pow(3, 6))));
  ModelCalculator test(expr, "");
  ASSERT_EQ(isinf(test.Process()), 1);
}

TEST(COMMON_TEST, nan) {
  std::string expr = "ln(-1)";
  // double answer = sin(cos(tan(2 + pow(3, 6))));
  ModelCalculator test(expr, "");
  ASSERT_EQ(isnan(test.Process()), 1);
}

TEST(COMMON_TEST, ln) {
  std::string expr = "ln(1)";
  // double answer = sin(cos(tan(2 + pow(3, 6))));
  ModelCalculator test(expr, "");
  ASSERT_NEAR(test.Process(), 0., EPS);
}

TEST(COMMON_TEST, mod) {
  std::string expr = "2 mod 3";
  // double answer = sin(cos(tan(2 + pow(3, 6))));
  ModelCalculator test(expr, "");
  ASSERT_NEAR(test.Process(), 2., EPS);
}

TEST(COMMON_TEST, log) {
  std::string expr = "log(-1*(sin(5) ^ 2 * cos(2) - 1))";
  double answer = log10(-(pow(sin(5), 2) * cos(2) - 1));
  ModelCalculator test(expr, "");
  ASSERT_NEAR(test.Process(), answer, EPS);
}

TEST(COMMON_TEST, cos_sin_x) {
  std::string expr = "(1+2)*4*cos(x*7-2)+sin(x*2)";
  std::string x = "2";
  double answer = (1 + 2) * 4 * cos(2 * 7 - 2) + sin(2 * 2);
  ModelCalculator test(expr, x);
  ASSERT_NEAR(test.Process(), answer, EPS);
}

TEST(COMMON_TEST, long_expr) {
  std::string expr =
      "tan( 3.764) ^sin( 9.445-sin( 7.2889 /  8.0438 -cos( sin(cos( "
      "tan(8.4448))) - 4.482)  )  / tan(cos(cos(sin(cos( "
      "cos(2.003)) )  ) / 0.1315) ))  -  8.8453/ 0.3612";
  std::string x = "2";
  double answer = -23.76667454586336;
  ModelCalculator test(expr, x);
  ASSERT_NEAR(test.Process(), answer, EPS);
}

TEST(COMMON_TEST, atan_sin) {
  std::string expr = "atan( 3.764) ^ sin(3)";
  std::string x = "2";
  double answer = pow(atan(3.764), sin(3));
  ModelCalculator test(expr, x);
  ASSERT_NEAR(test.Process(), answer, EPS);
}

TEST(COMMON_TEST, sqrt) {
  std::string expr = "sqrt(atan( 3.764) ^ sin(3))";
  std::string x = "2";
  double answer = sqrt(pow(atan(3.764), sin(3)));
  ModelCalculator test(expr, x);
  ASSERT_NEAR(test.Process(), answer, EPS);
}

TEST(COMMON_TEST, asin_acos) {
  std::string expr = "asin(acos(x)-1)";
  std::string x = "0.25";
  double answer = asin(acos(0.25) - 1);
  ModelCalculator test(expr, x);
  ASSERT_NEAR(test.Process(), answer, EPS);
}

TEST(Exp, common_test) {
  std::string expr = "1e5";
  std::string x = "";
  double answer = 1e5;
  ModelCalculator test(expr, x);
  ASSERT_NEAR(test.Process(), answer, EPS);
}

TEST(Exp, common_test_2) {
  std::string expr = "1e(-7) + 25 -75.4";
  std::string x = "";
  double answer = 1e-7 + 25 - 75.4;
  ModelCalculator test(expr, x);
  ASSERT_NEAR(test.Process(), answer, EPS);
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
