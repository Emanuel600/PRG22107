#ifndef SHELFLIST_H
#define SHELFLIST_H

#include <QListWidget>
// Lista de notas dentro de um livro
class ShelfList : public QListWidget{
public:
    ShelfList();
    int get_row(QListWidgetItem*item);
private slots:
    // Renomear Nota
    void Rename(QListWidgetItem*item);
    // Deletar Nota
    void Delete(QListWidgetItem*item);
private:
    // Parte do menu de contexto
    QAction* RenameItem;
    QAction* DeleteItem;

    QList<QAction*> ActionList;

    QMenu* RightClickMenu;
};

#endif // SHELFLIST_H
