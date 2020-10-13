#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QStandardItemModel"
#include "newtodoitemdialog.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int i = 0;
void MainWindow::on_newTodoItemButton_clicked()
{
    if(ptr_new_todo_item_dialog_ == nullptr){
        ptr_new_todo_item_dialog_ = new NewTodoItemDialog(this);
    }
    // 此处需要阻塞其他界面
    ptr_new_todo_item_dialog_->exec();
}

void MainWindow::appendItem(const QString &item, bool done)
{
    ui->todoItemsView->appendItem(item, done);
}
