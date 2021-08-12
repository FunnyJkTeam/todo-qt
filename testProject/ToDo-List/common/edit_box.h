#ifndef EDIT_BOX_H
#define EDIT_BOX_H

#include <QDialog>
#include <functional>

namespace Ui {
class EditBox;
}

class EditBox
        : public QDialog
{
    Q_OBJECT
public:
    using acceptCallbackt_t = std::function<void(void)>;
    using rejectCallback_t = std::function<void(int)>;


public:
    explicit EditBox(const QString &title="",const QString &defaultContent="",
                     acceptCallbackt_t func_ok=nullptr,rejectCallback_t func_err=nullptr,
                     QWidget *parent = nullptr);
    ~EditBox() override;

    void setTitle(const QString &title);

    void setCbOk( acceptCallbackt_t cbOk);

    void setCbCancel( rejectCallback_t cbCancel);

private slots:
    void on_btnOk_clicked();

    void on_btnBack_clicked();

protected:
    Ui::EditBox *ui;

    acceptCallbackt_t m_cbOk;
    rejectCallback_t m_cbCancel;
};

#endif // EDIT_BOX_H
