#ifndef NEWTODOITEMDIALOG_H
#define NEWTODOITEMDIALOG_H

#include <QDialog>

namespace Ui {
class NewTodoItemDialog;
}

class NewTodoItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewTodoItemDialog(QWidget *parent = 0);
    ~NewTodoItemDialog();

private slots:

    void on_okButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::NewTodoItemDialog *ui;

    QWidget *parent;
};

#endif // NEWTODOITEMDIALOG_H
