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
    auto *new_todo_item_dialog = new NewTodoItemDialog(this);
    new_todo_item_dialog->show();
}

void MainWindow::appendItem(const QString &item, bool done) {
    ui->todoItemsView->appendItem(item, done);
}
