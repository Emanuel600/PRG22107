#ifndef SHELFLIST_H
#define SHELFLIST_H

#include <QListWidget>
// Abstract
class ShelfList : public QListWidget{
public:
    ShelfList();
    int get_row(QListWidgetItem*item);
};

#endif // SHELFLIST_H
