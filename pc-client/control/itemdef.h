#ifndef ITEMDEF_H
#define ITEMDEF_H

#include <QMetaType>

typedef enum{
    S_RED,
    S_BLUE,
    S_YELLOW,
} ItemStatus;

struct ItemData{
    QString str_info;
};

Q_DECLARE_METATYPE(ItemData)

#endif // ITEMDEF_H
