#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

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
};

#endif // MAINWINDOW_H
