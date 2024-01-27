#include "depositwindow.h"

#include "ui_depositwindow.h"

Deposit::Deposit(QWidget *parent) : QWidget(parent), ui(new Ui::Deposit) {
  ui->setupUi(this);
}

Deposit::~Deposit() { delete ui; }
