#include "logindialog.h"
#include "ui_logindialog.h"


#include "networkutil.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(&NetworkUtil::instance(), &NetworkUtil::loginReplied, this, &LoginDialog::onLoginReply);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_exitButton_clicked()
{
    this->close();
}

void LoginDialog::on_loginButton_clicked()
{
    NetworkUtil::instance().login(ui->usernameLineEdit->text(), ui->passwordlineEdit->text());
}

void LoginDialog::on_loginButton_clicked(bool checked)
{

}
