#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <memory>
#include <QDialog>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>

#include <iostream>
#include <assert.h>
#include "mainwindow.h"

#include "networkutil.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_exitButton_clicked();

    void on_loginButton_clicked();

    void onLoginReply(QJsonObject replied_json) {
        auto it = replied_json.find("status");
        assert(it != replied_json.end());

        if (it.value() == "ok" || it.value() == "Ok" || it.value() == "OK") {
            auto data_it = replied_json.find("data").value();
            auto data = data_it.toObject();
            auto user_id = data["user_id"].toString();
            NetworkUtil::instance().setUserId(user_id);

            QMessageBox::information(NULL, "提示", "登录成功.", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            main_window_.reset(new MainWindow());
            main_window_->setWindowFlags(main_window_->windowFlags() | Qt::WindowStaysOnTopHint);
            main_window_->showNormal();
            main_window_->show();
            this->hide();

            // 获取TODO列表
            NetworkUtil::instance().queryTodoItems(user_id);

        } else {
            QMessageBox::information(NULL, "提示", "登录失败.", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
    }

    void onQueryTodoItemReply(QJsonObject replied_json) {
        auto it = replied_json.find("status");
        assert(it != replied_json.end());

        if (it.value() != "ok" && it.value() != "OK" && it.value() != "Ok") {
            QMessageBox::information(NULL, "提示", "或缺待办事项失败。", QMessageBox::Yes);
            return;
        }

        auto todo_items = replied_json.find("data")->toArray();
        for(const auto &todo_item : todo_items) {
            auto user_id = todo_item.toObject()["user_id"].toString();
            auto context = todo_item.toObject()["context"].toString();
            // status为0表示todo, 为1表示done。
            int status = todo_item.toObject()["status"].toInt();
            main_window_->appendItem(context, /*done=*/status == 1);
        }

    }

    void on_loginButton_clicked(bool checked);

private:
    Ui::LoginDialog *ui;

    std::unique_ptr<MainWindow> main_window_ = nullptr;
};

#endif // LOGINDIALOG_H
