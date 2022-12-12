#include "shelflist.h"

ShelfList::ShelfList(){}

int ShelfList::get_row(QListWidgetItem*item){
        QModelIndex ind =  this->indexFromItem(item);
        return ind.row();
}
