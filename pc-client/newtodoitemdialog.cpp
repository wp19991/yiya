#include "newtodoitemdialog.h"
#include "ui_newtodoitemdialog.h"
#include "todolistview.h"
#include "mainwindow.h"

#include <QJsonObject>
#include <QMessageBox>

#include "networkutil.h"

NewTodoItemDialog::NewTodoItemDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTodoItemDialog)
{
    ui->setupUi(this);
    this->parent = parent;
    connect(&NetworkUtil::instance(), &NetworkUtil::addTodoItemReplied, this, &NewTodoItemDialog::onAddTodoItemReply);
}

NewTodoItemDialog::~NewTodoItemDialog()
{
    delete ui;
}

void NewTodoItemDialog::onAddTodoItemReply(QJsonObject replied_json) {
    auto it = replied_json.find("status");
    assert(it != replied_json.end());
    if (it.value() != "ok" && it.value() != "OK" && it.value() != "Ok") {
        auto err_it = replied_json.find("error_msg");
        assert(err_it != replied_json.end());
        QMessageBox::information(NULL, "提示",QString("添加待办事项失败:") + err_it.value().toString(), QMessageBox::Yes);
        return;
    }

    // 新增待办事项成功, 绘制到窗口
    reinterpret_cast<MainWindow*>(parentWidget())->appendItem(
                this->ui->textEdit->toPlainText());
    this->setEnabled(true);
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
        // loading......
       NetworkUtil::instance().addTodoItem(NetworkUtil::instance().getUserId(), this->ui->textEdit->toPlainText());
        this->setEnabled(false);
    }

    this->destroy();
}
