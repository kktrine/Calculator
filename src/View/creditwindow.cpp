#include "creditwindow.h"

#include "ui_creditwindow.h"

Credit::Credit(QWidget* parent) : QWidget(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
  ui->overpayment->setReadOnly(true);
  ui->payment->setReadOnly(true);
  ui->total->setReadOnly(true);
  QValidator* validator_double =
      new QRegExpValidator(QRegExp("[0-9]+(\\.[0-9]+)?"));
  QValidator* validator_int = new QRegExpValidator(QRegExp("[1-9][0-9]*"));
  ui->lineEdit_percent->setValidator(validator_double);
  ui->lineEdit_amount->setValidator(validator_double);
  ui->lineEdit_period->setValidator(validator_int);
  setFixedSize(geometry().width(), geometry().height());
  setWindowTitle("Credit calculator");
}

Credit::~Credit() { delete ui; }

void Credit::on_pushButton_clicked() {
  std::string total = "", monthly = "", over = "";
  std::string sum = ui->lineEdit_amount->text().toStdString();
  std::string period = ui->lineEdit_period->text().toStdString();
  std::string percent = ui->lineEdit_percent->text().toStdString();
  Controller res;
  if (ui->differenciated->isChecked())
    res.GetCreditResult(sum, period, percent, total, monthly, over, 0);
  else if (ui->annuity->isChecked()) {
    res.GetCreditResult(sum, period, percent, total, monthly, over, 1);
  }
  ui->overpayment->setText(QString::fromStdString(over));
  ui->payment->setText(QString::fromStdString(monthly));
  ui->total->setText(QString::fromStdString(total));
}
