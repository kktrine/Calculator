#ifndef MODEL_H
#define MODEL_H
#include <algorithm>
#include <clocale>
#include <cmath>
#include <iostream>
#include <regex>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;
namespace s21 {
class ModelCalculator {
 public:
  ModelCalculator() noexcept : str_(""), x_(""){};
  ModelCalculator(string arg_str, string arg_x) noexcept
      : str_(arg_str), x_(arg_x){};
  ~ModelCalculator() noexcept {}
  double Process() {
    Prepare();
    CheckInput();
    Parse();
    return Calculate();
  }
  void CountPointsForGraph(string x_min_arg, string x_max_arg,
                           vector<double>& x, vector<double>& y);

 private:
  stack<char> stk_;
  string str_;
  string polish_notation_ = "";
  string x_;
  void CheckInput() const;
  void Prepare();
  void Parse();
  double Calculate();

  void OperatorParser(size_t pos);
  void BracketParser();
  bool CheckUnary(size_t pos) const;

  double CalcOperator(double left, double right, char op);
  double CalcFun(double val, char fun);
  void CheckX(size_t pos) const {
    if (!(strchr(")+-^/M*", str_[pos + 1]) != NULL || str_[pos + 1] == '\0'))
      throw logic_error("");
  }
  bool IsFun(char sym) const noexcept {
    return (strchr("cstCSTqlL", sym) && sym);
  }
  bool IsNumOrX(char sym) const noexcept {
    return ((sym >= '0' && sym <= '9') || sym == 'x');
  }
  bool IsNum(char sym) const noexcept { return ((sym >= '0' && sym <= '9')); }
  bool IsOperator(char sym) const noexcept {
    return (strchr("+-*/^m~", sym) && sym);
  }
  size_t OperatorPriority(char op) const noexcept {
    size_t res = 0;
    if (op == '~') res = 2;
    if (IsFun(op))
      res = 4;
    else if ('^' == op)
      res = 3;
    else if (strchr("*/m", op))
      res = 2;
    else if (strchr("+-", op))
      res = 1;
    else if (strchr("(", op))
      res = 0;
    return res;
  }
};

inline void ModelCalculator::CountPointsForGraph(string x_min_arg,
                                                 string x_max_arg,
                                                 vector<double>& x,
                                                 vector<double>& y) {
  std::setlocale(LC_ALL, "en_US.UTF-8");
  double x_min = stod(x_min_arg), x_max = stod(x_max_arg);
  double step = (x_max - x_min) / 100., current_y = 0;
  if (x_max <= x_min) throw std::logic_error("Invalid x_min and x_max");
  Prepare();
  CheckInput();
  Parse();
  for (double i = x_min; i <= x_max; i += step) {
    x_ = to_string(i);
    x.push_back(i);
    current_y = Calculate();
    y.push_back(current_y);
  }
}

inline void ModelCalculator::CheckInput() const {
  size_t pos = 0;
  char sym = 0;
  if (str_.length() > 255) throw out_of_range("");
  if (str_.length() == 0) throw invalid_argument("Empty expression");
  if (count(str_.begin(), str_.end(), '(') !=
      count(str_.begin(), str_.end(), ')'))
    throw logic_error("Wrong number of branches");
  if (str_.find("x") != string::npos && x_.length() == 0)
    throw logic_error("X value is empty");
  if (count(x_.begin(), x_.end(), ')') + count(x_.begin(), x_.end(), ')') > 1 ||
      count(x_.begin(), x_.end(), '.') > 1)
    throw logic_error("Wrong walue for x");
  while (pos < str_.npos && str_[pos] != '\0') {
    sym = str_[pos];
    if (IsNum(sym)) {
      size_t end_pos = str_.find_first_not_of("0123456789.", pos);
      string num = str_.substr(pos, end_pos - pos);
      if (count(num.begin(), num.end(), '.') > 1)
        throw logic_error("Wrong number found: ");
      pos = end_pos;
    } else if (IsFun(sym)) {
      if (str_[pos + 1] != '(')
        throw logic_error("No brackets after operator ");
      ++pos;
    } else if (IsOperator(sym)) {
      if (sym != '~' && !IsNumOrX(str_[pos - 1]) && str_[pos - 1] != ')')
        throw logic_error("No left operand for operator ");
      ++pos;
    } else if (sym == 'x') {
      CheckX(pos);
      ++pos;
    } else if (sym == ')') {
      if (!IsNumOrX(str_[pos - 1]) && str_[pos - 1] != ')')
        throw logic_error("Wrong ) usage");
      ++pos;
    } else if (sym == '(' || sym == '\0') {
      ++pos;
    } else {
      throw logic_error("Incnown symbol ");
    }
  }
}

inline void ModelCalculator::Prepare() {
  size_t pos = str_.find('+');
  vector<string> functions = {"asin", "acos", "atan", "sin", "cos",
                              "tan",  "sqrt", "ln",   "log", "mod"};
  vector<string> letters = {"S", "C", "T", "s", "c", "t", "q", "l", "L", "m"};
  for (size_t i = 0; i < functions.size(); ++i) {
    str_ = regex_replace(str_, regex(functions[i]), letters[i]);
  }
  str_ = regex_replace(str_, regex("e"), "*10^");
  while (pos != string::npos) {
    if (CheckUnary(pos)) str_.erase(pos, 1);
    pos = str_.find('+', pos + 1);
  }
  pos = str_.find('-');
  while (pos != string::npos) {
    if (CheckUnary(pos)) str_[pos] = '~';
    pos = str_.find('-', pos + 1);
  }
  str_.erase(remove(str_.begin(), str_.end(), ' '), str_.end());
}

inline bool ModelCalculator::CheckUnary(size_t pos) const {
  bool res = 0;
  if (IsOperator(str_[pos + 1])) throw logic_error("");
  if (pos == 0)
    res = true;
  else if (str_[pos - 1] == '(' || str_[pos - 1] == 'e')
    res = true;
  return res;
}

inline void ModelCalculator::OperatorParser(size_t pos) {
  size_t stack_priority = -1;
  size_t sourse_priority = OperatorPriority(str_[pos]);
  bool is_left_op = strchr("*/+-", str_[pos]) != NULL;
  if (IsOperator(str_[pos + 1])) throw logic_error("");
  if (stk_.size() == 0) {
    stk_.push(str_[pos]);
  } else {
    stack_priority = OperatorPriority(stk_.top());
    while (stack_priority > sourse_priority ||
           (stack_priority == sourse_priority && is_left_op)) {
      polish_notation_.push_back(stk_.top());
      stk_.pop();
      polish_notation_.push_back(' ');
      if (stk_.size())
        stack_priority = OperatorPriority(stk_.top());
      else
        stack_priority = sourse_priority - 1;
    }
    stk_.push(str_[pos]);
  }
}

inline void ModelCalculator::BracketParser() {
  while (stk_.top() != '(' && stk_.size() > 0) {
    polish_notation_.push_back(stk_.top());
    stk_.pop();
    polish_notation_.push_back(' ');
  }
  if (stk_.empty()) {
    throw logic_error("");
  } else {
    stk_.pop();
    if (stk_.size()) {
      if (IsFun(stk_.top())) {
        polish_notation_.push_back(stk_.top());
        stk_.pop();
        polish_notation_.push_back(' ');
      }
    }
  }
}

inline void ModelCalculator::Parse() {
  size_t pos = 0;
  char sym = 0;
  while (pos < str_.npos && str_[pos]) {
    sym = str_[pos];
    if (IsNum(sym)) {
      size_t end_pos = str_.find_first_not_of("0123456789e.", pos);
      polish_notation_.append(str_.substr(pos, end_pos - pos));
      polish_notation_.push_back(' ');
      pos = end_pos;
    } else if (sym == 'x') {
      polish_notation_.append("x ");
      ++pos;
    } else if (IsOperator(sym) || IsFun(sym)) {
      OperatorParser(pos);
      ++pos;
    } else if (sym == '(') {
      stk_.push(sym);
      ++pos;
    } else if (sym == ')') {
      BracketParser();
      ++pos;
    }
  }
  while (stk_.size()) {
    if (stk_.top() == ')' || stk_.top() == '(') throw logic_error("");
    polish_notation_.push_back(stk_.top());
    polish_notation_.push_back(' ');
    stk_.pop();
  }
}

inline double ModelCalculator::Calculate() {
  std::setlocale(LC_ALL, "en_US.UTF-8");
  stack<double> numbers;
  size_t pos = 0;
  double res = 0., left = 0., right = 0.;
  char sym = 0;
  while (pos < polish_notation_.length() && !isinf(res)) {
    sym = polish_notation_[pos];
    if (IsNumOrX(sym)) {
      if (sym == 'x')
        numbers.push(stod(x_));
      else
        numbers.push(stod(&polish_notation_[pos]));

    } else if (sym == '~') {
      numbers.top() *= -1;

    } else if (IsOperator(sym)) {
      right = numbers.top();
      numbers.pop();
      left = numbers.top();
      numbers.pop();
      numbers.push(CalcOperator(left, right, sym));

    } else if (IsFun(sym)) {
      numbers.top() = CalcFun(numbers.top(), sym);

    } else {
      throw logic_error("");
    }
    pos = polish_notation_.find(' ', pos) + 1;
  }
  return numbers.top();
}

inline double ModelCalculator::CalcOperator(double left, double right,
                                            char op) {
  double res = 0.;
  switch (op) {
    case '+':
      res = left + right;
      break;
    case '-':
      res = left - right;
      break;
    case '*':
      res = left * right;
      break;
    case '/':
      res = left / right;
      break;
    case 'm':
      res = fmod(left, right);
      break;
    case '^':
      res = pow(left, right);
      break;
  }
  return res;
}

inline double ModelCalculator::CalcFun(double val, char fun) {
  double res = 0.;
  switch (fun) {
    case 'S':
      res = asin(val);
      break;
    case 'C':
      res = acos(val);
      break;
    case 'T':
      res = atan(val);
      break;
    case 's':
      res = sin(val);
      break;
    case 'c':
      res = cos(val);
      break;
    case 't':
      res = tan(val);
      break;
    case 'q':
      res = sqrt(val);
      break;
    case 'l':
      res = log(val);
      break;
    case 'L':
      res = log10(val);
      break;
  }
  return res;
}

}  // namespace s21
#endif  // MODEL_H
