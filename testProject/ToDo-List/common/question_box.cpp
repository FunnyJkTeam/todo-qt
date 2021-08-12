#include "question_box.h"
#include "ui_question_box.h"

QuestionBox::QuestionBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestionBox)
{
    ui->setupUi(this);
}

QuestionBox::~QuestionBox()
{
    delete ui;
}

void QuestionBox::setTitle(const QString &title)
{
    this->ui->labTitle->setText(title);
}

void QuestionBox::setContent(const QString &content)
{
    this->ui->labTips->setText(content);
}

void QuestionBox::setConfirmedCallback(QuestionBox::acceptCallbackt_t func)
{
    if(func){
        this->m_OnConfirmed = std::move(func);
    }
}

void QuestionBox::setCanceledCallback(QuestionBox::rejectCallback_t func)
{
    if(func){
        this->m_onCanceled = std::move(func);
    }
}

void QuestionBox::on_btnOk_clicked()
{
    if(this->m_OnConfirmed){
        this->m_OnConfirmed();
    }
    this->accept();
}

void QuestionBox::on_btnBack_clicked()
{
    if(this->m_onCanceled){
        this->m_onCanceled(-1);
    }
    this->reject();
}
