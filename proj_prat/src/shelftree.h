#ifndef SHELFTREE_H
#define SHELFTREE_H

#include <QInputDialog>
#include <QTreeWidget>
#include <QMenuBar>

#include "shelflist.h"
#include "notebook.h"

class Shelftree : public QTreeWidget{
public:
    Shelftree();

    void add_list(QList<QString> list);
    void add_book(Notebook* book);
private slots:
    void toggle();

    void Edit();
    void Delete();
    void CreateNote();

    void ShowContextMenu(const QPoint &);
private:
    // Right-Click menu
    void CreateMenu();
    // Actions of the menu
    void CreateActions();

    QAction* EditItem;
    QAction* DeleteItem;
    QAction* CreateChild;

    QList<QAction*> RightClickActions;

    QMenu* RightClickMenu;
};

#endif // SHELFTREE_H
