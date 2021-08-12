#ifndef TODOWIDGET_H
#define TODOWIDGET_H

#include <QWidget>

namespace Ui {
class ToDoWidget;
}

class ToDoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ToDoWidget(QWidget *parent = nullptr);
    ~ToDoWidget();

private:
    Ui::ToDoWidget *ui;
};

#endif // TODOWIDGET_H
