#include "newtodoitemdialog.h"
#include "ui_newtodoitemdialog.h"
#include "todolistview.h"
#include "mainwindow.h"

NewTodoItemDialog::NewTodoItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTodoItemDialog)
{
    ui->setupUi(this);
    this->parent = parent;
}

NewTodoItemDialog::~NewTodoItemDialog()
{
    delete ui;
}

void NewTodoItemDialog::on_cancelButton_clicked()
{
    this->destroy();
}

void NewTodoItemDialog::on_okButton_clicked()
{
    if (this->ui->textEdit->toPlainText().isEmpty()) {
        // TODO(qwang): WARNING
    } else {
        reinterpret_cast<MainWindow*>(parentWidget())->appendItem(
                    this->ui->textEdit->toPlainText());
    }

    this->destroy();
}
