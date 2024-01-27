#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include <QDialog>
#include <vector>

#include "../Controller/controller.h"
namespace Ui {
class Graph;
}

class Graph : public QDialog {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr, QString expr_arg = "");
  //  void set_label_text(QString expr);
  ~Graph();

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::Graph *ui;
  QString expr;
};

#endif  // GRAPHWINDOW_H
