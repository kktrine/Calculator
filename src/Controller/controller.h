#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/model_calculator.h"
#include "../Model/model_credit.h"
using namespace s21;
class Controller {
 public:
  Controller(){};
  string GetCalculationResult(std::string expr_arg, std::string x_arg);
  void GetCreditResult(string sum, string period, string percent, string& total,
                       string& monthly, string& over, int type);
  bool GetGraphResult(string expr, string x_min, string x_max,
                      vector<double>& x, vector<double>& y);
  ~Controller(){};
};

inline string Controller::GetCalculationResult(string expr, string x) {
  string res;
  ModelCalculator obj(expr, x);
  try {
    res = std::to_string(obj.Process());
  } catch (...) {
    res = "ERROR! ";
  }
  return res;
}

inline void Controller::GetCreditResult(string sum, string period,
                                        string percent, string& total,
                                        string& monthly, string& over,
                                        int type) {
  if (sum.length() && period.length() && percent.length()) {
    ModelCredit credit(sum, period, percent);
    if (type == 1) {
      credit.annyity_payment(monthly, over, total);
    } else {
      credit.diff_payment(monthly, over, total);
    }
  }
}

inline bool Controller::GetGraphResult(string expr, string x_min, string x_max,
                                       vector<double>& x, vector<double>& y) {
  bool res = true;
  try {
    ModelCalculator graph(expr, "1");
    graph.CountPointsForGraph(x_min, x_max, x, y);
  } catch (...) {
    res = false;
  }
  return res;
}

#endif  // CONTROLLER_H
