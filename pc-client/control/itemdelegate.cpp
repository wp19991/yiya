#include "itemdelegate.h"

#include <QMouseEvent>
#include <QPainter>
#include <QStyledItemDelegate>
#include <QStyle>
#include <QEvent>
#include <QDebug>
#include <QFontMetrics>
#include "itemdef.h"

ItemDelegate::ItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

ItemDelegate::~ItemDelegate()
{

}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{


    if(index.isValid())
    {
        painter->save();

        painter->setRenderHint(QPainter::Antialiasing, true);
        ItemStatus status = (ItemStatus)(index.data(Qt::UserRole).toInt());

        QVariant variant = index.data(Qt::UserRole+1);
        ItemData data = variant.value<ItemData>();

        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth( option.rect.width()-1);
        rect.setHeight(option.rect.height()-1);

        //QPainterPath画圆角矩形
        const qreal radius = 7;
        QPainterPath path;
        path.moveTo(rect.topRight() - QPointF(radius, 0));
        path.lineTo(rect.topLeft() + QPointF(radius, 0));
        path.quadTo(rect.topLeft(), rect.topLeft() + QPointF(0, radius));
        path.lineTo(rect.bottomLeft() + QPointF(0, -radius));
        path.quadTo(rect.bottomLeft(), rect.bottomLeft() + QPointF(radius, 0));
        path.lineTo(rect.bottomRight() - QPointF(radius, 0));
        path.quadTo(rect.bottomRight(), rect.bottomRight() + QPointF(0, -radius));
        path.lineTo(rect.topRight() + QPointF(0, radius));
        path.quadTo(rect.topRight(), rect.topRight() + QPointF(-radius, -0));
        painter->setPen(QPen(Qt::gray));
        if(option.state.testFlag(QStyle::State_Selected))
        {
            painter->setBrush(QColor(41, 41, 41));
            painter->drawPath(path);
        }
        else if(option.state.testFlag(QStyle::State_MouseOver))
        {
            painter->setBrush(QColor(41, 41, 41));
            painter->drawPath(path);
        }
        else{

            painter->setBrush(QColor(68, 68, 68));
            painter->drawPath(path);
        }

        //绘制数据位置
        QRect NameRect = QRect(rect.left() +10, rect.top()+10, rect.width()-80, rect.height() -20);
        QRect circle = QRect(NameRect.right() +10, rect.top()+(rect.height() -25)/2, 25, 25);

        QImage image_icon(":/selected.svg");
        switch (status) {
        case S_RED:
            image_icon = QImage(":/selected.svg");
            break;
        case S_BLUE:
            image_icon = QImage(":/partiallychecked.svg");
            break;
        case S_YELLOW:
            image_icon = QImage(":/unselected.svg");
            break;
        }

        painter->drawImage(circle,image_icon);     //画圆圈

        painter->setPen(QPen(Qt::white));
        painter->setFont(QFont("Times", 12, QFont::Bold));
        painter->drawText(NameRect, Qt::AlignLeft |Qt::AlignVCenter,data.str_info); //绘制文字

        painter->restore();
    }
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(option.widget->width()-10, 60);
}

bool ItemDelegate::editorEvent(QEvent *event,
                               QAbstractItemModel *model,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index)
{

    if((event->type() == QEvent::MouseButtonRelease) ||
            (event->type() == QEvent::MouseButtonDblClick))
    {
        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth( option.rect.width()-1);
        rect.setHeight(option.rect.height()-1);

        QRect NameRect = QRect(rect.left() +10, rect.top()+10, rect.width()-80, rect.height() -20);
        QRect circle = QRect(NameRect.right() +10, rect.top()+(rect.height() -25)/2, 25, 25);

        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        if(mouseEvent->button() != Qt::LeftButton||
                !circle.contains(mouseEvent->pos()))
        {
            return true;
        }
        if(event->type() == QEvent::MouseButtonDblClick)
        {
            return true;
        }
        ItemStatus itemStatus = static_cast<ItemStatus>(index.model()->data(index, Qt::UserRole).toInt());
        if(itemStatus == ItemStatus::S_RED)
        {
            itemStatus = ItemStatus::S_YELLOW;
        }else
        {
            itemStatus = ItemStatus::S_RED;
        }
        return model->setData(index, itemStatus, Qt::UserRole);
    }
    return QStyledItemDelegate::editorEvent(event, model, option, index);

}
