#ifndef CREDITWINDOW_H
#define CREDITWINDOW_H

#include <QLineEdit>
#include <QValidator>
#include <QWidget>

#include "../Controller/controller.h"

namespace Ui {
class Credit;
}

class Credit : public QWidget {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::Credit *ui;
};

#endif  // CREDITWINDOW_H
