#include "mainwindow.h"
#include <QApplication>

#include "logindialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // login first.
    LoginDialog login_dialog;
    login_dialog.show();


//    MainWindow w;
//    w.setWindowFlags(w.windowFlags() | Qt::WindowStaysOnTopHint);
//    w.showNormal();
//    w.show();

    return a.exec();
}
