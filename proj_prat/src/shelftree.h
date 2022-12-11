#ifndef SHELFTREE_H
#define SHELFTREE_H

#include <QInputDialog>
#include <QTreeWidget>
#include <QMenuBar>

#include "shelflist.h"
#include "notebook.h"

class Shelftree : public QTreeWidget{
Q_OBJECT
public:
    Shelftree();

    void add_list(QList<QString> list);
    void add_book(Notebook* book);
private slots:
    void toggle(){}

    void ShowContextMenu(const QPoint &);
signals:
    // Envia sinal a shelf (parente) que foi modificada
    void Book_Renamed(unsigned index);
    void Book_Deleted(unsigned index);
    void Note_Created(unsigned index);
    void List_Created(unsigned index);
    void Note_Opened(unsigned bx, unsigned nx);
    void Note_Edited(unsigned bx, unsigned nx);
    void Note_Deleted(unsigned bx, unsigned nx);
private:
    // Right-Click menu
    void CreateMenu();
    /* Actions of the menu */
    /* books */
    void CreateBookActions();
    /* Notes */
    void CreateNoteActions();

    /* Aux methods */
    // Rename
    void Edit_Book(QTreeWidgetItem* book_item);
    // Delete
    void DeleteBook();
    // Rename
    void EditBook();
    // Creates note
    void NewNote();
    // Creates list
    void NewList();
    // Opens note/list
    void OpenNote();
    // Edits note/list
    void EditNote();
    // Deletes a note/list
    void DeleteNote();

    QAction* DeleteBookItem;
    QAction* NewNoteAction;
    QAction* NewListAction;
    QAction* EditBookItem;

    QAction* EditNoteItem;
    QAction* DeleteNoteItem;

    QList<QAction*> CurrentActions;

    QMenu* RightClickMenu;
};

#endif // SHELFTREE_H
