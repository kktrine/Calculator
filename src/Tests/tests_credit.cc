#include <gtest/gtest.h>

#include "../Model/model_credit.h"
using namespace std;
using namespace s21;
TEST(COMMON_TEST_1, annyity) {
  ModelCredit test("150000", "15", "10.1");
  string monthly_payment = "", overpayment = "0", total = "0";
  test.annyity_payment(monthly_payment, overpayment, total);
  EXPECT_TRUE(monthly_payment == to_string(10686.50));
  EXPECT_TRUE(total == to_string(160297.50));
  EXPECT_TRUE(overpayment == to_string(10297.50));
}

TEST(COMMON_TEST_1, diff) {
  ModelCredit test("150000", "15", "10.1");
  string monthly_payment = "", overpayment = "0", total = "0";
  test.diff_payment(monthly_payment, overpayment, total);
  string monthly = to_string(11262.50) + " ... " + to_string(10084.17);
  EXPECT_TRUE(monthly_payment == monthly);
  EXPECT_TRUE(total == to_string(160100.0));
  EXPECT_TRUE(overpayment == to_string(10100.0));
}

TEST(COMMON_TEST_2, annyity) {
  ModelCredit test("300000", "1", "50");
  string monthly_payment = "", overpayment = "0", total = "0";
  test.annyity_payment(monthly_payment, overpayment, total);
  EXPECT_TRUE(monthly_payment == to_string(312500.0));
  EXPECT_TRUE(total == to_string(312500.0));
  EXPECT_TRUE(overpayment == to_string(12500.0));
}

TEST(COMMON_TEST_2, diff) {
  ModelCredit test("300000", "1", "50");
  string monthly_payment = "", overpayment = "0", total = "0";
  test.diff_payment(monthly_payment, overpayment, total);
  string monthly = to_string(312500.0) + " ... " + to_string(312500.0);
  EXPECT_TRUE(monthly_payment == monthly);
  EXPECT_TRUE(total == to_string(312500.0));
  EXPECT_TRUE(overpayment == to_string(12500.0));
}

int main() {
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
