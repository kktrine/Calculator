#include "mainwindow.h"

#include "../Controller/controller.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  credit = new Credit();
  ui->setupUi(this);
  setFixedSize(geometry().width(), geometry().height());
  ui->textEdit_expr->setFocus();
  ui->textEdit_expr->setFocusPolicy(Qt::ClickFocus);
  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(input()));
  ui->pushButton_0->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(input()));
  ui->pushButton_1->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(input()));
  ui->pushButton_2->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(input()));
  ui->pushButton_3->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(input()));
  ui->pushButton_4->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(input()));
  ui->pushButton_5->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(input()));
  ui->pushButton_6->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(input()));
  ui->pushButton_7->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(input()));
  ui->pushButton_8->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(input()));
  ui->pushButton_9->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(input()));
  ui->pushButton_x->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(input()));
  ui->pushButton_plus->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(input()));
  ui->pushButton_minus->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(input()));
  ui->pushButton_mul->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(input()));
  ui->pushButton_div->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(input()));
  ui->pushButton_mod->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(input()));
  ui->pushButton_pow->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(input_function()));
  ui->pushButton_sqrt->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(input_function()));
  ui->pushButton_sin->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(input_function()));
  ui->pushButton_cos->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(input_function()));
  ui->pushButton_tan->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(input_function()));
  ui->pushButton_asin->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(input_function()));
  ui->pushButton_acos->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(input_function()));
  ui->pushButton_atan->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_left_bracket, SIGNAL(clicked()), this, SLOT(input()));
  ui->pushButton_left_bracket->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_right_bracket, SIGNAL(clicked()), this, SLOT(input()));
  ui->pushButton_right_bracket->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(input_function()));
  ui->pushButton_log->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(input_function()));
  ui->pushButton_ln->setFocusPolicy(Qt::NoFocus);
  connect(ui->pushButton_e, SIGNAL(clicked()), this, SLOT(input()));
  ui->pushButton_e->setFocusPolicy(Qt::NoFocus);
  ui->pushButton_dot->setFocusPolicy(Qt::NoFocus);
  ui->pushButton_C->setFocusPolicy(Qt::NoFocus);
  ui->pushButton_CE->setFocusPolicy(Qt::NoFocus);
}
MainWindow::~MainWindow() { delete ui; }

int MainWindow::input() {
  QPushButton* button = (QPushButton*)sender();
  if (ui->textEdit_x->hasFocus() &&
      ((button->text() >= '0' && button->text() <= '9') ||
       button->text() == "-" || button->text() <= 'e')) {
    if (ui->textEdit_x->toPlainText() == "x") ui->textEdit_x->setText("");
    ui->textEdit_x->insertPlainText(button->text());

  } else {
    if (ui->textEdit_expr->toPlainText() == "Expression")
      ui->textEdit_expr->setText("");
    ui->textEdit_expr->insertPlainText(button->text());
  }
  return 0;
}

int MainWindow::input_function() {
  QPushButton* button = (QPushButton*)sender();
  if (ui->textEdit_expr->toPlainText() == "Expression")
    ui->textEdit_expr->setText("");
  ui->textEdit_expr->insertPlainText(button->text() + "(");
  return 0;
}

void MainWindow::on_pushButton_eq_clicked() {
  QString array = ui->textEdit_expr->toPlainText();
  QString array_x = ui->textEdit_x->toPlainText();
  Controller res;
  ui->label_answer->setText(QString::fromStdString(
      res.GetCalculationResult(array.toStdString(), array_x.toStdString())));
}

void MainWindow::on_pushButton_CE_clicked() {
  ui->textEdit_expr->setText(
      "<html><head/><body><p align=\"center\">Expression</p></body></html>");
  ui->textEdit_x->setText(
      "<html><head/><body><p align=\"center\">x</p></body></html>");
  ui->label_answer->setText(
      "<html><head/><body><p align=\"center\">Answer</p></body></html>");
  //  ui->label_answer->setText("Answer");
}

void MainWindow::on_pushButton_plot_clicked() {
  Graph window_graph(nullptr, ui->textEdit_expr->toPlainText());
  window_graph.setModal(true);
  window_graph.setWindowTitle("Graph");
  window_graph.exec();
}

void MainWindow::on_pushButton_dot_clicked() {
  if (ui->textEdit_x->hasFocus()) {
    if (ui->textEdit_x->toPlainText() == "x") ui->textEdit_x->setText("");
    ui->textEdit_x->insertPlainText(".");

  } else {
    if (ui->textEdit_expr->toPlainText() == "Expression")
      ui->textEdit_expr->setText("");
    ui->textEdit_expr->insertPlainText(".");
  }
}

void MainWindow::on_pushButton_C_clicked() {
  QString text = 0;
  if (ui->textEdit_x->hasFocus()) {
    if (ui->textEdit_x->toPlainText() == "x")
      ui->textEdit_x->setText("");
    else {
      text = ui->textEdit_x->toPlainText();
      text.chop(1);
      ui->textEdit_x->setText(text);
      QTextCursor cursor = ui->textEdit_x->textCursor();
      cursor.movePosition(QTextCursor::End);
      ui->textEdit_x->setTextCursor(cursor);
    }

  } else {
    if (ui->textEdit_expr->toPlainText() == "Expression")
      ui->textEdit_expr->setText("");
    else {
      text = ui->textEdit_expr->toPlainText();
      text.chop(1);
      ui->textEdit_expr->setText(text);
      QTextCursor cursor = ui->textEdit_expr->textCursor();
      cursor.movePosition(QTextCursor::End);
      ui->textEdit_expr->setTextCursor(cursor);
    }
  }
}

void MainWindow::on_pushButton_clicked() { credit->show(); }
