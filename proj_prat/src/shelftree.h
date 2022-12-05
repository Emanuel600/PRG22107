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

    void EditBook();
    void DeleteBook();
    void NewNote();

    void ShowContextMenu(const QPoint &);
signals:
    // Envia sinal a shelf (parente) que foi modificada
    void Book_Renamed(unsigned index) {}
    void Book_Deleted(unsigned index) {}
    void Note_Created(unsigned index) {}
private:
    // Right-Click menu
    void CreateMenu();
    // Actions of the menu (books)
    void CreateBookActions();
    // Actions of the menu (notes)
    void CreateNoteActions();

    // Aux methods
    void Edit_Book(QTreeWidgetItem* book_item);

    QAction* EditBookItem;
    QAction* DeleteBookItem;
    QAction* NewNoteAction;

    QAction* EditNoteItem;
    QAction* DeleteNoteItem;

    QList<QAction*> CurrentActions;

    QMenu* RightClickMenu;
};

#endif // SHELFTREE_H
