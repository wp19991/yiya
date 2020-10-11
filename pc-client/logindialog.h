#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <memory>
#include <QDialog>
#include <QMessageBox>
#include <QJsonObject>
#include <iostream>
#include <assert.h>
#include "mainwindow.h"

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

    void onHttpReply(QJsonObject replied_json) {
        auto it = replied_json.find("status");
        assert(it != replied_json.end());

        if (it.value() == "ok" || it.value() == "Ok" || it.value() == "OK") {
            QMessageBox::information(NULL, "提示", "登录成功.", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                main_window_.reset(new MainWindow());
                main_window_->setWindowFlags(main_window_->windowFlags() | Qt::WindowStaysOnTopHint);
                main_window_->showNormal();
                main_window_->show();
                this->hide();
        } else {
            QMessageBox::information(NULL, "提示", "登录失败.", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
    }

private:
    Ui::LoginDialog *ui;

    std::unique_ptr<MainWindow> main_window_ = nullptr;
};

#endif // LOGINDIALOG_H
