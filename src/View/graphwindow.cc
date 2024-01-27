#include "graphwindow.h"

#include <iostream>

#include "ui_graphwindow.h"

Graph::Graph(QWidget* parent, QString expr_arg)
    : QDialog(parent), ui(new Ui::Graph) {
  ui->setupUi(this);
  setFixedSize(geometry().width(), geometry().height());
  expr = expr_arg;
  ui->label_graph_name->setText("  y =    " + expr);
  QValidator* validator_double =
      new QRegExpValidator(QRegExp("^-?\\d*\\.?\\d*$"));
  ui->x_min->setValidator(validator_double);
  ui->x_max->setValidator(validator_double);

  ui->widget_graph->addGraph();
}

Graph::~Graph() { delete ui; }

void Graph::on_pushButton_clicked() {
  std::vector<double> x, y;
  double y_min = stod(ui->y_min->text().toStdString()),
         y_max = stod(ui->y_max->text().toStdString());
  std::string x_min = ui->x_min->text().toStdString();
  std::string x_max = ui->x_max->text().toStdString();
  if (ui->widget_graph->graph(0)->data()->isEmpty() == 0) {
    ui->widget_graph->graph(0)->data()->clear();
    ui->widget_graph->replot();
  }
  Controller graph;
  if (graph.GetGraphResult(expr.toStdString(), x_min, x_max, x, y) &&
      y_min < y_max) {
    QVector<double> X(x.begin(), x.end()), Y(y.begin(), y.end());
    ui->widget_graph->graph(0)->setData(X, Y);
    ui->widget_graph->xAxis->setRange(stod(x_min), stod(x_max));
    ui->widget_graph->yAxis->setRange(y_min, y_max);
    ui->widget_graph->replot();
    ui->label_graph_name->setText("  y =    " + expr);
  } else {
    ui->label_graph_name->setText("  y =    " + expr + "   ERROR!");
  }
}
