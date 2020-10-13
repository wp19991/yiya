#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class NewTodoItemDialog;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void appendItem(const QString &item, bool done = false);

    ~MainWindow();

private slots:
    void on_newTodoItemButton_clicked();

private:
    Ui::MainWindow *ui;
    NewTodoItemDialog *ptr_new_todo_item_dialog_ = nullptr;
};

#endif // MAINWINDOW_H
