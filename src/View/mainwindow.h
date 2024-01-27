#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPlainTextEdit>
#include <QWidget>

#include "../Controller/controller.h"
#include "creditwindow.h"
#include "depositwindow.h"
#include "graphwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  Credit *credit;
  Deposit *deposit;

 private slots:
  int input();
  void on_pushButton_eq_clicked();
  void on_pushButton_CE_clicked();
  int input_function();
  void on_pushButton_plot_clicked();
  void on_pushButton_dot_clicked();
  void on_pushButton_C_clicked();
  void on_pushButton_clicked();
};

#endif  // MAINWINDOW_H
