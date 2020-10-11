#ifndef TODOLISTVIEW_H
#define TODOLISTVIEW_H

#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QListView>
#include "control/itemdelegate.h"
#include "control/itemdef.h"
class TodoListView : public QListView {
public:
    explicit TodoListView(QWidget *parent) : QListView(parent) {

        item_delegate_ = new ItemDelegate(this);
        setItemDelegate(item_delegate_);       //为视图设置委托

        item_model_ = new QStandardItemModel(this);
        proxy_item_model_ = new QSortFilterProxyModel(this);
        proxy_item_model_->setSourceModel(item_model_);
        proxy_item_model_->setFilterRole(Qt::UserRole);
        proxy_item_model_->setDynamicSortFilter(true);
        setModel(proxy_item_model_);                  //为委托设置模型
        setViewMode(QListView::IconMode); //设置Item图标显示
        setDragEnabled(false);            //控件不允许拖动
    }

    ~TodoListView() {
        delete item_model_;
    }

    void appendItem(const QString &item, bool done) {

        ItemData itemData;
        itemData.str_info = item;
        ItemStatus itemStatus = done? S_RED : S_YELLOW;

        QStandardItem *ptr_item = new QStandardItem;
        ptr_item->setData(itemStatus,Qt::UserRole);  // 单一存取
        ptr_item->setData(QVariant::fromValue(itemData),Qt::UserRole+1);//整体存取
        item_model_->appendRow(ptr_item);
    }

private:
    ItemDelegate* item_delegate_ = nullptr;                 //委托
    QSortFilterProxyModel* proxy_item_model_ = nullptr;
    QStandardItemModel *item_model_ = nullptr;
};

#endif // TODOLISTVIEW_H
