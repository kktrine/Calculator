#ifndef MODEL_CREDIT_H
#define MODEL_CREDIT_H

#include <clocale>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
namespace s21 {
class ModelCredit {
 public:
  ModelCredit(string sum_arg, string period_arg, string percent_arg) {
    std::setlocale(LC_ALL, "en_US.UTF-8");
    sum_ = stod(sum_arg);
    period_ = stoi(period_arg);
    percent_ = stod(percent_arg);
  };
  ~ModelCredit(){};
  void annyity_payment(string& monthly_payment, string& overpayment,
                       string& total);
  void diff_payment(string& monthly_payment, string& overpayment,
                    string& total);

 private:
  double sum_, percent_;
  size_t period_;
};

inline void ModelCredit::annyity_payment(string& monthly_payment,
                                         string& overpayment, string& total) {
  double percent_per_month = percent_ / 12. / 100;
  double coeff = (percent_per_month * pow(1. + percent_per_month, period_)) /
                 (pow(1. + percent_per_month, period_) - 1.);
  double month = sum_ * coeff, total_payment = period_ * month;
  double over = total_payment - sum_;

  month = round(month * 10) / 10;
  total_payment = round(total_payment * 10) / 10;
  over = round(over * 10) / 10;

  monthly_payment = to_string(month);
  total = to_string(total_payment);
  overpayment = to_string(over);
}

inline void ModelCredit::diff_payment(string& monthly_payment,
                                      string& overpayment, string& total) {
  double fix = sum_ / period_;
  double max_payment = fix + sum_ * percent_ / 100. / 12,
         min_payment = fix + fix * percent_ / 100. / 12;
  double rest = sum_;
  double total_payment = 0., current_payment = 0., over = 0.;
  for (size_t i = 0; i < period_; ++i) {
    current_payment = fix + rest * percent_ / 100. / 12.;
    total_payment += current_payment;
    rest -= fix;
  }

  max_payment = round(max_payment * 100) / 100;
  min_payment = round(min_payment * 100) / 100;
  over = round((total_payment - sum_) * 100) / 100;
  total_payment = round(total_payment * 100) / 100;

  monthly_payment = to_string(max_payment) + " ... " + to_string(min_payment);
  overpayment = to_string(over);
  total = to_string(total_payment);
}
}  // namespace s21
#endif  // MODEL_CREDIT_H
