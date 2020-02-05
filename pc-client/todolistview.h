#ifndef TODOLISTVIEW_H
#define TODOLISTVIEW_H

#include <QStandardItemModel>
#include <QListView>

class TodoListView : public QListView {
public:
    explicit TodoListView(QWidget *parent) : QListView(parent) {
        itemModel = new QStandardItemModel(this);
        this->setModel(itemModel);
    }

    ~TodoListView() {
        delete itemModel;
    }

    void appendItem(const QString &item) {
        itemModel->appendRow(new QStandardItem(item));
    }

private:
    QStandardItemModel *itemModel = nullptr;
};

#endif // TODOLISTVIEW_H
