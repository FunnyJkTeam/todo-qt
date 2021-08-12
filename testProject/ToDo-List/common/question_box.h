#ifndef QUESTION_BOX_H
#define QUESTION_BOX_H

#include <QDialog>
#include <functional>

namespace Ui {
class QuestionBox;
}

class QuestionBox : public QDialog
{
    Q_OBJECT
public:
    using acceptCallbackt_t = std::function<void(void)>;
    using rejectCallback_t = std::function<void(int)>;

public:
    explicit QuestionBox(QWidget *parent = nullptr);
    ~QuestionBox();

    void setTitle(const QString &title);
    void setContent(const QString &content);

    void setConfirmedCallback(acceptCallbackt_t func);
    void setCanceledCallback(rejectCallback_t func);

protected:
    Ui::QuestionBox *ui;

    acceptCallbackt_t m_OnConfirmed;
    rejectCallback_t m_onCanceled;
private slots:
    void on_btnOk_clicked();
    void on_btnBack_clicked();
};

#endif // QUESTION_BOX_H
