#include "edit_box.h"
#include "ui_edit_box.h"



EditBox::EditBox(const QString &title, const QString &defaultContent,
                 EditBox::acceptCallbackt_t func_ok, EditBox::rejectCallback_t func_err,
                 QWidget *parent)
    :QDialog(parent),
      ui(new Ui::EditBox)
{
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    this->ui->setupUi(this);
    this->ui->labTitle->setText(title);
    this->ui->txtInput->setText(defaultContent);
    this->setCbOk(func_ok);
    this->setCbCancel(func_err);
}

EditBox::~EditBox()
{
    delete ui;
}

void EditBox::setTitle(const QString &title)
{
    this->ui->labTitle->setText(title);
}

void EditBox::setCbOk(EditBox::acceptCallbackt_t cbOk)
{
    if(cbOk){
        this->m_cbOk = std::move(cbOk);
    }
}

void EditBox::setCbCancel(EditBox::rejectCallback_t cbCancel)
{
    if(cbCancel){
        this->m_cbCancel = std::move(cbCancel);
    }
}



void EditBox::on_btnOk_clicked()
{
    if(this->m_cbOk){
        this->m_cbOk();
    }
}

void EditBox::on_btnBack_clicked()
{
    if(this->m_cbCancel){
        this->m_cbCancel(-1);
    }
}
