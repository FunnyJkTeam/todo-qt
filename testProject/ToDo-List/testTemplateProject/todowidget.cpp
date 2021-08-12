#include "todowidget.h"
#include "ui_todowidget.h"

ToDoWidget::ToDoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToDoWidget)
{
    ui->setupUi(this);
}

ToDoWidget::~ToDoWidget()
{
    delete ui;
}
